
#include <GL/freeglut.h>
void display()
{
    ///小畫家幫我們寫程式 除 255.0 就好
    glColor3f(233/255.0,141/255.0,128/255.0);
    ///顏色不可以超過不可以
    glBegin(GL_POLYGON);///多邊形
        glVertex2f((65-100)/100.0,-(54-100)/100.0);
        glVertex2f((34-100)/100.0,-(138-100)/100.0);
        glVertex2f((59-100)/100.0,-(138-100)/100.0);
        glVertex2f((87-100)/100.0,-(53-100)/100.0);
        ///先減一半 再除一半 y變負號
    glEnd();



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

