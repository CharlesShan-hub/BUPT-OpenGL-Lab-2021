/*
#include <GLUT/glut.h>
#include <math.h>

#define MaxGLfloat 64
typedef struct{
    GLfloat data[MaxGLfloat][2];
    int num;
}GLfloatArray;

void draw_INIT(){
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 1.0, 1.0, 0.0);
}

void draw_LINE(GLfloatArray array,int line_width,float R,float G, float B){
    glLineWidth(line_width);
    glColor3f (R,G,B);
    glBegin(GL_LINES);
    for(int i=0;i<array.num;i++)
        glVertex2fv(array.data[i]);
    glEnd();
    glFlush();
}

void draw_POLYGON(GLfloatArray array,int line_width,float R,float G, float B){
    glLineWidth(line_width);
    glColor3f (R,G,B);
    glBegin(GL_POLYGON);
    for(int i=0;i<array.num;i++)
        glVertex2fv(array.data[i]);
    glEnd();
    glFlush();
}

void draw_LINE_LOOP(float pos_x,float pos_y,float r,int line_width,float R,float G, float B,int num_segments){
    glColor3f(R,G,B);
    glLineWidth(line_width);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
            glVertex2f(x+pos_x, y+pos_y);
    }
    glEnd();
    glFlush();
}

void display(){
    // Draw init
    draw_INIT();
    
    // Draw Smoke
    draw_LINE_LOOP(0.4,0.7,0.05,5,0,0,0,128);
    draw_LINE_LOOP(0.5,0.8,0.06,5,0,0,0,128);
    draw_LINE_LOOP(0.6,0.9,0.07,5,0,0,0,128);
    
    // Draw Chimney
    GLfloatArray pos_chimney = {{
        {0.2,0.3}, {0.4,0.3}, {0.4,0.7}, {0.2,0.7}
    },4};
    draw_POLYGON(pos_chimney,4,0.0, 0.0, 0.0);
    
    // Draw a Outline
    GLfloatArray pos_outline1 = {{
        {0.0,0.8}, {0.5,0.2}, {-0.5,0.2}
    },3};
    draw_POLYGON(pos_outline1,4,1.0,0.0,0.0);
    
    GLfloatArray pos_outline2 = {{
        {0.5,0.2}, {0.5,-0.7}, {-0.5,-0.7}, {-0.5,0.2}
    },4};
    draw_POLYGON(pos_outline2,4,1.0, 1.0, 1.0);
    
    // Draw door and windows
    GLfloatArray pos_window_and_door = {{
        {-0.4, -0.0},{-0.1, -0.0},
        {-0.1, -0.0},{-0.1, -0.3},
        {-0.1, -0.3},{-0.4, -0.3},
        {-0.4, -0.3},{-0.4, -0.0},
        {-0.25,-0.0},{-0.25,-0.3},
        {-0.1,-0.15},{-0.4,-0.15},
        { 0.1, -0.0},{ 0.4, -0.0},
        { 0.1, -0.0},{ 0.1, -0.7},
        { 0.4, -0.0},{ 0.4, -0.7},
    },18};
    draw_LINE(pos_window_and_door,6 ,0.0, 0.0, 0.0);
    
    GLfloatArray pos_door_bar = {{
        {0.15,-0.325}, {0.2,-0.325}, {0.2,-0.375}, {0.15,-0.375}
    },4};
    draw_POLYGON(pos_door_bar,4,0.0, 0.0, 0.0);
    
    // Draw fence
    GLfloatArray pos_fence = {{
        {-0.9,-0.7},{0.9,-0.7}},44};
    for(int i=0;i<19;i++){
        pos_fence.data[2+2*i][0]=-0.9+0.1*i;
        pos_fence.data[2+2*i][1]=-0.6;
        pos_fence.data[3+2*i][0]=-0.9+0.1*i;
        pos_fence.data[3+2*i][1]=-0.9;
    }
    draw_LINE(pos_fence,50 ,169.0/255, 104.0/255, 36.0/255);

}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutCreateWindow("House");
    glutDisplayFunc(display);
    glutMainLoop();
}
*/
/*#######################################################################################################*/
/*
#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>
 
#define SOLID 1
#define WIRE 2
 
int moveX,moveY;
int spinX = 0;
int spinY = 0;
int des = 0;
 
void init() {
   //??????????????????????????????
   GLfloat ambient[] = { 0.5, 0.8, 0.1, 0.1 };
   GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat position[] = { -80.0, 50.0, 25.0, 1.0 };
   //??????????????????
   GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
   GLfloat local_view[] = { 0.0 };
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_SMOOTH);
   //???????????????
   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   //???????????????
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
   //??????????????????
   glLightfv(GL_LIGHT0, GL_POSITION, position);
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
   glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
   //????????????
   glEnable(GL_LIGHTING);
   //????????????
   glEnable(GL_LIGHT0);
}
 
//??????
void drawBall(double R, double x, double y,double z, int MODE) {
    glPushMatrix();
    glTranslated(x,y,z);
    if (MODE == SOLID) {
        glutSolidSphere(R,20,20);
    } else if (MODE ==WIRE) {
        glutWireSphere(R,20,20);
    }
    glPopMatrix();
}
 
//?????????
void drawHalfBall(double R, double x, double y,double z, int MODE) {
    glPushMatrix();
    glTranslated(x,y,z);
    GLdouble eqn[4]={0.0, 1.0, 0.0, 0.0};
    glClipPlane(GL_CLIP_PLANE0,eqn);
    glEnable(GL_CLIP_PLANE0);
    if (MODE == SOLID) {
        glutSolidSphere(R,20,20);
    } else if (MODE ==WIRE) {
        glutWireSphere(R,20,20);
    }
    glDisable(GL_CLIP_PLANE0);
    glPopMatrix();
}
 
//????????????
void drawSkewed(double l, double w, double h, double x, double y, double z, int MODE) {
    glPushMatrix();
    glScaled(l, w, h);
    glTranslated(x, y, z);
    if (MODE == SOLID) {
        glutSolidCube(1);
    } else if (MODE ==WIRE) {
        glutWireCube(1);
    }
    glPopMatrix();
}
 
void display(void) {
    //?????????????????????
    glClear(GL_COLOR_BUFFER_BIT);
    //????????????
    glColor3f(1.0, 1.0, 1.0);
    //?????????????????????
    glLoadIdentity();
    //??????????????????
    gluLookAt(-2.0, -1.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    glRotated(spinX, 0, 1, 0);
    glRotated(spinY, 1, 0, 0);
    glTranslated(0, 0, des);
    //???
    drawBall(2, 0, 1, 0, SOLID);
    //??????
    drawSkewed(5, 4.4, 4, 0, -0.75, 0, SOLID);
    //??????
    drawHalfBall(1, 3.5, -2.1, 0, SOLID);
    drawHalfBall(1, -3.5, -2.1, 0, SOLID);
    //??????
    drawSkewed(1, 3, 1, 3.5, -1.3, 0, SOLID);
    drawSkewed(1, 3, 1, -3.5, -1.3, 0, SOLID);
    //???
    drawBall(1, 3.5, -6.4, 0, SOLID);
    drawBall(1, -3.5, -6.4, 0, SOLID);
    //???
    drawSkewed(1.2, 3, 2, 1, -2.4, 0, SOLID);
    drawSkewed(1.2, 3, 2, -1, -2.4, 0, SOLID);
    //???
    drawSkewed(1.5, 1, 3, 0.9, -9.2, 0, SOLID);
    drawSkewed(1.5, 1, 3, -0.9, -9.2, 0, SOLID);
    glPopMatrix();
    glutSwapBuffers();
}
//??????????????????
void mouseClick(int btn, int state, int x, int y) {
    moveX = x;
    moveY = y;
    GLfloat ambient[] = { (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 0.1 };
     //???????????????
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    //????????????
    glEnable(GL_LIGHT0);
}
 
//????????????
void keyPressed(unsigned char key, int x, int y) {
    switch (key) {
    case 'a':
        spinX -= 2;
        break;
    case 'd':
         spinX += 2;
        break;
    case 'w':
        des += 2;
        break;
    case 's':
        des -= 2;
        break;
    }
    glutPostRedisplay();
}
// ??????????????????
void mouseMove(int x, int y) {
    int dx = x - moveX;
    int dy = y - moveY;
    printf("dx;%dx,dy:%dy\n",dx,dy);
    spinX += dx;
    spinY += dy;
    glutPostRedisplay();
    moveX = x;
    moveY = y;
}
 
void reshape(int w, int h) {
    //??????????????????
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    //????????????
    glMatrixMode(GL_PROJECTION);
    //???????????????????????????
    glLoadIdentity();
    //??????????????????
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}
 
int main(int argc, char** argv) {
    //?????????
    glutInit(&argc, argv);
    //??????????????????
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    //?????????????????????
    glutInitWindowSize(500, 500);
    //???????????????????????????
    glutInitWindowPosition(100, 100);
    //????????????
    glutCreateWindow(argv[0]);
    //?????????
    init();
    //????????????
    glutDisplayFunc(display);
    //??????????????????????????????
    glutReshapeFunc(reshape);
    //??????????????????????????????????????????????????????
    glutMouseFunc(mouseClick);
    //???????????????????????????????????????????????????
    glutMotionFunc(mouseMove);
    //????????????
    glutKeyboardFunc(keyPressed);
    //??????
    glutMainLoop();
    return 0;
}
*/
/*#######################################################################################################*/
/*
#include <GLUT/glut.h>
#include <math.h>
#include <stdio.h>
//????????????
#define GL_PI 3.1415f
//?????????????????????
GLint SCREEN_WIDTH=0;
GLint SCREEN_HEIGHT=0;
//???????????????????????????
GLint windowWidth=400;
GLint windowHeight=300;
//???x???????????????
GLfloat xRotAngle=0.0f;
//???y???????????????
GLfloat yRotAngle=0.0f;
//???????????????????????????
GLfloat sizes[2];
//???????????????????????????
GLfloat step;
  
enum MODELS{
    SPHERE=0,
    CONE,
    CUBE,
    TORUS,
    DODECAHEDRON,
    TEAPOT,
    OCTAHEDRON,
    TETRAHEDRON,
    ICOSAHEDRON
};
GLint iModel=SPHERE;
GLboolean bWire=GL_TRUE;
//??????????????????
void processMenu(int value){
    switch(value){
        case 1:
            iModel=SPHERE;
            break;
        case 2:
            iModel=CONE;
            break;
        case 3:
            iModel=CUBE;
            break;
        case 4:
            iModel=TORUS;
            break;
        case 5:
            iModel=DODECAHEDRON;
            break;
        case 6:
            iModel=TEAPOT;
            break;
        case 7:
            iModel=OCTAHEDRON;
            break;
        case 8:
            iModel=TETRAHEDRON;
            break;
        case 9:
            iModel=ICOSAHEDRON;
            break;
        case 10:
            bWire=GL_TRUE;
            break;
        case 11:
            bWire=GL_FALSE;
            break;
        default:
            break;
    }
    //????????????
    glutPostRedisplay();
}
//??????????????????
void renderScreen(void){
    //??????????????????????????????
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    //????????????????????????????????????1
    glClearStencil(1);
    //?????????????????????
    glEnable(GL_STENCIL_TEST);
    //?????????????????????????????????????????????????????????????????????????????????????????????
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    //?????????Matrix????????????
    glPushMatrix();
    //????????????x?????????xRotAngle
    glRotatef(xRotAngle,1.0f,0.0f,0.0f);
    //????????????y?????????yRotAngle
    glRotatef(yRotAngle,0.0f,1.0f,0.0f);
    //??????????????????
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH,GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH,GL_NICEST);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH,GL_NICEST);
      
    //?????????????????????
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_LINES);
        glVertex3f(-9.0f,0.0f,0.0f);
        glVertex3f(9.0f,0.0f,0.0f);
        glVertex3f(0.0f,-9.0f,0.0f);
        glVertex3f(0.0f,9.0f,0.0f);
        glVertex3f(0.0f,0.0f,-9.0f);
        glVertex3f(0.0f,0.0f,9.0f);
    glEnd();
  
    glPushMatrix();
    glTranslatef(9.0f,0.0f,0.0f);
    glRotatef(90.0f,0.0f,1.0f,0.0f);
    glutSolidCone(0.3,0.6,10,10);
    glPopMatrix();
  
    glPushMatrix();
    glTranslatef(0.0f,9.0f,0.0f);
    glRotatef(-90.0f,1.0f,0.0f,0.0f);
    glutSolidCone(0.3,0.6,10,10);
    glPopMatrix();
  
    glPushMatrix();
    glTranslatef(0.0f,0.0f,9.0f);
    glRotatef(90.0f,0.0f,0.0f,1.0f);
    glutSolidCone(0.3,0.6,10,10);
    glPopMatrix();
  
    //???????????????????????????
    glColor3f(0.0f,1.0f,0.0f);
    switch(iModel){
        //???
        case SPHERE:
            if(bWire){
                glutWireSphere(8.0f,20,20);
            }
            else{
                glutSolidSphere(8.0f,20,20);
            }
            break;
        //??????
        case CONE:
            if(bWire){
                glutWireCone(4.0f,8.0f,20,20);
            }
            else{
                glutSolidCone(4.0f,8.0f,20,20);
            }
            break;
        //??????
        case CUBE:
            if(bWire){
                glutWireCube(8.0f);
            }
            else{
                glutSolidCube(8.0f);
            }
            break;
        //??????
        case TORUS:
            if(bWire){
                glutWireTorus(3.0f,6.0f,20,20);
            }
            else{
                glutSolidTorus(3.0f,6.0f,20,20);
            }
            break;
        //???????????????????????????1.0
        case DODECAHEDRON:
            glScalef(6.0f,6.0f,6.0f);//x,y,z????????????6???
            if(bWire){
                glutWireDodecahedron();
            }
            else{
                glutSolidDodecahedron();
            }
            break;
        //??????
        case TEAPOT:
            if(bWire){
                glutWireTeapot(8.0f);
            }
            else{
                glutSolidTeapot(8.0f);
            }
            break;
        //????????????????????????1.0
        case OCTAHEDRON:
            glScalef(6.0f,6.0f,6.0f);//x,y,z????????????6???
            if(bWire){
                glutWireOctahedron();
            }
            else{
                glutSolidOctahedron();
            }
            break;
        //????????????????????????1.0
        case TETRAHEDRON:
            glScalef(6.0f,6.0f,6.0f);//x,y,z????????????6???
            if(bWire){
                glutWireTetrahedron();
            }
            else{
                glutSolidTetrahedron();
            }
            break;
        //???????????????????????????1.0
        case ICOSAHEDRON:
            glScalef(6.0f,6.0f,6.0f);//x,y,z????????????6???
            if(bWire){
                glutWireIcosahedron();
            }
            else{
                glutSolidIcosahedron();
            }
            break;
        default:
            break;
    }
  
    //??????????????????Matrix
    glPopMatrix();
    //??????????????????????????????
    glutSwapBuffers();
}
//??????Redering State
void setupRederingState(void){
    //???????????????????????????
    glClearColor(0.0f,0.0,0.0,1.0f);
    //???????????????????????????
    glColor3f(1.0f,1.0f,0.0f);
    //??????????????????
    glEnable(GL_DEPTH_TEST);
    //?????????????????????????????????
    glGetFloatv(GL_POINT_SIZE_RANGE,sizes);
    //?????????????????????????????????
    glGetFloatv(GL_POINT_SIZE_GRANULARITY,&step);
    printf("point size range:%f-%f\n",sizes[0],sizes[1]);
    printf("point step:%f\n",step);
}
//??????????????????????????????
void changSize(GLint w,GLint h){
    //????????????
    GLfloat ratio;
    //??????????????????x(-100.0f,100.0f)???y(-100.0f,100.0f)???z(-100.0f,100.0f)
    GLfloat coordinatesize=10.0f;
    //??????????????????????????????
    if((w==0)||(h==0))
        return;
    //?????????????????????????????????
    glViewport(0,0,w,h);
    //??????????????????????????????????????????
    glMatrixMode(GL_PROJECTION);
    //??????????????????????????????????????????
    glLoadIdentity();
    ratio=(GLfloat)w/(GLfloat)h;
    //????????????
    if(w<h)
        glOrtho(-coordinatesize,coordinatesize,-coordinatesize/ratio,coordinatesize/ratio,-coordinatesize,coordinatesize);
    else
        glOrtho(-coordinatesize*ratio,coordinatesize*ratio,-coordinatesize,coordinatesize,-coordinatesize,coordinatesize);
    //??????????????????????????????????????????????????????
    glMatrixMode(GL_MODELVIEW);
    //??????????????????????????????????????????
    glLoadIdentity();
}
  
//??????????????????????????????
void specialKey(int key,int x,int y){
  
    if(key==GLUT_KEY_UP){
        xRotAngle-=5.0f;
    }
    else if(key==GLUT_KEY_DOWN){
        xRotAngle+=5.0f;
    }
    else if(key==GLUT_KEY_LEFT){
        yRotAngle-=5.0f;
    }
    else if(key==GLUT_KEY_RIGHT){
        yRotAngle+=5.0f;
    }
    //????????????
    glutPostRedisplay();
}
  
int main(int argc, char* argv[])
{
    int nModelMenu;
    int nWireMenu;
    int nMainMenu;
    //?????????glut
    glutInit(&argc,argv);
    //??????????????????????????????????????????????????????
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL);
    //????????????????????????
    SCREEN_WIDTH=glutGet(GLUT_SCREEN_WIDTH);
    //????????????????????????
    SCREEN_HEIGHT=glutGet(GLUT_SCREEN_HEIGHT);
    //??????????????????????????????OpenGL Glut Demo
    glutCreateWindow("OpenGL Glut Demo");
    //??????????????????
    glutReshapeWindow(windowWidth,windowHeight);
    //??????????????????
    glutPositionWindow((SCREEN_WIDTH-windowWidth)/2,(SCREEN_HEIGHT-windowHeight)/2);
    //??????????????????
    nModelMenu=glutCreateMenu(processMenu);
    glutAddMenuEntry("Sphere",1);
    glutAddMenuEntry("Cone",2);
    glutAddMenuEntry("Cube",3);
    glutAddMenuEntry("Torus",4);
    glutAddMenuEntry("Dodecahedron",5);
    glutAddMenuEntry("Teapot",6);
    glutAddMenuEntry("Octahedron",7);
    glutAddMenuEntry("Tetrahedron",8);
    glutAddMenuEntry("Icosahedron",9);
    nWireMenu=glutCreateMenu(processMenu);
    glutAddMenuEntry("Wire",10);
    glutAddMenuEntry("Solid",11);
    nMainMenu=glutCreateMenu(processMenu);
    glutAddSubMenu("Model",nModelMenu);
    glutAddSubMenu("WireOrSolid",nWireMenu);
    //?????????????????????????????????
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    //????????????????????????????????????
    glutReshapeFunc(changSize);
    //????????????????????????
    glutDisplayFunc(renderScreen);
    //????????????????????????????????????
    glutSpecialFunc(specialKey);
    //????????????????????????
    setupRederingState();
    glutMainLoop();
    return 0;
}
*/
/*#######################################################################################################*/
/*
#include <GLUT/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    Visualise a 3D axis
    glColor3f(1.0, 0.0, 0.0);    //????????
    glBegin(GL_LINES);    //????
    glVertex3f(0, 0, 0);
    glVertex3f(2, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 2, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 2);
    glEnd();
    
    //wall
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);    //????????
    glutSolidCube(1);    //SolidCube ????????1
    glPopMatrix();

    //chimney
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslated(0.4, 1.0, 0);
    glutSolidCube(0.2);
    glPopMatrix();
    
    //roof
    glPushMatrix();
    glTranslated(0, 0.41, 0); //Translated ????????1
    glRotated(270, 10, 0, 0); //Rotated
    glColor3f(1, 0, 0);    //????????
    glutSolidCone(1, 1, 50, 50); //SolidCone
    glPopMatrix();

    //door
    glPushMatrix();
    glTranslated(0, 0, 0.501);
    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_POLYGON);
    glVertex2f(0.1, 0.2);
    glVertex2f(0.4, 0.2);
    glVertex2f(0.4, -0.5);
    glVertex2f(0.1, -0.5);
    glEnd();

    //window
    glBegin(GL_POLYGON);
    glVertex2f(-0.4, 0.2);
    glVertex2f(-0.1, 0.2);
    glVertex2f(-0.1, -0.1);
    glVertex2f(-0.4, -0.1);
    glEnd();
    glPopMatrix();

    //fence
    glBegin(GL_POLYGON);
    glVertex3f(1.0, -0.5, 1.0);
    glVertex3f(-1.0, -0.5, 1.0);
    glVertex3f(-1.0, -0.2, 1.0);
    glVertex3f(1.0, -0.2, 1.0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(1.0, -0.5, -1.0);
    glVertex3f(-1.0, -0.5, -1.0);
    glVertex3f(-1.0, -0.2, -1.0);
    glVertex3f(1.0,-0.2, -1.0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(1.0, -0.5, 1.0);
    glVertex3f(1.0, -0.2, 1.0);
    glVertex3f(1.0, -0.2, -1.0);
    glVertex3f(1.0, -0.5, -1.0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(-1.0, -0.5, 1.0);
    glVertex3f(-1.0, -0.2, 1.0);
    glVertex3f(-1.0, -0.2, -1.0);
    glVertex3f(-1.0, -0.5, -1.0);
    glEnd();

    //law
    glColor3f(0, 0.8, 0);
    glBegin(GL_POLYGON);
    glVertex3f(2.0,-0.5,2.0);
    glVertex3f(-2.0, -0.5, 2.0);
    glVertex3f(-2.0, -0.5, -2.0);
    glVertex3f(2.0, -0.5, -2.0);
    glEnd();

    glFlush();
}

void init() {
    //wall lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_position[] = { 1.0, 1.0, 0.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_COLOR_MATERIAL);
    
    //3D background
    glClearColor(0.0, 1.0, 1.0, 1.0);    //????????
    glColor3f(0.0, 0.0, 0.0);    //????????
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 100.0); //top=100 others=2
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("3D Drawing with Visualised Axis");
    glutDisplayFunc(display);
    init();
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}
*/

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// angle of rotation for the camera direction
float angle = 0.0f;

// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;

// XZ position of the camera
float x = 0.0f, z = 5.0f;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

// Constant definitions for Menus
#define RED 1
#define GREEN 2
#define BLUE 3
#define ORANGE 4

#define FILL 1
#define LINE 2

// Pop up menu identifiers
int fillMenu, fontMenu, mainMenu, colorMenu;

// color for the nose
float red = 1.0f, blue = 0.5f, green = 0.5f;

// scale of snowman
float scale = 1.0f;

// menu status
int menuFlag = 0;

// default font
void *font = GLUT_BITMAP_TIMES_ROMAN_24;

#define INT_GLUT_BITMAP_8_BY_13 1
#define INT_GLUT_BITMAP_9_BY_15 2
#define INT_GLUT_BITMAP_TIMES_ROMAN_10  3
#define INT_GLUT_BITMAP_TIMES_ROMAN_24  4
#define INT_GLUT_BITMAP_HELVETICA_10  5
#define INT_GLUT_BITMAP_HELVETICA_12  6
#define INT_GLUT_BITMAP_HELVETICA_18  7

void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;

    float ratio = w * 1.0 / h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

void drawSnowMan() {

    glScalef(scale, scale, scale);
    glColor3f(1.0f, 1.0f, 1.0f);

    // Draw Body
    glTranslatef(0.0f, 0.75f, 0.0f);
    glutSolidSphere(0.75f, 20, 20);

    // Draw Head
    glTranslatef(0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.25f, 20, 20);

    // Draw Eyes
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.05f, 0.10f, 0.18f);
    glutSolidSphere(0.05f, 10, 10);
    glTranslatef(-0.1f, 0.0f, 0.0f);
    glutSolidSphere(0.05f, 10, 10);
    glPopMatrix();

    // Draw Nose
    glColor3f(red, green, blue);
    glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(0.08f, 0.5f, 10, 2);

    glColor3f(1.0f, 1.0f, 1.0f);

}

void renderBitmapString(
    float x,
    float y,
    float z,
    void *font,
    char *string) {
    char *c;
    glRasterPos3f(x, y, z);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void computePos(float deltaMove) {

    x += deltaMove * lx * 0.1f;
    z += deltaMove * lz * 0.1f;
}

void renderScene(void)
{
    if (deltaMove)
        computePos(deltaMove);

    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();
    
    // Set the camera
    gluLookAt(x, 1.0f, z,
        x + lx, 1.0f, z + lz,
        0.0f, 1.0f, 0.0f);

    // Draw ground
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, -100.0f);
    glEnd();

    // Draw 36 SnowMen
    char number[3];
    for (int i = -3; i < 3; i++)
    {
        for (int j = -3; j < 3; j++)
        {
            glPushMatrix();
            glTranslatef(i*10.0f, 0.0f, j * 10.0f);
            drawSnowMan();
            sprintf(number, "%d", (i + 3) * 6 + (j + 3));
            renderBitmapString(0.0f, 0.5f, 0.0f, (void *)font, number);
            glPopMatrix();
        }
    }
        
    glutSwapBuffers();
}

// -----------------------------------
//             KEYBOARD
// -----------------------------------

void processNormalKeys(unsigned char key, int xx, int yy)
{
    switch (key)
    {
    case 27:
        glutDestroyMenu(mainMenu);
        glutDestroyMenu(fillMenu);
        glutDestroyMenu(colorMenu);
        glutDestroyMenu(fontMenu);
        exit(0);
        break;
    }
}

void pressKey(int key, int xx, int yy)
{
    switch (key)
    {
    case GLUT_KEY_UP: deltaMove = 0.5f; break;
    case GLUT_KEY_DOWN: deltaMove = -0.5f; break;
    }
}

void releaseKey(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
    case GLUT_KEY_DOWN: deltaMove = 0; break;
    }
}

// -----------------------------------
//             MOUSE
// -----------------------------------

void mouseMove(int x, int y)
{
    // this will only be true when the left button is down
    if (xOrigin >= 0)
    {
        // update deltaAngle
        deltaAngle = (x - xOrigin) * 0.001f;

        // update camera's direction
        lx = sin(angle + deltaAngle);
        lz = -cos(angle + deltaAngle);
    }
}

void mouseButton(int button, int state, int x, int y)
{
    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {

        // when the button is released
        if (state == GLUT_UP) {
            angle += deltaAngle;
            xOrigin = -1;
        }
        else  {// state = GLUT_DOWN
            xOrigin = x;
        }
    }
}

// -----------------------------------
//             MENUS
// -----------------------------------

void processMenuStatus(int status, int x, int y)
{
    if (status == GLUT_MENU_IN_USE)
        menuFlag = 1;
    else
        menuFlag = 0;
}

void processMainMenu(int option)
{
    // nothing to do in here
    // all actions are for submenus
}

void processFillMenu(int option)
{
    switch (option)
    {
    case FILL: glPolygonMode(GL_FRONT, GL_FILL); break;
    case LINE: glPolygonMode(GL_FRONT, GL_LINE); break;
    }
}

void processFontMenu(int option)
{
    switch (option)
    {
    case INT_GLUT_BITMAP_8_BY_13:
        font = GLUT_BITMAP_8_BY_13;
        break;
    case INT_GLUT_BITMAP_9_BY_15:
        font = GLUT_BITMAP_9_BY_15;
        break;
    case INT_GLUT_BITMAP_TIMES_ROMAN_10:
        font = GLUT_BITMAP_TIMES_ROMAN_10;
        break;
    case INT_GLUT_BITMAP_TIMES_ROMAN_24:
        font = GLUT_BITMAP_TIMES_ROMAN_24;
        break;
    case INT_GLUT_BITMAP_HELVETICA_10:
        font = GLUT_BITMAP_HELVETICA_10;
        break;
    case INT_GLUT_BITMAP_HELVETICA_12:
        font = GLUT_BITMAP_HELVETICA_12;
        break;
    case INT_GLUT_BITMAP_HELVETICA_18:
        font = GLUT_BITMAP_HELVETICA_18;
        break;
    }
}

void processColorMenu(int option)
{
    switch (option) {
    case RED:
        red = 1.0f;
        green = 0.0f;
        blue = 0.0f; break;
    case GREEN:
        red = 0.0f;
        green = 1.0f;
        blue = 0.0f; break;
    case BLUE:
        red = 0.0f;
        green = 0.0f;
        blue = 1.0f; break;
    case ORANGE:
        red = 1.0f;
        green = 0.5f;
        blue = 0.5f; break;
    }
}

void createPopupMenus()
{
    fontMenu = glutCreateMenu(processFontMenu);

    glutAddMenuEntry("BITMAP_8_BY_13 ", INT_GLUT_BITMAP_8_BY_13);
    glutAddMenuEntry("BITMAP_9_BY_15", INT_GLUT_BITMAP_9_BY_15);
    glutAddMenuEntry("BITMAP_TIMES_ROMAN_10 ", INT_GLUT_BITMAP_TIMES_ROMAN_10);
    glutAddMenuEntry("BITMAP_TIMES_ROMAN_24", INT_GLUT_BITMAP_TIMES_ROMAN_24);
    glutAddMenuEntry("BITMAP_HELVETICA_10 ", INT_GLUT_BITMAP_HELVETICA_10);
    glutAddMenuEntry("BITMAP_HELVETICA_12", INT_GLUT_BITMAP_HELVETICA_12);
    glutAddMenuEntry("BITMAP_HELVETICA_18", INT_GLUT_BITMAP_HELVETICA_18);

    fillMenu = glutCreateMenu(processFillMenu);

    glutAddMenuEntry("Fill", FILL);
    glutAddMenuEntry("Line", LINE);

    colorMenu = glutCreateMenu(processColorMenu);
    glutAddMenuEntry("Red", RED);
    glutAddMenuEntry("Blue", BLUE);
    glutAddMenuEntry("Green", GREEN);
    glutAddMenuEntry("Orange", ORANGE);

    mainMenu = glutCreateMenu(processMainMenu);

    glutAddSubMenu("Polygon Mode", fillMenu);
    glutAddSubMenu("Color", colorMenu);
    glutAddSubMenu("Font", fontMenu);
    // attach the menu to the right button
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    // this will allow us to know if the menu is active
    glutMenuStatusFunc(processMenuStatus);
}

// -----------------------------------
//             MAIN
// -----------------------------------

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutCreateWindow("Lighthouse3D - GLUT Tutorial");

    // register callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);

    // here are the two new functions
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);

    // OpenGL init
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // init Menus
    createPopupMenus();

    // enter GLUT event processing cycle
    glutMainLoop();

    return 1;
}
