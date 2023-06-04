#include <opencv/highgui.h> ///�ϥ� OpenCV 2.1 ���²��, �u�n�� High GUI �Y�i
#include <opencv/cv.h>
#include <stdio.h>
#include <GL/glut.h>
#include "glm.h"
///�令Ū�i�����H���骺�U����
GLMmodel * head = NULL;///GLMmodel * robot = NULL;///�����H���ū���
GLMmodel * body = NULL;
GLMmodel * hand_left1 = NULL, * hand_right1 = NULL;///�����H�W���u
GLMmodel * hand_left2 = NULL, * hand_right2 = NULL;///�����H�����u
GLMmodel * hand_left3 = NULL, * hand_right3 = NULL;///�����H�U���u
GLMmodel * l_leg = NULL, * r_leg = NULL;///�����H���Ⱖ�}

float teapotX = 0, teapotY = 0, oldX = 0, oldY = 0;
float angle[20] = {}, angle2[20] = {};///�쥻�Ofloat angle = 0, angle2=0
float NewAngle[20] = {}, NewAngle2[20] = {};
float OldAngle[20] = {}, OldAngle2[20] = {};
int ID = 0;///ID�|�P�_��L����O���@�����`�n��
FILE * fout = NULL;///�g�ɮ�
FILE * fin = NULL;///Ū�ɮ�


void timer(int t)
{
    printf("�{�btimer(%d)\n", t);
    glutTimerFunc(20,timer,t+1);///���W�]�w�U�Ӿx��

    float alpha = (t%50)/50.0;///0.0~1.0

    if (t%50==0)
    {
        if(fin==NULL) fin = fopen("motion.txt","r");
        for ( int i=0;i<20;i++ )
        {
            OldAngle[i] = NewAngle[i];
            OldAngle2[i] = NewAngle2[i];
            fscanf(fin,"%f",&NewAngle[i]);
            fscanf(fin,"%f",&NewAngle2[i]);
        }
    }
    for ( int i=0;i<20;i++)
    {
        angle[i] = NewAngle[i] * alpha + OldAngle[i] * (1-alpha);
        angle2[i] = NewAngle2[i] * alpha + OldAngle2[i] * (1-alpha);

    }

    glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y)///��L����禡
{
    if ( key=='0' ) ID = 0;
    if ( key=='1' ) ID = 1;
    if ( key=='2' ) ID = 2;
    if ( key=='3' ) ID = 3;
    if ( key=='4' ) ID = 4;
    if ( key=='5' ) ID = 5;
    if ( key=='6' ) ID = 6;
    if ( key=='7' ) ID = 7;
    if ( key=='8' ) ID = 8;
    if ( key=='9' ) ID = 9;
    if ( key=='s' ) {///SAVE�s��,�|�ʨ�motion�ɮ�
        if (fout == NULL) fout = fopen("motion.txt","w");
        for(int i=0; i<20; i++)
        {
            fprintf(fout, "%.2f", angle[i]);
            fprintf(fout,"%.2f", angle2[i]);
        }
        fprintf(fout,"\n");
        printf("�g�F�@��");
    }
    if (key=='r'){///read Ū�ɷ|,�ʨ�motion�ɮ�
        if(fin == NULL) fin = fopen("motion.txt", "r");
        for(int i=0;i<20;i++){
            fscanf(fin, "%f", &angle[i]);
            fscanf(fin, "%f", &angle2[i]);
        }
        glutPostRedisplay();
    }
    if (key=='p'){///play���� �|�ʨ�motion�ɮ�
        glutTimerFunc(0,timer,0);
    }
}
int myTexture(char * filename)///�K��
{
    IplImage * img = cvLoadImage(filename); ///OpenCVŪ��
    cvCvtColor(img,img, CV_BGR2RGB); ///OpenCV���m (�ݭncv.h)
    glEnable(GL_TEXTURE_2D); ///1. �}�ҶK�ϥ\��
    GLuint id; ///�ǳƤ@�� unsigned int ���, �s �K��ID
    glGenTextures(1, &id); /// ����Generate �K��ID
    glBindTexture(GL_TEXTURE_2D, id); ///�j�wbind �K��ID
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); /// �K�ϰѼ�, �W�L�]�˪��d��T, �N���жK��
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); /// �K�ϰѼ�, �W�L�]�˪��d��S, �N���жK��
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /// �K�ϰѼ�, ��j�ɪ�����, �γ̪��I
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /// �K�ϰѼ�, �Y�p�ɪ�����, �γ̪��I
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->imageData);
    return id;
}
void mouse(int button, int state, int x, int y) {
    oldX = x;
    oldY = y;
}
void motion(int x, int y) {///150*5���Y�����ʳt���ܧ�
    teapotX += (x-oldX) / 150.0*5;///teapotX = (x-150)/150.0;
    teapotY += (oldY-y) / 150.0*5;///teapotY = (150-y)/150.0;
    angle[ID] += x - oldX;
    angle2[ID] += oldY - y;///�ĤG�ӱ��઺���ץi���y�b�����Y
    oldX = x;
    oldY = y;
    glutPostRedisplay();
    printf("  glTranslatef( %.2f, %.2f, 0 ); \n", teapotX, teapotY );
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glScalef(1.5,1.5,1.5);///�����H���Y�M����A��j�@�I
        glTranslatef(0,-0.5,0);///���U�@�b(�U�O-0.5)
        glPushMatrix();
            glColor3f(1,1,1);///�����H�����C��///�n������H�C��אּ�զ� �N�i�H�ݨ�K�ϤF
            glScalef(0.1,0.1,0.1);///�����H���j�p
            glRotatef(angle[0],0,1,0);///�����H���y�b��V����///���骺���
            ///glmDraw(robot, GLM_MATERIAL|GLM_TEXTURE);///�[�Wtexture�\�� �����H�i�H��M���e�{
            glmDraw(body, GLM_MATERIAL|GLM_TEXTURE);///�����e����

            glPushMatrix();///�����H�����W���u
                glTranslatef( -2.07, +7.87, 0 );
                glRotatef(angle[1],0,1,0);///��y�b�����
                glRotatef(angle2[1],1,0,0);///�h�@�Ө������Y���u��180��
                glTranslatef( 2.07, -7.87, 0 );///glTranslated(teapotX,teapotY,0);
                glmDraw(hand_left1,GLM_MATERIAL|GLM_TEXTURE);

                glPushMatrix();///�����H�������u
                    glTranslatef( -3.37, +6.97, 0 );
                    glRotatef(angle[2],0,1,0);///��y�b�����
                    glRotatef(angle2[2],1,0,0);///�h�@�Ө������Y���u��180��
                    glTranslatef( 3.37, -6.97, 0 );///glTranslated(teapotX,teapotY,0);
                    glmDraw(hand_left2,GLM_MATERIAL|GLM_TEXTURE);
                glPopMatrix();

                glPushMatrix();///�����H�����U���u
                    glTranslatef( -4.40, +5.10, 0 );
                    glRotatef(angle[3],0,1,0);///��y�b�����
                    glRotatef(angle2[3],1,0,0);///�h�@�Ө������Y���u��180��
                    glTranslatef( 4.40, -5.10, 0 );///glTranslated(teapotX,teapotY,0);
                    glmDraw(hand_left3,GLM_MATERIAL|GLM_TEXTURE);
                glPopMatrix();

            glPopMatrix();


            glPushMatrix();///�����H���k�W���u
                glTranslatef( +2.07, +7.87, 0 );
                glRotatef(angle[4],0,1,0);///��y�b�����
                glRotatef(angle2[4],1,0,0);///�h�@�Ө������Y���u��180��
                glTranslatef( -2.07, -7.87, 0 );///glTranslated(teapotX,teapotY,0);
                glmDraw(hand_right1,GLM_MATERIAL|GLM_TEXTURE);

                glPushMatrix();///�����H���k���u
                    glTranslatef( +3.37, +6.97, 0 );
                    glRotatef(angle[5],0,1,0);///��y�b�����
                    glRotatef(angle2[5],1,0,0);///�h�@�Ө������Y���u��180��
                    glTranslatef( -3.37, -6.97, 0 );///glTranslated(teapotX,teapotY,0);
                    glmDraw(hand_right2,GLM_MATERIAL|GLM_TEXTURE);
                glPopMatrix();

                glPushMatrix();///�����H���k�U���u
                    glTranslatef( +4.40, +5.10, 0 );
                    glRotatef(angle[6],0,1,0);///��y�b�����
                    glRotatef(angle2[6],1,0,0);///�h�@�Ө������Y���u��180��
                    glTranslatef( -4.40, -5.10, 0 );///glTranslated(teapotX,teapotY,0);
                    glmDraw(hand_right3,GLM_MATERIAL|GLM_TEXTURE);
                glPopMatrix();



            glPopMatrix();

            glPushMatrix();
                ///glTranslated(teapotX,teapotY,0);///�������H���Y�������������I��m
                glTranslatef( +0.07, +7.60, 0 );///��U������translate���� ���ܭt �t�ܥ�
                glRotatef(angle[7],0,1,0);///��y�b�����
                glRotatef(angle2[7],1,0,0);///�h�@�Ө������Y���u��180��
                glTranslatef( -0.07, -7.60, 0 );
                glmDraw(head, GLM_MATERIAL|GLM_TEXTURE);///�����e�Y
            glPopMatrix();

            glPushMatrix();///�����H���䪺�}
                    ///glTranslated(teapotX,teapotY,0);
                    glTranslatef( -1.40, +3.83, 0 );
                    glRotatef(angle[8],0,1,0);///��y�b�����
                    glRotatef(angle2[8],1,0,0);///�h�@�Ө������Y���u��180��
                    glTranslatef( 1.40, -3.83, 0 );
                    glmDraw(l_leg,GLM_MATERIAL|GLM_TEXTURE);
                glPopMatrix();

                glPushMatrix();///�����H�k�䪺�}
                    ///glTranslated(teapotX,teapotY,0);
                    glTranslatef( +1.40, +3.83, 0 );
                    glRotatef(angle[9],0,1,0);///��y�b�����
                    glRotatef(angle2[9],1,0,0);///�h�@�Ө������Y���u��180��
                    glTranslatef( -1.40, -3.83, 0 );
                    glmDraw(r_leg,GLM_MATERIAL|GLM_TEXTURE);
                glPopMatrix();
        glPopMatrix();

        glColor3f(0,1,0);///����ǯ���
        glutSolidTeapot( 0.02 );

    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(500,500);///���p�µ����ܤj
    glutCreateWindow("week16");


    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);///�ϥ���L�������H�����`�����

    ///robot = glmReadOBJ("model/robot.obj");///Ū�i�@�Ӿ����H��obj��
    head = glmReadOBJ("model/head.obj");///Ū�i�����H���Y
    body = glmReadOBJ("model/body.obj");///Ū�i�����H������
    hand_left1 = glmReadOBJ("model/hand_left1.obj");///�����H���W���u
    hand_right1 = glmReadOBJ("model/hand_right1.obj");///�����H�k�W���u

    hand_left2 = glmReadOBJ("model/hand_left2.obj");///�����H�������u
    hand_right2 = glmReadOBJ("model/hand_right2.obj");///�����H�k�����u

    hand_left3 = glmReadOBJ("model/hand_left3.obj");///�����H���U���u
    hand_right3 = glmReadOBJ("model/hand_right3.obj");///�����H�k�U���u

    l_leg = glmReadOBJ("model/l_leg.obj");///�����H���䪺�}
    r_leg = glmReadOBJ("model/r_leg.obj");///�����H�k�䪺�}

    myTexture("model/diffuso.jpg");///�ǥ�mtTeature��model��Ƨ��̪�jpg��Ū�i��
    glEnable(GL_DEPTH_TEST);///�}��3D�����ե\�� ���K�Ϫ���V��


    glutMainLoop();
}
