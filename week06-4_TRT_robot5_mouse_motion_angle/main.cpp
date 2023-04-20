
#include <GL/freeglut.h>
float angle=0; ///�����ܼ� angle ����
void myCube()///step02-1�禡
{
    glPushMatrix();
        glScalef(1,0.3,0.3);
        glutSolidCube(0.5);///�j�p��0.5�����

    glPopMatrix();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); ///�M�e��

    glutSolidSphere(0.01,30,30);///step01 �p�y������

    glPushMatrix();///�k�䪺
        glTranslatef(0.25,0,0);///(3)�M�w�n����b�����m�W
        glRotatef(angle,0,0,1);///(2)
        glTranslatef(0.25,0,0);///(1)
        myCube();///�W���u
        glPushMatrix();
            glTranslatef(0.25,0,0);///(3)�M�w�n����b�����m�W
            glRotatef(angle,0,0,1);///(2)
            glTranslatef(0.25,0,0);///(1)
            myCube();///�U��y
        glPopMatrix();
    glPopMatrix();


    glPushMatrix();///���䪺
        glTranslatef(-0.25,0,0);///(3)�M�w�n����b�����m�W
        glRotatef(-angle,0,0,1);///(2)
        glTranslatef(-0.25,0,0);///(1)
        myCube();///�W���u
        glPushMatrix();
            glTranslatef(-0.25,0,0);///(3)�M�w�n����b�����m�W
            glRotatef(-angle,0,0,1);///(2)
            glTranslatef(-0.25,0,0);///(1)
            myCube();///�U��y
        glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
    ///angle++;///����++
}
void motion(int x, int y)
{///step03-1 �s�[�� mouse motion
    angle = x;
}
int main(int argc,char *argv[])
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("week06");

    glutMotionFunc(motion);///step03-1 �s�[�� mouse motion
	glutDisplayFunc(display);
	glutIdleFunc(display); ///���e�e��
	glutMainLoop();
}