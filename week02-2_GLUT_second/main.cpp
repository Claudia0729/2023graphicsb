#include <GL/freeglut.h>
void display()
{
    ///glColor3f(0,1,0);///��⪺
    glBegin(GL_POLYGON);///�h���
        glColor3f(1,0,0); glVertex2f(0,1);///�W�� ����
        glColor3f(0,1,0); glVertex2f(-1,-1);///���U�� ����
        glColor3f(0,0,1); glVertex2f(1,-1);///�k�U�� ���
    glEnd();

    glColor3f(1,1,0);
    glutSolidTeapot( 0.3 );
    glutSwapBuffers();
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    ///�n�]�w GLUT ����ܼҦ�
    glutCreateWindow("week02");///�n�ؤ@�ӵ��r�A�� "..."
    glutDisplayFunc(display);///�n��ܪ��禡 DISPLAY()
    glutMainLoop();///�̫��main�j�� ���b�̫᭱


}

