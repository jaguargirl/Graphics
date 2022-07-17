#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
using namespace std;
struct MaterialPoint
{
    float x, y, z; //pozitie
    float vx, vy, vz; //viteza
    float ax, ay, az; //acceleratie
    float rx,ry,rz;
};

void moveMe(MaterialPoint *m)
{
    glTranslatef(m->x, m->y, m->z);

    m->vx += m->ax;
    m->vy += m->ay;
    m->vz += m->az;

    m->x += m->vx;
    m->y += m->vy;
    m->z += m->vz;

    glRotatef(m->rx, 1,0,0);
    glRotatef(m->ry, 0,1,0);
    glRotatef(m->rz, 0,0,1);
}

void initGL(int width, int height)
{
    const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    //const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
    const GLfloat light_position[] = { 0.0f, 0.0f, 5.0f, 0.0f };

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_COLOR_MATERIAL);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width/(GLfloat)height,2.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}
void gradient(float redB,float greenB, float blueB,float redT,float greenT, float blueT)
{
    glPushMatrix();
    glTranslatef(0.0f,0.0f,-50.0f);
    glScalef(35,23,1);
    glBegin(GL_QUADS);
    //culoarea de jos
    glColor3f(redB,greenB,blueB);
    glVertex2f(-1.0,-1.0);
    glVertex2f(1.0,-1.0);
    //culoarea de sus
    glColor3f(redT,greenT,blueT);
    glVertex2f(1.0, 1.0);
    glVertex2f(-1.0, 1.0);

    glEnd();
    glPopMatrix();
}
void deseneazaPasare(float x, float y, float z, float red, float green, float blue, MaterialPoint* miscarea, float aripRot, float aripRot1)
{
    //Pasare
    //Corp
    glPushMatrix();
    glColor3f(red,green,blue);
    glTranslatef(x,y,z);
    moveMe(miscarea);
    //glRotatef(axisRot, 0,1,0);
    glTranslatef(0,0.0,0.0);
    glScalef(1.5,1,1);
    glutSolidSphere(0.4,40,40);
    glPopMatrix();

    //Cap
    glPushMatrix();
    glTranslatef(x,y,z);
    moveMe(miscarea);
    //glRotatef(axisRot, 0,1,0);
    glTranslatef(0.85,0.0,0.0);
    glutSolidSphere(0.3,40,40);
    glPopMatrix();

    //Aripa 1
    glPushMatrix();
    glTranslatef(x,y,z);
    moveMe(miscarea);
    //glRotate(axisRot,0,1,0);
    glRotatef(aripRot,1,0,0);
    glTranslatef(0.0,-0.4,0.5);
    glRotatef(120,1,0,0);
    glutSolidCone(0.5,0.2,40,40);
    glPopMatrix();

    //Aripa 2
    glPushMatrix();
    glTranslatef(x,y,z);
    moveMe(miscarea);
    //glRotate(axisRot,0,1,0);
    glRotatef(aripRot1, 1,0,0);
    glTranslatef(0.0,-0.4,-0.5);
    glRotatef(60,1,0,0);
    glutSolidCone(0.5,0.2,40,40);
    glPopMatrix();

    //Coada
    glPushMatrix();
    glTranslatef(x,y,z);
    moveMe(miscarea);
    //glRotatef(axisRot, 0,1,0);
    glTranslatef(-1,0.0,0.0);
    glRotatef(90,0,1,0);
    glScaled(1,0.5,1);
    glutSolidCone(0.3,0.7,40,40);
    glPopMatrix();

    //Ochi 1
    glPushMatrix();
    glColor3f(1.0f,1.0f,1.0f);
    glTranslatef(x,y,z);
    moveMe(miscarea);
    //glRotatef(axisRot, 0,1,0);
    glTranslatef(1.0,0.0,0.2);
    glutSolidSphere(0.1,40,40);
    glPopMatrix();

    //Ochi 2
    glPushMatrix();
    glTranslatef(x,y,z);
    moveMe(miscarea);
    //glRotatef(axisRot, 0,1,0);
    glTranslatef(1.0,0.0,-0.2);
    glutSolidSphere(0.1,40,40);
    glPopMatrix();

    //Cioc pasare
    glColor3f(1.0f,1.0f,0.0f);
    glPushMatrix();
    glTranslatef(x,y,z);
    moveMe(miscarea);
    //glRotatef(axisRot, 0,1,0);
    glTranslatef(1.1,0.0,0.0);
    glRotatef(280,1,0,0);
    glRotatef(90,0,1,0);
    glutSolidCone(0.1,0.3,40,40);
    glPopMatrix();
}
static void
display(void)
{
    static float axisRot = 0.0f;
    static float globRotB = 240.0f;
    static float aripRot = 0.0f;
    static float aripRot1 = 0.0f;
    static int frame,timebase=0;
    int time;
    char s[100];
    frame++;
    time=glutGet(GLUT_ELAPSED_TIME);
    if (time - timebase > 1000)
    {
        sprintf(s,"Proiect");
        glutSetWindowTitle(s);
        timebase = time;
        frame = 0;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity(); //initializarea sistemului de coordonate

    static MaterialPoint *miscare = new MaterialPoint;
    static MaterialPoint *miscNor = new MaterialPoint;
    static MaterialPoint *miscPasare = new MaterialPoint;
    static MaterialPoint *miscNor1 = new MaterialPoint;
    static MaterialPoint *miscSoare = new MaterialPoint;
    static bool initMiscare = true;
    if (initMiscare)
    {
        miscare->vx=0.0001f;

        miscNor->x=0.0f; miscNor->y=0.0f; miscNor->z=0.0f;
        miscNor->vx=0.0f; miscNor->vy=0.0f; miscNor->vz=0.0f;
        miscNor->ax=0.0f; miscNor->ay=0.0f; miscNor->az=0.0f;
        miscNor->vx=0.0001f;

        miscSoare->x=0.0f; miscSoare->y=0.0f; miscSoare->z=0.0f;
        miscSoare->vx=0.0f; miscSoare->vy=0.0f; miscSoare->vz=0.0f;
        miscSoare->ax=0.0f; miscSoare->ay=0.0f; miscSoare->az=0.0f;
        miscSoare->rx=0.0f; miscSoare->ry=0.0f; miscSoare->rz=0.0f;
        miscSoare->rz=-120.0f;

        miscPasare->x=0.0f; miscPasare->y=0.0f; miscPasare->z=0.0f;
        miscPasare->vx=0.0f; miscPasare->vy=0.0f; miscPasare->vz=0.0f;
        miscPasare->ax=0.0f; miscPasare->ay=0.0f; miscPasare->az=0.0f;
        miscPasare->rx=0.0f; miscPasare->ry=0.0f; miscPasare->rz=0.0f;
        miscPasare->x=-1.0f;
        miscPasare->ax=0.000001f;
        initMiscare = false;
    }
    //Sfera
    glPushMatrix();
    glColor3f(0.89f, 0.70f, 0.81f);
    moveMe(miscare);
    glTranslatef(0.0f,0.2f,-3.0f);
    glScalef(1,1.3,1);
    glutSolidSphere(0.4,70,70);
    glPopMatrix();

    //Trapez
    glPushMatrix();
    moveMe(miscare);
    glBegin(GL_TRIANGLES);
    glColor3f(0.89f, 0.70f, 0.81f);
    glVertex3f(-0.32, -0.1, -3.0);
    glVertex3f(-0.15, -0.42, -3.0);
    glVertex3f(0.15, -0.42, -3.0);

    glColor3f(0.89f, 0.70f, 0.81f);
    glVertex3f(0.32, -0.1, -3.0);
    glVertex3f(-0.32, -0.1, -3.0);
    glVertex3f(0.15, -0.42, -3.0);
    glEnd();
    glPopMatrix();

    //Cub
    glPushMatrix();
    glColor3f(0.76f, 0.60f, 0.42f);
    moveMe(miscare);
    glTranslatef(0.0f,-0.85f,-3.0f);
    glutSolidCube(0.35);
    glPopMatrix();

    //Linii
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    moveMe(miscare);
    glTranslatef(-0.14f,-0.42f,-3.0f);
    glRotatef(90,1,0,0);
    glutSolidCylinder(0.01,0.25,40,40);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    moveMe(miscare);
    glTranslatef(0.14f,-0.42f,-3.0f);
    glRotatef(90,1,0,0);
    glutSolidCylinder(0.01,0.25,40,40);
    glPopMatrix();

    //Nor1
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    moveMe(miscNor);
    glTranslatef(-5.5f,5.0f,-23.0f);
    glutSolidSphere(1.3,40,40);
    glPopMatrix();

    glPushMatrix();
    moveMe(miscNor);
    glTranslatef(-6.7f,5.0f,-23.0f);
    glutSolidSphere(1,40,40);
    glPopMatrix();

    glPushMatrix();
    moveMe(miscNor);
    glTranslatef(-6.0f,6.0f,-23.0f);
    glutSolidSphere(1,40,40);
    glPopMatrix();

    //Nor2
    glPushMatrix();
    moveMe(miscNor);
    glTranslatef(-11.5f,-2.0f,-22.0f);
    glutSolidSphere(1.3,40,40);
    glPopMatrix();

    glPushMatrix();
    moveMe(miscNor);
    glTranslatef(-12.7f,-2.0f,-22.0f);
    glutSolidSphere(1,40,40);
    glPopMatrix();

    glPushMatrix();
    moveMe(miscNor);
    glTranslatef(-12.0f,-1.0f,-22.0f);
    glutSolidSphere(1,40,40);
    glPopMatrix();

    //Nor3
    glPushMatrix();
    moveMe(miscNor);
    glTranslatef(5.5f,3.0f,-22.0f);
    glutSolidSphere(1.3,40,40);
    glPopMatrix();

    glPushMatrix();
    moveMe(miscNor);
    glTranslatef(6.7f,3.0f,-22.0f);
    glutSolidSphere(1,40,40);
    glPopMatrix();

    glPushMatrix();
    moveMe(miscNor);
    glTranslatef(6.0f,4.0f,-22.0f);
    glutSolidSphere(1,40,40);
    glPopMatrix();

    //Nor4
    glPushMatrix();
    moveMe(miscNor);
    glScalef(1.3,1,1);
    glTranslatef(0.0f,0.0f,-23.0f);
    glutSolidSphere(1.3,40,40);
    glPopMatrix();

    glPushMatrix();
    moveMe(miscNor);
    glTranslatef(-1.7f,0.0f,-23.0f);
    glutSolidSphere(1,40,40);
    glPopMatrix();

    glPushMatrix();
    moveMe(miscNor);
    glTranslatef(-0.5f,1.0f,-23.0f);
    glutSolidSphere(1.2,40,40);
    glPopMatrix();

    //Nor5
    glPushMatrix();
    moveMe(miscNor);
    glScalef(1.3,1,1);
    glTranslatef(8.0f,-5.0f,-22.0f);
    glutSolidSphere(1.3,40,40);
    glPopMatrix();

    glPushMatrix();
    moveMe(miscNor);
    glTranslatef(8.5f,-5.0f,-22.0f);
    glutSolidSphere(1,40,40);
    glPopMatrix();

    glPushMatrix();
    moveMe(miscNor);
    glTranslatef(9.4f,-4.0f,-22.0f);
    glutSolidSphere(1.2,40,40);
    glPopMatrix();

    //Soare
    glPushMatrix();
    glColor3f(0.92f,0.7f,0.0f);
    glTranslatef(0.0,-5.0,-25.0);
    moveMe(miscSoare);
    glTranslatef(10.0f,7.0f,0.0f);
    /*glRotatef(globRotB, 0,0,1);
    glTranslatef(10.0f,7.0f,0.0f);
    glRotatef(axisRot,0,1,0);*/
    glutSolidSphere(1,40,40);
    glPopMatrix();
    deseneazaPasare(0,5.0,-17.0,0.72,0.8,1.0,miscPasare,aripRot,aripRot1);
    deseneazaPasare(-3,0,-18.0, 0.46, 0.38,1.0, miscPasare,aripRot, aripRot1);
    deseneazaPasare(0,-2.0,-15.0, 0.74, 0.78, 1.0, miscPasare, aripRot, aripRot1);
    if (miscare->x > 1.3f)
    {
        miscare->ax = 0.00f;
        miscare->vx = 0.0f;
        miscare->ay=0.0000001f;
        miscare->x = 1.3f;
    }
    if(miscare->y>0.45f)
    {
        miscare->ay=0.00f;
        miscare->vy=0.00f;
        miscare->ax=-0.0000001f;
        miscare->y = 0.45f;
    }

    if(miscare->x<-1.3f)
    {
        miscare->ax=0.00f;
        miscare->vx=0.0f;
        miscare->ay=-0.0000001f;
        miscare->x = -1.3f;
    }

    if(miscare->y<0.0f)
    {
        miscare->ay=0.00f;
        miscare->vy=0.00f;
        miscare->ax=0.0000001f;
        miscare->y = 0.0f;
    }
    if(miscNor->x>25)
    {
        miscNor->x=-25;
    }
    if(miscPasare->x>7.0)
    {
        miscPasare->ax=-0.0000001f;

    }
    else
        if(miscPasare->x<0)
    {
        miscPasare->ax=0.0000001f;

    }
    if(miscPasare->vx<0)
    {
        miscPasare->ry=180.0f;
    }
    else
    {
        miscPasare->ry=0.0f;
    }
    if((miscSoare->rz<-10&&miscSoare->rz>-60)||(miscSoare->rz<-190&&miscSoare->rz>-230)){
        gradient(1.0,0.0,0.25,0.0,0.0,1.0);
    }
    if(miscSoare->rz<=-60&&miscSoare->rz>=-190){
        glClearColor(0.0f, 0.007f, 0.18f,1.0f);
    }
    if((miscSoare->rz<=-220&&miscSoare->rz>=-360)||(miscSoare->rz<=0&&miscSoare->rz>=-20)){
        glClearColor(0.66f, 0.66f, 0.90f, 0.5f);
    }
    miscSoare->rz-=0.05f;
    miscSoare->rz=fmod(miscSoare->rz,360.0f);
    axisRot -= 1.0f;
    axisRot=fmod(axisRot, 360.0f);
    aripRot -= 1.0f;
    aripRot=fmod(aripRot, 90.0f);
    aripRot1 += 1.0f;
    aripRot1=fmod(aripRot1, 90.0f);
    globRotB -= 0.05f;
    globRotB=fmod(globRotB, 360.0f);

    glutSwapBuffers();
}
static void
idle(void)
{
    glutPostRedisplay();
}
/* Punct de intrare in program */
int
main(int argc, char *argv[])
{
    int width = 1350;
    int height = 900;
    glutInit(&argc, argv);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(5,5);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(""); //titlu vid, il setez in display()
    glClearColor(0.66f, 0.66f, 0.90f, 0.5f);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    initGL(width, height);
    glutMainLoop();
    return EXIT_SUCCESS;
}
