
#include <GL/glut.h>
void display()
{
    glColor3f(1,1,0);///step01-2��m ����
    glutSolidTeapot( 0.5 );///�e�X��ߤp����
    glColor3f(0,1,0);///step01-2��m ����
    glutSolidTeapot( 0.3 );///�e�X��ߤp����

    glutSwapBuffers();///�洫��ܥX��
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
