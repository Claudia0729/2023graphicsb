#include <GL/freeglut.h>
float angle=0; ///�����ܼ� angle ����
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); ///�M�e��

    glutSolidSphere(0.01,30,30);///step01 �p�y������

    glPushMatrix();
        glTranslatef(0.25,0.25,0);///(3)
        glRotatef(angle,0,0,1);///(2)
        glTranslatef(0.45,0,0);///(1)
        glutSolidTeapot(0.3);

    glPopMatrix();

    glutSwapBuffers();
    angle++;///����++
}
int main(int argc,char *argv[])
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("week06");

	glutDisplayFunc(display);
	glutIdleFunc(display); ///���e�e��
	glutMainLoop();
}
