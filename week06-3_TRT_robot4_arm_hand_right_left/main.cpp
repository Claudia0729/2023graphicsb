#include <GL/freeglut.h>
float angle=0; ///办跑计 angle à
void myCube()///step02-1ㄧΑ
{
    glPushMatrix();
        glScalef(1,0.3,0.3);
        glutSolidCube(0.5);///0.5よ遏

    glPopMatrix();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); ///睲礶

    glutSolidSphere(0.01,30,30);///step01 瞴暗いみ

    glPushMatrix();///娩
        glTranslatef(0.25,0,0);///(3)∕﹚璶рもぐ或竚
        glRotatef(angle,0,0,1);///(2)
        glTranslatef(0.25,0,0);///(1)
        myCube();///も羥
        glPushMatrix();
            glTranslatef(0.25,0,0);///(3)∕﹚璶рもぐ或竚
            glRotatef(angle,0,0,1);///(2)
            glTranslatef(0.25,0,0);///(1)
            myCube();///も▂
        glPopMatrix();
    glPopMatrix();


    glPushMatrix();///オ娩
        glTranslatef(-0.25,0,0);///(3)∕﹚璶рもぐ或竚
        glRotatef(angle,0,0,1);///(2)
        glTranslatef(-0.25,0,0);///(1)
        myCube();///も羥
        glPushMatrix();
            glTranslatef(-0.25,0,0);///(3)∕﹚璶рもぐ或竚
            glRotatef(angle,0,0,1);///(2)
            glTranslatef(-0.25,0,0);///(1)
            myCube();///も▂
        glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
    angle++;///à++
}
int main(int argc,char *argv[])
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("week06");

	glutDisplayFunc(display);
	glutIdleFunc(display); ///礶礶
	glutMainLoop();
}
