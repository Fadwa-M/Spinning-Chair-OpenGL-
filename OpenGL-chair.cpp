#include<bits/stdc++.h>
#include<GL/glu.h>
#include<GL/glut.h>
//#include <windows.h>
using namespace std;

float x_rotation=0;
float y_rotation=0;
float z_rotation=0;

float x_trans=0;
float y_trans=0;
float z_trans=0;

double scale_x = 1.0; 
double scale_y = 1.0; 
double scale_z = 1.0;

int dx[]={-1,1,1,-1};
int dy[]={-1,-1,-1,-1};
int dz[]={-1,-1,1,1};

float angle=0;
bool rotate_by_default = 1;

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON and state == GLUT_DOWN || button == 3) 
            scale_x += 0.1, scale_y += 0.1, scale_z += 0.1;

    if (button == GLUT_RIGHT_BUTTON and state == GLUT_DOWN || button == 4) 
        if(scale_x > 0.2 && scale_y > 0.2 && scale_z > 0.2)
            scale_x -= 0.1, scale_y -= 0.1, scale_z -= 0.1;

    glutPostRedisplay(); /// Post re-paint request to activate display()
}

void specFunc(int key,int x,int y){
    x_trans += (key==GLUT_KEY_RIGHT?  0.1 : 0);
    x_trans += (key==GLUT_KEY_LEFT ? -0.1 : 0);
    y_trans += (key==GLUT_KEY_UP ?    0.1 : 0);
    y_trans += (key==GLUT_KEY_DOWN ? -0.1 : 0);
    z_trans += (key== GLUT_KEY_F1?    0.1 : 0);
    z_trans += (key== GLUT_KEY_F2?   -0.1 : 0);

    glutPostRedisplay(); 

}
void keyboardFunction(unsigned char key ,int x,int y){
    rotate_by_default = false;

    x_rotation += ( key == 'x' ?  0.5 : 0);
    x_rotation += ( key == 'X' ? -0.5 : 0);
    y_rotation += ( key == 'y' ?  0.5 : 0);
    y_rotation += ( key == 'Y' ? -0.5 : 0);
    z_rotation += ( key == 'z' ?  0.5 : 0);
    z_rotation += ( key == 'Z' ? -0.5 : 0);

    if(key=='r'){
        x_rotation = y_rotation = z_rotation = 0;
        x_trans = y_trans = z_trans = 0;
        scale_x = scale_y = scale_z = 1;
    }

    if(key==27)
        exit(0);

    glutPostRedisplay();
}

void defaultRotation(){
    float rotateValue = 0.2;

    if(rotate_by_default == true)
        y_rotation += rotateValue;
}

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT | // Clear the color buffer with current clearing color 
            GL_DEPTH_BUFFER_BIT); // and  the depth buffer. 
    glLoadIdentity();

    // Create a viewing matrix derived from an eye point, 
    // a reference point indicating the center of the scene, 
    // and an UP vector.
    gluLookAt(0,1,3,0,0,0,0,1,0);

    glRotatef(x_rotation,1.0,0.0,0.0);
    glRotatef(y_rotation,0.0,1.0,0.0);
    glRotatef(z_rotation,0.0,0.0,1.0);

    glTranslatef(x_trans,y_trans,z_trans);

    glScalef(scale_x,scale_y,scale_z);

    //bottom
    glPushMatrix(); /// Save model-view matrix setting
        glColor3f(0.4,0.5,0.6);
        glScalef(1,0.05,1);
        glutSolidCube(1);
    glPopMatrix(); /// Restore the model-view matrix


    // back
    glPushMatrix();
        glColor3f(0.4,0.3,0.3);
        glTranslatef(0.0,0.5,-0.48);
        glScalef(1,1,0.05);
        glutSolidCube(1);
    glPopMatrix();

    for(int i=0;i<4;i++){
        glPushMatrix();
            glTranslatef(0.46*dx[i],0.5*dy[i],0.46*dz[i]);
            glScalef(0.07,1,0.07);
            glutSolidCube(1);
        glPopMatrix();
    }

    // holes in the back
    glColor3f(1,1,1);
    glPushMatrix();
        glTranslatef(0.0,0.8,-0.48);
        glScalef(0.8,0.15,0.052);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0,0.5,-0.48);
        glScalef(0.8,0.15,0.052);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0,0.15,-0.48);
        glScalef(0.8,0.25,0.052);
        glutSolidCube(1);
    glPopMatrix();

    defaultRotation();
    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}

void MyInit() {
    glClearColor(1.0,1.0,1.0,1.0); ///Set background (clear) color to white
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); /// To operate on the Projection matrix
    glFrustum(-1,1,-1,1,2,10); ///describes a perspective matrix that produces a perspective projection.
    glMatrixMode(GL_MODELVIEW); ///To operate on the model-view matrix
}

void instructions();


int main(int argc,char **argv) {
    glutInit(&argc,argv);

    instructions();
    glutInitWindowSize(600,600);
    glutInitWindowPosition(500,100);
    glutInitDisplayMode(GLUT_RGB |    // Use RGBA coloring
                        GLUT_DOUBLE | // Enable double buffering
                        GLUT_DEPTH);  // enable depth buffering
    glutCreateWindow("Chair");

    MyInit();
    glutSpecialFunc(specFunc);
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(keyboardFunction);
    glutDisplayFunc(Draw);

    glutMainLoop();
    return 0;
}

void instructions() {
         // Rotation
cout <<  "x  Rotate in positive x axis \n" <<
         "X  Rotate in negative x axis \n" <<

         "y  Rotate in positive y axis \n" <<
         "Y  Rotate in negative y axis \n" <<

         "z  Rotate in positive z axis \n" <<
         "Z  Rotate in negative z axis \n\n" <<

         // Scaling
         "right mouse or scroll up click  scale down \n" <<
         "left mouse or scroll down click  scale up \n\n" <<

         // Translation
         "up key Translate in  positive y axis \n" <<
         "down key Translate in  negative y axis \n" <<

         "right key Translate in  positive x axis \n" <<
         "left key Translate in  negative x axis \n" <<

         "F1 key Translate in  positive z axis \n" <<
         "F2 key Translate in  negative Z axis \n\n" <<

         // Restting 
         "\"r\" for restoring the initial state\n"<<

        // Exiting
         "ESC to exit the program\n";

        cout.flush();
}

// update log
// - code style enhancments 
// - fixed the zooming issue
// - zoom in and out using scroll wheel 
// - reseting the initial state of the chair by pressing "r" 
// - close program using escape key
// - the chair rotates by defualt around the y-axis
//   until the user makes an interaction through the keyboard
// - recolored the chair  & removed lighting 
