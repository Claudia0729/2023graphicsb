#include <opencv/highgui.h> ///使用 OpenCV 2.1 比較簡單, 只要用 High GUI 即可
#include <opencv/cv.h>
#include <stdio.h>
#include <GL/glut.h>
#include "glm.h"
///改成讀進機器人身體的各部位
GLMmodel * head = NULL;///GLMmodel * robot = NULL;///機器人的空指標
GLMmodel * body = NULL;
GLMmodel * hand_left1 = NULL, * hand_right1 = NULL;///機器人上手臂
GLMmodel * hand_left2 = NULL, * hand_right2 = NULL;///機器人中手臂
GLMmodel * hand_left3 = NULL, * hand_right3 = NULL;///機器人下手臂
GLMmodel * l_leg = NULL, * r_leg = NULL;///機器人的兩隻腳

float teapotX = 0, teapotY = 0, oldX = 0, oldY = 0;
float angle[20] = {}, angle2[20] = {};///原本是float angle = 0, angle2=0
float NewAngle[20] = {}, NewAngle2[20] = {};
float OldAngle[20] = {}, OldAngle2[20] = {};
int ID = 0;///ID會判斷鍵盤按到是哪一個關節要動
FILE * fout = NULL;///寫檔案
FILE * fin = NULL;///讀檔案


void timer(int t)
{
    printf("現在timer(%d)\n", t);
    glutTimerFunc(20,timer,t+1);///馬上設定下個鬧鐘

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
void keyboard(unsigned char key, int x, int y)///鍵盤控制的函式
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
    if ( key=='s' ) {///SAVE存檔,會動到motion檔案
        if (fout == NULL) fout = fopen("motion.txt","w");
        for(int i=0; i<20; i++)
        {
            fprintf(fout, "%.2f", angle[i]);
            fprintf(fout,"%.2f", angle2[i]);
        }
        fprintf(fout,"\n");
        printf("寫了一行");
    }
    if (key=='r'){///read 讀檔會,動到motion檔案
        if(fin == NULL) fin = fopen("motion.txt", "r");
        for(int i=0;i<20;i++){
            fscanf(fin, "%f", &angle[i]);
            fscanf(fin, "%f", &angle2[i]);
        }
        glutPostRedisplay();
    }
    if (key=='p'){///play播放 會動到motion檔案
        glutTimerFunc(0,timer,0);
    }
}
int myTexture(char * filename)///貼圖
{
    IplImage * img = cvLoadImage(filename); ///OpenCV讀圖
    cvCvtColor(img,img, CV_BGR2RGB); ///OpenCV轉色彩 (需要cv.h)
    glEnable(GL_TEXTURE_2D); ///1. 開啟貼圖功能
    GLuint id; ///準備一個 unsigned int 整數, 叫 貼圖ID
    glGenTextures(1, &id); /// 產生Generate 貼圖ID
    glBindTexture(GL_TEXTURE_2D, id); ///綁定bind 貼圖ID
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖T, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖S, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /// 貼圖參數, 放大時的內插, 用最近點
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /// 貼圖參數, 縮小時的內插, 用最近點
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->imageData);
    return id;
}
void mouse(int button, int state, int x, int y) {
    oldX = x;
    oldY = y;
}
void motion(int x, int y) {///150*5讓頭的移動速度變快
    teapotX += (x-oldX) / 150.0*5;///teapotX = (x-150)/150.0;
    teapotY += (oldY-y) / 150.0*5;///teapotY = (150-y)/150.0;
    angle[ID] += x - oldX;
    angle2[ID] += oldY - y;///第二個旋轉的角度可能跟y軸有關係
    oldX = x;
    oldY = y;
    glutPostRedisplay();
    printf("  glTranslatef( %.2f, %.2f, 0 ); \n", teapotX, teapotY );
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glScalef(1.5,1.5,1.5);///機器人的頭和身體再放大一點
        glTranslatef(0,-0.5,0);///往下一半(下是-0.5)
        glPushMatrix();
            glColor3f(1,1,1);///機器人整體顏色///要把機器人顏色改為白色 就可以看到貼圖了
            glScalef(0.1,0.1,0.1);///機器人的大小
            glRotatef(angle[0],0,1,0);///機器人對著y軸方向旋轉///身體的轉動
            ///glmDraw(robot, GLM_MATERIAL|GLM_TEXTURE);///加上texture功能 機器人可以更清楚呈現
            glmDraw(body, GLM_MATERIAL|GLM_TEXTURE);///換成畫身體

            glPushMatrix();///機器人的左上手臂
                glTranslatef( -2.07, +7.87, 0 );
                glRotatef(angle[1],0,1,0);///對y軸做轉動
                glRotatef(angle2[1],1,0,0);///多一個角度讓頭不只轉180度
                glTranslatef( 2.07, -7.87, 0 );///glTranslated(teapotX,teapotY,0);
                glmDraw(hand_left1,GLM_MATERIAL|GLM_TEXTURE);

                glPushMatrix();///機器人的左中臂
                    glTranslatef( -3.37, +6.97, 0 );
                    glRotatef(angle[2],0,1,0);///對y軸做轉動
                    glRotatef(angle2[2],1,0,0);///多一個角度讓頭不只轉180度
                    glTranslatef( 3.37, -6.97, 0 );///glTranslated(teapotX,teapotY,0);
                    glmDraw(hand_left2,GLM_MATERIAL|GLM_TEXTURE);
                glPopMatrix();

                glPushMatrix();///機器人的左下手臂
                    glTranslatef( -4.40, +5.10, 0 );
                    glRotatef(angle[3],0,1,0);///對y軸做轉動
                    glRotatef(angle2[3],1,0,0);///多一個角度讓頭不只轉180度
                    glTranslatef( 4.40, -5.10, 0 );///glTranslated(teapotX,teapotY,0);
                    glmDraw(hand_left3,GLM_MATERIAL|GLM_TEXTURE);
                glPopMatrix();

            glPopMatrix();


            glPushMatrix();///機器人的右上手臂
                glTranslatef( +2.07, +7.87, 0 );
                glRotatef(angle[4],0,1,0);///對y軸做轉動
                glRotatef(angle2[4],1,0,0);///多一個角度讓頭不只轉180度
                glTranslatef( -2.07, -7.87, 0 );///glTranslated(teapotX,teapotY,0);
                glmDraw(hand_right1,GLM_MATERIAL|GLM_TEXTURE);

                glPushMatrix();///機器人的右中臂
                    glTranslatef( +3.37, +6.97, 0 );
                    glRotatef(angle[5],0,1,0);///對y軸做轉動
                    glRotatef(angle2[5],1,0,0);///多一個角度讓頭不只轉180度
                    glTranslatef( -3.37, -6.97, 0 );///glTranslated(teapotX,teapotY,0);
                    glmDraw(hand_right2,GLM_MATERIAL|GLM_TEXTURE);
                glPopMatrix();

                glPushMatrix();///機器人的右下手臂
                    glTranslatef( +4.40, +5.10, 0 );
                    glRotatef(angle[6],0,1,0);///對y軸做轉動
                    glRotatef(angle2[6],1,0,0);///多一個角度讓頭不只轉180度
                    glTranslatef( -4.40, -5.10, 0 );///glTranslated(teapotX,teapotY,0);
                    glmDraw(hand_right3,GLM_MATERIAL|GLM_TEXTURE);
                glPopMatrix();



            glPopMatrix();

            glPushMatrix();
                ///glTranslated(teapotX,teapotY,0);///讓機器人的頭放到綠色茶壺中心點位置
                glTranslatef( +0.07, +7.60, 0 );///把下面那個translate的值 正變負 負變正
                glRotatef(angle[7],0,1,0);///對y軸做轉動
                glRotatef(angle2[7],1,0,0);///多一個角度讓頭不只轉180度
                glTranslatef( -0.07, -7.60, 0 );
                glmDraw(head, GLM_MATERIAL|GLM_TEXTURE);///換成畫頭
            glPopMatrix();

            glPushMatrix();///機器人左邊的腳
                    ///glTranslated(teapotX,teapotY,0);
                    glTranslatef( -1.40, +3.83, 0 );
                    glRotatef(angle[8],0,1,0);///對y軸做轉動
                    glRotatef(angle2[8],1,0,0);///多一個角度讓頭不只轉180度
                    glTranslatef( 1.40, -3.83, 0 );
                    glmDraw(l_leg,GLM_MATERIAL|GLM_TEXTURE);
                glPopMatrix();

                glPushMatrix();///機器人右邊的腳
                    ///glTranslated(teapotX,teapotY,0);
                    glTranslatef( +1.40, +3.83, 0 );
                    glRotatef(angle[9],0,1,0);///對y軸做轉動
                    glRotatef(angle2[9],1,0,0);///多一個角度讓頭不只轉180度
                    glTranslatef( -1.40, -3.83, 0 );
                    glmDraw(r_leg,GLM_MATERIAL|GLM_TEXTURE);
                glPopMatrix();
        glPopMatrix();

        glColor3f(0,1,0);///綠色基準茶壺
        glutSolidTeapot( 0.02 );

    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(500,500);///讓小黑視窗變大
    glutCreateWindow("week16");


    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);///使用鍵盤讓機器人的關節做轉動

    ///robot = glmReadOBJ("model/robot.obj");///讀進一個機器人的obj檔
    head = glmReadOBJ("model/head.obj");///讀進機器人的頭
    body = glmReadOBJ("model/body.obj");///讀進機器人的身體
    hand_left1 = glmReadOBJ("model/hand_left1.obj");///機器人左上手臂
    hand_right1 = glmReadOBJ("model/hand_right1.obj");///機器人右上手臂

    hand_left2 = glmReadOBJ("model/hand_left2.obj");///機器人左中手臂
    hand_right2 = glmReadOBJ("model/hand_right2.obj");///機器人右中手臂

    hand_left3 = glmReadOBJ("model/hand_left3.obj");///機器人左下手臂
    hand_right3 = glmReadOBJ("model/hand_right3.obj");///機器人右下手臂

    l_leg = glmReadOBJ("model/l_leg.obj");///機器人左邊的腳
    r_leg = glmReadOBJ("model/r_leg.obj");///機器人右邊的腳

    myTexture("model/diffuso.jpg");///藉由mtTeature把model資料夾裡的jpg檔讀進來
    glEnable(GL_DEPTH_TEST);///開啟3D的測試功能 讓貼圖的方向更正


    glutMainLoop();
}
