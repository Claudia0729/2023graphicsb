
#include <GL/freeglut.h>
void display()
{
    ///�p�e�a���ڭ̼g�{�� �� 255.0 �N�n
    glColor3f(233/255.0,141/255.0,128/255.0);
    ///�C�⤣�i�H�W�L���i�H
    glBegin(GL_POLYGON);///�h���
        glVertex2f((65-100)/100.0,-(54-100)/100.0);
        glVertex2f((34-100)/100.0,-(138-100)/100.0);
        glVertex2f((59-100)/100.0,-(138-100)/100.0);
        glVertex2f((87-100)/100.0,-(53-100)/100.0);
        ///����@�b �A���@�b y�ܭt��
    glEnd();



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

