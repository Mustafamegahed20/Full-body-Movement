#include <stdlib.h>
#include <C:\glut\include\GL\glut.h>
#include<math.h>
#define PI 3.14

double eye[] = { 0.0, 0.0, 5.0 };
double center[] = { 0.0, 0.0, 0.0 };
double up[] = { 0.0, 1.0, 0.0 };

int moving, startx, starty;

GLfloat angle1 = 0.0;   /* in degrees */
GLfloat angle2 = 0.0;   /* in degrees */


static int arm[] = { 0, 0 };
static int arm2[] = { 0, 0 };
static int arm3[] = { 0, 0 };
static int leg1[] = { 0, 0 };
static int leg2[] = { 0, 0 };
static int knee[] = { 0, 0 };
static int elbow[] = { 0, 0 };
static int fingers[] = { 0, 0 };
static int flang[] = { 0, 0 };

void rotatePoint(double a[], double theta, double p[])
{

    double temp[3];
    temp[0] = p[0];
    temp[1] = p[1];
    temp[2] = p[2];

    temp[0] = -a[2] * p[1] + a[1] * p[2];
    temp[1] = a[2] * p[0] - a[0] * p[2];
    temp[2] = -a[1] * p[0] + a[0] * p[1];

    temp[0] *= sin(theta);
    temp[1] *= sin(theta);
    temp[2] *= sin(theta);

    temp[0] += (1 - cos(theta)) * (a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
    temp[1] += (1 - cos(theta)) * (a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
    temp[2] += (1 - cos(theta)) * (a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

    temp[0] += cos(theta) * p[0];
    temp[1] += cos(theta) * p[1];
    temp[2] += cos(theta) * p[2];

    p[0] = temp[0];
    p[1] = temp[1];
    p[2] = temp[2];
}
void crossProduct(double a[], double b[], double c[])
{
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(double a[])
{
    double norm;
    norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
    norm = sqrt(norm);
    a[0] /= norm;
    a[1] /= norm;
    a[2] /= norm;
}
void lookRight()
{
    rotatePoint(up, PI / 8, eye);
}

void lookLeft()
{
    rotatePoint(up, -PI / 8, eye);
}

void lookUp()
{
    double horizontal[3];
    double look[] = { center[0] - eye[0], center[1] - eye[1], center[2] - eye[2] };
    crossProduct(up, look, horizontal);
    normalize(horizontal);
    rotatePoint(horizontal, PI / 8, eye);
    rotatePoint(horizontal, PI / 8, up);
}

void lookDown()
{
    double horizontal[3];
    double look[] = { center[0] - eye[0], center[1] - eye[1], center[2] - eye[2] };
    crossProduct(up, look, horizontal);
    normalize(horizontal);
    rotatePoint(horizontal, -PI / 8, eye);
    rotatePoint(horizontal, -PI / 8, up);
}

void moveForward()
{
    double direction[3];
    direction[0] = center[0] - eye[0];
    direction[1] = center[1] - eye[1];
    direction[2] = center[2] - eye[2];
    float speed = 0.1;
    eye[0] += direction[0] * speed;
    eye[1] += direction[1] * speed;
    eye[2] += direction[2] * speed;

    center[0] += direction[0] * speed;
    center[1] += direction[1] * speed;
    center[2] += direction[2] * speed;
}

void moveBackword()
{
    double direction[3];
    direction[0] = center[0] - eye[0];
    direction[1] = center[1] - eye[1];
    direction[2] = center[2] - eye[2];
    float speed = 0.1;
    eye[0] -= direction[0] * speed;
    eye[1] -= direction[1] * speed;
    eye[2] -= direction[2] * speed;

    center[0] -= direction[0] * speed;
    center[1] -= direction[1] * speed;
    center[2] -= direction[2] * speed;


}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(60.0,
        1.0,
        1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}
void reset()
{
    double e[] = { 0.0, 0.0, 5.0 };
    double c[] = { 0.0, 0.0, 0.0 };
    double u[] = { 0.0, 1.0, 0.0 };
    for (int i = 0; i < 3; i++)
    {
        eye[i] = e[i];
        center[i] = c[i];
        up[i] = u[i];
    }
}
void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        lookLeft();
        break;
    case GLUT_KEY_RIGHT:
        lookRight();
        break;
    case GLUT_KEY_UP:
        lookUp();
        break;
    case GLUT_KEY_DOWN:
        lookDown();
        break;
    }
    glutPostRedisplay();
}


void display(void) {

    //camera movement
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2],
        center[0], center[1], center[2],
        up[0], up[1], up[2]);

    ////

    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle1, 0.0, 1.0, 0.0);


    // START OF HEAD
    glPushMatrix();
    glTranslatef(0.0, 2.95, 0.0);
    glutWireSphere(0.26, 16, 16);
    glPopMatrix();
    // END OF HEAD

    // START OF STOMACH
    glPushMatrix();
    glTranslatef(0.0, 1.25, 0.0);
    glScalef(1, 2.5, 0.3);
    glutWireCube(1.0);
    glPopMatrix();
    // END OF STOMACH

     // START OF LEFT LEG
    glPushMatrix();

    glTranslatef(-0.3, 0.0, 0.0);
    glRotatef((GLfloat)leg1[1], 1.0, 0.0, 0.0);
    glRotatef((GLfloat)leg2[1], 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.73, 0.0);


    //glTranslatef(0.0, -0.73, 0.0);

    glPushMatrix();
    glScalef(0.4, 1.5, 0.3);
    glutWireCube(1.0);
    glPopMatrix();


    glTranslatef(0.3, -0.73, 0.0);
    glRotatef(GLfloat(knee[1]), 1.0, 0.0, 0.0);
    glTranslatef(-0.3, -0.5, 0.0);
    glPushMatrix();
    glScalef(0.4, 1.0, 0.3);
    glutWireCube(1.0);
    glPopMatrix();

    glTranslatef(0.0, -0.625, 0.0);
    glPushMatrix();
    glScalef(0.4, 0.25, 0.75);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();
    // END OF LEFT LEG



     // START OF RIGHT LEG
    glPushMatrix();

    glTranslatef(0.3, 0.0, 0.0);
    glRotatef((GLfloat)leg1[0], 1.0, 0.0, 0.0);
    glRotatef((GLfloat)leg2[0], 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.73, 0.0);


    //glTranslatef(-0.5, -0.5, 0.0);

    glPushMatrix();
    glScalef(0.4, 1.5, 0.3);
    glutWireCube(1.0);
    glPopMatrix();


    glTranslatef(0.3, -0.73, 0.0);
    glRotatef(GLfloat(knee[0]), 1.0, 0.0, 0.0);
    glTranslatef(-0.3, -0.5, 0.0);


    glPushMatrix();
    glScalef(0.4, 1.0, 0.3);
    glutWireCube(1.0);
    glPopMatrix();

    glTranslatef(0.0, -0.625, 0.0);
    glPushMatrix();
    glScalef(0.4, 0.25, 0.75);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();
    // END OF RIGHT LEG

    //START OF RIGHT ARM
    glPushMatrix();



    glTranslatef(0.7, 2.3, 0.0);
    glRotatef((GLfloat)arm2[0], 1.0, 0.0, 0.0);
    glRotatef(arm[0], 0.0, 0.0, 1.0);
    glRotatef(arm3[0], 0.0, 1.0, 0.0);
    glTranslatef(0.0, -0.35, 0.0);



    glPushMatrix();
    glScalef(0.2, 0.8, 0.3);
    glutWireCube(1.0);
    glPopMatrix();




    //glTranslatef(0.38, -0.8, 0.0);

    glTranslatef(-1, -0.4, 0.0);
    glRotatef((GLfloat)elbow[0], 1.0, 0.0, 0.0);
    glTranslatef(1, -0.4, 0.0);


    glPushMatrix();
    glScalef(0.2, 0.8, 0.3);
    glutWireCube(1.0);
    glPopMatrix();

    // START OF FINGER 1
    glPushMatrix();

    glTranslatef(0.05, -0.5, 0.125);


    glTranslatef(0.1, 0, 0);
    glRotatef(flang[0], 0, 0, 1);
    glTranslatef(-0.1, 0, 0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.03);
    glutWireCube(1.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.0, -0.2, 0);
    glTranslatef(0.05, 0, 0);
    glRotatef(fingers[0], 0, 0, 1);
    glTranslatef(-0.05, 0, 0);
    glScalef(0.08, 0.2, 0.03);
    glutWireCube(1.0);
    glPopMatrix();

    glPopMatrix();

    //// END OF FINGER 1

    // START OF FINGER 2
    glPushMatrix();

    glTranslatef(0.05, -0.5, 0.045);


    glTranslatef(0.1, 0, 0);
    glRotatef(flang[0], 0, 0, 1);
    glTranslatef(-0.1, 0, 0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.03);
    glutWireCube(1.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.0, -0.2, 0);
    glTranslatef(0.05, 0, 0);
    glRotatef(fingers[0], 0, 0, 1);
    glTranslatef(-0.05, 0, 0);
    glScalef(0.08, 0.2, 0.03);
    glutWireCube(1.0);
    glPopMatrix();

    glPopMatrix();

    //// END OF FINGER 2

    // START OF FINGER 3
    glPushMatrix();

    glTranslatef(0.05, -0.5, -0.045);


    glTranslatef(0.1, 0, 0);
    glRotatef(flang[0], 0, 0, 1);
    glTranslatef(-0.1, 0, 0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.03);
    glutWireCube(1.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.0, -0.2, 0);
    glTranslatef(0.05, 0, 0);
    glRotatef(fingers[0], 0, 0, 1);
    glTranslatef(-0.05, 0, 0);
    glScalef(0.08, 0.2, 0.03);
    glutWireCube(1.0);
    glPopMatrix();

    glPopMatrix();

    //// END OF FINGER 3

    // START OF FINGER 4
    glPushMatrix();

    glTranslatef(0.05, -0.5, -0.125);


    glTranslatef(0.1, 0, 0);
    glRotatef(flang[0], 0, 0, 1);
    glTranslatef(-0.1, 0, 0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.03);
    glutWireCube(1.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.0, -0.2, 0);
    glTranslatef(0.05, 0, 0);
    glRotatef(fingers[0], 0, 0, 1);
    glTranslatef(-0.05, 0, 0);
    glScalef(0.08, 0.2, 0.03);
    glutWireCube(1.0);
    glPopMatrix();

    glPopMatrix();

    //// END OF FINGER 4

    // START OF FINGER 5
    glPushMatrix();

    glTranslatef(-0.05, -0.5, 0);


    glTranslatef(0.1, 0, 0);
    glRotatef(-flang[0], 0, 0, 1);
    glTranslatef(-0.1, 0, 0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.03);
    glutWireCube(1.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.0, -0.2, 0);
    glTranslatef(0.05, 0, 0);
    glRotatef(-fingers[0], 0, 0, 1);
    glTranslatef(-0.05, 0, 0);
    glScalef(0.08, 0.2, 0.03);
    glutWireCube(1.0);
    glPopMatrix();

    glPopMatrix();
    //// END OF FINGER 5


    glPopMatrix();

    // END OF RIGHT ARM

    //START OF LEFT ARM

    glPushMatrix();



    glTranslatef(-0.7, 2.3, 0.0);
    glRotatef((GLfloat)arm2[1], 1.0, 0.0, 0.0);
    glRotatef(arm[1], 0.0, 0.0, 1.0);
    glRotatef(arm3[1], 0.0, 1.0, 0.0);
    glTranslatef(0.0, -0.35, 0.0);

    glPushMatrix();
    glScalef(0.2, 0.8, 0.3);
    glutWireCube(1.0);
    glPopMatrix();


    glTranslatef(-1, -0.4, 0.0);
    glRotatef((GLfloat)elbow[1], 1.0, 0.0, 0.0);
    glTranslatef(1, -0.4, 0.0);

    glPushMatrix();
    glScalef(0.2, 0.8, 0.3);
    glutWireCube(1.0);
    glPopMatrix();

    // START OF FINGER 1
    glPushMatrix();

    glTranslatef(-0.05, -0.5, 0.125);


    glTranslatef(0.1, 0, 0);
    glRotatef(flang[1], 0, 0, 1);
    glTranslatef(-0.1, 0, 0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.03);
    glutWireCube(1.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.0, -0.2, 0);
    glTranslatef(0.05, 0, 0);
    glRotatef(fingers[1], 0, 0, 1);
    glTranslatef(-0.05, 0, 0);
    glScalef(0.08, 0.2, 0.03);
    glutWireCube(1.0);
    glPopMatrix();

    glPopMatrix();

    //// END OF FINGER 1

    // START OF FINGER 2
    glPushMatrix();

    glTranslatef(-0.05, -0.5, 0.045);


    glTranslatef(0.1, 0, 0);
    glRotatef(flang[1], 0, 0, 1);
    glTranslatef(-0.1, 0, 0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.03);
    glutWireCube(1.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.0, -0.2, 0);
    glTranslatef(0.05, 0, 0);
    glRotatef(fingers[1], 0, 0, 1);
    glTranslatef(-0.05, 0, 0);
    glScalef(0.08, 0.2, 0.03);
    glutWireCube(1.0);
    glPopMatrix();

    glPopMatrix();

    //// END OF FINGER 2

    // START OF FINGER 3
    glPushMatrix();

    glTranslatef(-0.05, -0.5, -0.045);


    glTranslatef(0.1, 0, 0);
    glRotatef(flang[1], 0, 0, 1);
    glTranslatef(-0.1, 0, 0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.03);
    glutWireCube(1.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.0, -0.2, 0);
    glTranslatef(0.05, 0, 0);
    glRotatef(fingers[1], 0, 0, 1);
    glTranslatef(-0.05, 0, 0);
    glScalef(0.08, 0.2, 0.03);
    glutWireCube(1.0);
    glPopMatrix();

    glPopMatrix();

    //// END OF FINGER 3

    // START OF FINGER 4
    glPushMatrix();

    glTranslatef(-0.05, -0.5, -0.125);


    glTranslatef(0.1, 0, 0);
    glRotatef(flang[1], 0, 0, 1);
    glTranslatef(-0.1, 0, 0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.03);
    glutWireCube(1.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.0, -0.2, 0);
    glTranslatef(0.05, 0, 0);
    glRotatef(fingers[1], 0, 0, 1);
    glTranslatef(-0.05, 0, 0);
    glScalef(0.08, 0.2, 0.03);
    glutWireCube(1.0);
    glPopMatrix();

    glPopMatrix();

    //// END OF FINGER 4
     // START OF FINGER 5
    glPushMatrix();

    glTranslatef(0.05, -0.5, 0);


    glTranslatef(0.1, 0, 0);
    glRotatef(-flang[1], 0, 0, 1);
    glTranslatef(-0.1, 0, 0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.03);
    glutWireCube(1.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.0, -0.2, 0);
    glTranslatef(0.05, 0, 0);
    glRotatef(-fingers[1], 0, 0, 1);
    glTranslatef(-0.05, 0, 0);
    glScalef(0.08, 0.2, 0.03);
    glutWireCube(1.0);
    glPopMatrix();

    glPopMatrix();
    //// END OF FINGER 5


    glPopMatrix();

    //END OF LEFT ARM

    glPopMatrix();
    glutSwapBuffers();
}




void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(85.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}



void keyboard(unsigned char key, int x, int y)
{
    switch (key) {


    case '3':
        moveForward();
        glutPostRedisplay();
        break;
    case '4':
        moveBackword();
        glutPostRedisplay();
        break;
    case '5':
        reset();
        glutPostRedisplay();
        break;

    case 'a':
        if (leg1[1] >= -60) {
            leg1[1] = (leg1[1] - 5) % 360;
            glutPostRedisplay();


        }
        break;

    case 'A':
        if (leg1[1] <= 50) {
            leg1[1] = (leg1[1] + 5) % 360;
            glutPostRedisplay();
        }
        break;


    case 's':
        if (leg1[0] >= -60) {
            leg1[0] = (leg1[0] - 5) % 360;
            glutPostRedisplay();


        }
        break;

    case 'S':
        if (leg1[0] <= 50) {
            leg1[0] = (leg1[0] + 5) % 360;
            glutPostRedisplay();
        }
        break;


    case 'd':
        if (leg2[1] <= 15) {
            leg2[1] = (leg2[1] + 5) % 360;
            glutPostRedisplay();
        }
        break;

    case 'D':
        if (leg2[1] >= -80) {
            leg2[1] = (leg2[1] - 5) % 360;
            glutPostRedisplay();
        }

        break;




    case 'f':
        if (leg2[0] >= -15) {
            leg2[0] = (leg2[0] - 5) % 360;
            glutPostRedisplay();
        }
        break;

    case 'F':
        if (leg2[0] <= 80) {
            leg2[0] = (leg2[0] + 5) % 360;
            glutPostRedisplay();
        }

        break;



    case 'g':
        if (knee[1] >= -70) {
            knee[1] = (knee[1] - 5) % 360;
            glutPostRedisplay();
        }
        break;

    case 'G':
        if (knee[1] <= 60) {
            knee[1] = (knee[1] + 5) % 360;
            glutPostRedisplay();
        }
        break;



    case 'h':
        if (knee[0] >= -70) {
            knee[0] = (knee[0] - 5) % 360;
            glutPostRedisplay();
        }
        break;

    case 'H':
        if (knee[0] <= 60) {
            knee[0] = (knee[0] + 5) % 360;
            glutPostRedisplay();
        }
        break;




    case 'j':
        if (arm[1] < 30) {
            arm[1] = (arm[1] + 5) % 360;
            glutPostRedisplay();
        }
        break;

    case 'J':
        if (arm[1] > -170) {
            arm[1] = (arm[1] - 5) % 360;
            glutPostRedisplay();
        }
        break;



    case 'k':
        if (arm[0] > -30) {
            arm[0] = (arm[0] - 5) % 360;
            glutPostRedisplay();
        }
        break;


    case 'K':
        if (arm[0] < 170) {
            arm[0] = (arm[0] + 5) % 360;
            glutPostRedisplay();
        }
        break;




    case 'l':
        if (arm3[1] < 90) {
            arm3[1] = (arm3[1] + 5) % 360;
            glutPostRedisplay();
        }
        break;

    case 'L':
        if (arm3[1] > -90) {
            arm3[1] = (arm3[1] - 5) % 360;
            glutPostRedisplay();
        }
        break;

    case 'z':
        if (arm3[0] < 90) {
            arm3[0] = (arm3[0] + 5) % 360;
            glutPostRedisplay();
        }
        break;

    case 'Z':
        if (arm3[0] > -90) {
            arm3[0] = (arm3[0] - 5) % 360;
            glutPostRedisplay();
        }
        break;



    case 'x':
        if (elbow[1] < 110) {
            elbow[1] = (elbow[1] + 5) % 360;
            glutPostRedisplay();
        }
        break;

    case 'X':
        if (elbow[1] > -110) {
            elbow[1] = (elbow[1] - 5) % 360;
            glutPostRedisplay();
        }
        break;

    case 'c':
        if (elbow[0] < 110) {
            elbow[0] = (elbow[0] + 5) % 360;
            glutPostRedisplay();
        }
        break;

    case 'C':
        if (elbow[0] > -110) {
            elbow[0] = (elbow[0] - 5) % 360;
            glutPostRedisplay();
        }
        break;





    case 'i':
        if (arm2[1] < 90) {
            arm2[1] = (arm2[1] + 5) % 360;
            glutPostRedisplay();
        }
        break;

    case 'I':
        if (arm2[1] > -80) {
            arm2[1] = (arm2[1] - 5) % 360;
            glutPostRedisplay();
        }
        break;



    case 'o':
        if (arm2[0] < 90) {
            arm2[0] = (arm2[0] + 5) % 360;
            glutPostRedisplay();
        }
        break;

    case 'O':
        if (arm2[0] > -80) {
            arm2[0] = (arm2[0] - 5) % 360;
            glutPostRedisplay();
        }
        break;





    case 'v':
        if (flang[1] < 10) {
            flang[1] = (flang[1] + 5) % 360;
            glutPostRedisplay();
        }
        break;

    case 'V':
        if (flang[1] > -10) {
            flang[1] = (flang[1] - 5) % 360;
            glutPostRedisplay();
        }
        break;

    case 'b':
        if (fingers[1] < 10) {
            fingers[1] = (fingers[1] + 5) % 360;
            glutPostRedisplay();
        }
        break;

    case 'B':
        if (fingers[1] > -10) {
            fingers[1] = (fingers[1] - 5) % 360;
            glutPostRedisplay();
        }
        break;

    case 'n':
        if (flang[0] < 10) {
            flang[0] = (flang[0] + 5) % 360;
            glutPostRedisplay();
        }
        break;

    case 'N':
        if (flang[0] > -10) {
            flang[0] = (flang[0] - 5) % 360;
            glutPostRedisplay();
        }
        break;

    case 'm':
        if (fingers[0] < 10) {
            fingers[0] = (fingers[0] + 5) % 360;
            glutPostRedisplay();
        }
        break;

    case 'M':
        if (fingers[0] > -10) {
            fingers[0] = (fingers[0] - 5) % 360;
            glutPostRedisplay();
        }
        break;



    case 27:
        exit(0);
        break;
    default:
        break;
    }
}





static void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            moving = 1;
            startx = x;
            starty = y;
        }
        if (state == GLUT_UP) {
            moving = 0;
        }
    }
}

static void motion(int x, int y)
{
    if (moving) {
        angle1 = angle1 + (x - startx);
        angle2 = angle2 + (y - starty);
        startx = x;
        starty = y;
        glutPostRedisplay();
    }
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;

}

