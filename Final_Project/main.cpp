///week12-5_TRT_keyboard_mouse �n�� keyboard mouse �Ӿޱ�
#include <stdio.h>
#include <GL/glut.h>
#include "glm.h";///week13 step02-2
///week13_step02-2 �A�� glm.cpp �b���� Add  files�[�i
GLMmodel * head = NULL;
GLMmodel * body = NULL;
GLMmodel * upleft_arm = NULL;
GLMmodel * lowleft_arm = NULL;

int show[4] = {1,0,0,0};///week13 step03-1 1�N��X�{
FILE * fout = NULL; ///step02-2 �@�}�l,�ɮרS���}, NULL
FILE * fin = NULL; ///step02-2 �nŪ�ɥΪ�����, �@�}�l�]�O NULL
float teapotX=0, teapotY=0; ///���ڭ̬ݲ��ʭ�
float angle=0, angle2=0, angle3=0;///step03-2 �\�ʧ@
void keyboard(unsigned char key, int x, int y )
{
    if ( key=='0' ) show[0] =! show[0];///week13 step03-1
    if ( key=='1' ) show[1] =! show[1];///week13 step03-1
    if ( key=='2' ) show[2] =! show[2];///week13 step03-1
    if ( key=='3' ) show[3] =! show[3];///week13 step03-1
    glutPostRedisplay();///week13 step03-1
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    if ( head==NULL )///week13 step02-2
    {
        head = glmReadOBJ("model/head.obj");///week13 step02-2
        body = glmReadOBJ("model/body.obj");
        upleft_arm = glmReadOBJ("model/upleft_arm.obj");
        lowleft_arm = glmReadOBJ("model/lowleft_arm.obj");
        ///glmUnitize(head);///week13 step02-2����|��

    }
    glPushMatrix();
        glScalef(0.3,0.3,0.3);///week13 step02-3
        if( show[0] ) glmDraw(head, GLM_MATERIAL);///week13 step02-2
        if( show[1] ) glmDraw(body, GLM_MATERIAL);///week13 step02-3
        if( show[2] ) glmDraw(upleft_arm, GLM_MATERIAL);///week13 step02-3
        if( show[3] ) glmDraw(lowleft_arm, GLM_MATERIAL);///week13 step02-3
    glPopMatrix();
    glutSwapBuffers();
}
void mouse(int button, int state, int x, int y)
{
    if(state==GLUT_DOWN){
        teapotX = (x-150)/150.0;
        teapotY = (150-y)/150.0;
        angle = x;
        printf("glTranslatef(%f, %f, 0);\n", teapotX, teapotY);
        if(fout==NULL) fout = fopen("file4.txt", "w"); ///step02-2 �S�}��,�N�}
        ///fprintf(fout, "%f %f\n", teapotX, teapotY); ///step02-2 �n�A�s�y��
    }
    display();
}
///void keyboard(unsigned char key, int x, int y) ///step02-2 keyboard�禡
///{
    ///if(fin==NULL){ ///step02-2 �p�G�ɮ��٨S fopen(), �N�}��
        ///fclose(fout); ///�e��mouse�|�}fout����, �ҥH�n����
        ///fin = fopen("file4.txt", "r"); ///step02-2 �S�}��,�N�}
    ///}
    ///fscanf(fin, "%f %f", &teapotX, &teapotY); ///step02-2 �u��Ū��
    ///display(); ///step02-2 ���e�e��
///}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("week13");

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard); ///step02-2 keyboard�n�����o(�}�ɡBŪ��)

    glutMainLoop();
}
