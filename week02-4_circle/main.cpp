#include <GL/freeglut.h>
#include <math.h>
void myCircle(float r, float x, float y)
{

    glBegin(GL_POLYGON);
    for (float a=0;a<=2*3.144592;a+=0.01)
    {
        glVertex2f(r*cos(a)+x,r*sin(a)+y);
    }

    glEnd();


}
void display()
{
    glColor3f(233/255.0,141/255.0,128/255.0);
    myCircle(0.5,0,0);

    glColor3f(1,1,0);
    myCircle(0.3,0.5,0.5);

    glColor3f(1,0,0);
    myCircle(0.3,-0.5,0.5);

    glColor3f(0,1,0);
    myCircle(0.3,-0.5,-0.5);

    glColor3f(0,0,1);
    myCircle(0.3,0.5,-0.5);

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
