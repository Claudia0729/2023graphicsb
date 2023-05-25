#include <GL/glut.h>
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glutSolidTeapot(0.3);
    glutSwapBuffers();

}
void motion(int x,int y)
{
    glLoadIdentity();
    float eyeX = (x-150)/150.0, eyeY = (150-y)/150.0;
    gluLookAt(eyeX,eyeY,1,   0,0,0,   0,1,0);
    glutPostRedisplay();
}
void reshape(int w, int h)///step03-2
{
    float ar = w / (float) h;///step03-2
    glViewport(0,0,w,h);///step03-2

    glMatrixMode(GL_PROJECTION);///step03-2透視投影
    glLoadIdentity();///step03-2
    gluPerspective(60,ar, 0.01,1000 );///step03-2 y方向60度 長寬比 近  遠

    glMatrixMode(GL_MODELVIEW);///step03-2
    glLoadIdentity();///step03-2
    gluLookAt(0,0,1,   0,0,0,   0,1,0);///step03-2

}
int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow("week15");

    glutReshapeFunc(reshape);///step03-2
    glutMotionFunc(motion);///step03-1
    glutDisplayFunc(display);

    glutMainLoop();
}
