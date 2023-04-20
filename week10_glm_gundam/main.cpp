///Week08-2_glm_model_texture

///把範例全刪,貼上 Week08-1_glm_model

///再結合上週的 myTexture的(部分)程式

///記得再裝 opencv2.1, 再配上週的3個咒語 目錄、目錄、cv210 cxcore210 highgui210

#include <opencv/highgui.h> ///使用 OpenCV 2.1 比較簡單, 只要用 High GUI 即可

#include <opencv/cv.h>

#include <GL/glut.h>

int myTexture(char * filename)

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

#include "glm.h" ///step02-1 把 source.zip裡的 glm.h 放在同目錄中

///step03-1也要把step02-1的 glm.h也準備好

///glm.cpp 也要加到你的程式目錄裡

GLMmodel * pmodel = NULL; ///step02-1 模型的指標,一開始NULL空的


float angle=0;

void display()

{

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);



    ///step03-1執行前,確認Gundam.obj Gundam.mtl 都在freeglut的bin

    if(pmodel==NULL){ ///第一次會進來 step02-1

        pmodel = glmReadOBJ("hand_left.obj");///檔名照你的檔名 step02-1

        glmUnitize(phand);///step02-2 縮放成Unit單位大小(-1..+1)

        glmFacetNormals(phand);///step03-1

        glmVertexNormals(phand, 90);///step03-1

    }

    glutSolidSphere(0.1,30,30);///畫面正中心在這
    glPushMatrix();

        glRotatef(angle, 0,1,0);
        glTranslatedf(0,-0.1,0);///把手的旋轉中心 放到畫面正中心
        glmDraw(phand, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE); ///step02-1

    glPopMatrix();



    ///glutSolidTeapot( 0.3 );

    angle++;

    glutSwapBuffers();

}

int main(int argc, char**argv)

{

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);

    glutCreateWindow("week08");



    myTexture("Diffuse.jpg");///step03-2圖檔也是放freeglut的bin

    glEnable(GL_DEPTH_TEST);///下週再教3D的glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);

    glutIdleFunc(display);

    glutMainLoop();

}
