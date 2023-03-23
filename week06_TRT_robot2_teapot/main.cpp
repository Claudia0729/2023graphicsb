#include <GL/freeglut.h>
float angle=0; ///全域變數 angle 角度
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); ///清畫面

    glutSolidSphere(0.01,30,30);///step01 小球做中心

    glPushMatrix();
        glTranslatef(0.25,0.25,0);///(3)
        glRotatef(angle,0,0,1);///(2)
        glTranslatef(0.45,0,0);///(1)
        glutSolidTeapot(0.3);

    glPopMatrix();

    glutSwapBuffers();
    angle++;///角度++
}
int main(int argc,char *argv[])
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("week06");

	glutDisplayFunc(display);
	glutIdleFunc(display); ///重畫畫面
	glutMainLoop();
}
