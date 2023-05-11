///week12-5_TRT_keyboard_mouse 要用 keyboard mouse 來操控
#include <stdio.h>
#include <GL/glut.h>
#include "glm.h";///week13 step02-2
///week13_step02-2 再把 glm.cpp 在左邊 Add  files加進
GLMmodel * head = NULL;
GLMmodel * body = NULL;
GLMmodel * upleft_arm = NULL;
GLMmodel * lowleft_arm = NULL;

int show[4] = {1,0,0,0};///week13 step03-1 1代表出現
FILE * fout = NULL; ///step02-2 一開始,檔案沒有開, NULL
FILE * fin = NULL; ///step02-2 要讀檔用的指標, 一開始也是 NULL
float teapotX=0, teapotY=0; ///幫我們看移動值
float angle=0, angle2=0, angle3=0;///step03-2 擺動作
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
        ///glmUnitize(head);///week13 step02-2之後會改

    }
    glPushMatrix();
        glScalef(0.3,0.3,0.3);///week13 step02-3
        glPushMatrix();///week13 step03-2
            glTranslatef( teapotX,teapotY,0 );///week13 step03-2
            if( show[0] ) glmDraw(head, GLM_MATERIAL);///week13 step02-2
        glPopMatrix();///week13 step03-2
        if( show[1] ) glmDraw(body, GLM_MATERIAL);///week13 step02-3
        if( show[2] ) glmDraw(upleft_arm, GLM_MATERIAL);///week13 step02-3
        if( show[3] ) glmDraw(lowleft_arm, GLM_MATERIAL);///week13 step02-3
    glPopMatrix();
    glutSwapBuffers();
}
int oldX=0, oldY=0;///week13 step03-2
void mouse(int button, int state, int x, int y)
{
    if(state==GLUT_DOWN){
            oldX = x;
            oldY = y;
    }
}
void motion( int x,int y )///week13 step03-2
{
    teapotX += ( x - oldX )/150.0;
    teapotY -= ( y - oldY )/150.0;
    oldX = x;
    oldY = y;
    glutPostRedisplay();
}
///void keyboard(unsigned char key, int x, int y) ///step02-2 keyboard函式
///{
    ///if(fin==NULL){ ///step02-2 如果檔案還沒 fopen(), 就開它
        ///fclose(fout); ///前面mouse會開fout指標, 所以要關掉
        ///fin = fopen("file4.txt", "r"); ///step02-2 沒開檔,就開
    ///}
    ///fscanf(fin, "%f %f", &teapotX, &teapotY); ///step02-2 真的讀檔
    ///display(); ///step02-2 重畫畫面
///}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("week13");

    glutMotionFunc(motion);///week13 step03-2
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard); ///step02-2 keyboard要做事囉(開檔、讀檔)

    glutMainLoop();
}
