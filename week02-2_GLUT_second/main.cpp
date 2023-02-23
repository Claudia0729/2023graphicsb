#include <GL/freeglut.h>
void display()
{
    ///glColor3f(0,1,0);///綠色的
    glBegin(GL_POLYGON);///多邊形
        glColor3f(1,0,0); glVertex2f(0,1);///上面 紅色
        glColor3f(0,1,0); glVertex2f(-1,-1);///左下角 黃色
        glColor3f(0,0,1); glVertex2f(1,-1);///右下角 綠色
    glEnd();

    glColor3f(1,1,0);
    glutSolidTeapot( 0.3 );
    glutSwapBuffers();
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

