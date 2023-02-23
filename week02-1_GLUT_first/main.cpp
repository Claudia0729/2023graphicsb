
#include <GL/glut.h>
void display()
{
    glColor3f(1,1,0);///step01-2色彩 黃色
    glutSolidTeapot( 0.5 );///畫出實心小茶壺
    glColor3f(0,1,0);///step01-2色彩 黃色
    glutSolidTeapot( 0.3 );///畫出實心小茶壺

    glutSwapBuffers();///交換顯示出來
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    ///要設定 GLUT 的顯示模式
    glutCreateWindow("week02");///要建一個窗字，較 "..."
    glutDisplayFunc(display);///要顯示的函式 DISPLAY()
    glutMainLoop();///最後用main迴圈 壓在最後面


}
