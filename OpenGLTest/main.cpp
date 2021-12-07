#include <GLUT/glut.h>
#include <math.h>
#include <stdio.h>

#define SOLID 1
#define WIRE 2

// Pop up menu identifiers
int fontMenu, colorMenu;

// default font
void *font = GLUT_BITMAP_TIMES_ROMAN_24;

#define INT_GLUT_BITMAP_8_BY_13 1
#define INT_GLUT_BITMAP_9_BY_15 2
#define INT_GLUT_BITMAP_TIMES_ROMAN_10  3
#define INT_GLUT_BITMAP_TIMES_ROMAN_24  4
#define INT_GLUT_BITMAP_HELVETICA_10  5
#define INT_GLUT_BITMAP_HELVETICA_12  6
#define INT_GLUT_BITMAP_HELVETICA_18  7

//绕x轴旋转角度
GLfloat xRotAngle=0.0f;
//绕y轴旋转角度
GLfloat yRotAngle=0.0f;
int moveX,moveY;
int spinX = 0;
int spinY = 0;
int des = 0;

// menu status
int menuFlag = 0;

GLdouble rotate_theta = 0;
GLdouble theta = 0;
GLdouble gamma_ = -60;
float xPosition = -1.5;
float zPosition = 0;
int back = 0;

void idle() {
    rotate_theta += 0.001;
    theta += 0.001;
    if (xPosition < 1.2 && back == 0)
        xPosition += 0.003;
    else if (xPosition >= 1.2 && back == 0)
        back = 1;
    else if (xPosition > -1.5 && back == 1)
        xPosition -= 0.003;
    else if (xPosition <= -1.5 && back == 1)
        back = 0;
    zPosition = 0.3*abs(sin(xPosition*20));
    glutPostRedisplay();
}

//画球
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
 
//画半球
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
 
//画长方体
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


void drawCircle() {
    float r = 0.15;
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(0.2);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 50; i++) {
        float theta_ = 2.0f * 3.1415926f * float(i) / float(50);
        float x = r * cosf(theta_);
        float y = r * sinf(theta_);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawCar() {
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glutSolidCube(0.3);//1
    glTranslated(0.3, 0, 0);
    glutSolidCube(0.3);//2
    glTranslated(0.3, 0, 0);
    glutSolidCube(0.3);//3
    glTranslated(-0.15, 0.3, 0);
    glutSolidCube(0.3);//4
    glTranslated(-0.3, 0, 0);
    glutSolidCube(0.3);//5
    glPopMatrix();

    glTranslated(0, -0.2, 0.1);
    drawCircle();
    glTranslated(0.5, 0, 0);
    drawCircle();
    glTranslated(0, 0, -0.2);
    drawCircle();
    glTranslated(-0.5, 0, 0);
    drawCircle();
}

void draw_init(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cos(theta)* cos(gamma_), 0.4*sin(gamma_), sin(theta)*cos(gamma_), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void draw_wall(){
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1);
    glPopMatrix();
}

void draw_chimney(){
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslated(0.4, 1.0, 0);
    glutSolidCube(0.2);
    glPopMatrix();
}

void draw_roof(){
    glPushMatrix();
    glTranslated(0, 0.41, 0);
    glRotated(270, 10, 0, 0);
    glColor3f(0.8, 0, 0);
    glutSolidCone(1, 1, 50, 50);
    glPopMatrix();
}

void draw_window(){
    glBegin(GL_POLYGON);
    glVertex2f(-0.4, 0.2);
    glVertex2f(-0.1, 0.2);
    glVertex2f(-0.1, -0.1);
    glVertex2f(-0.4, -0.1);
    glEnd();
    glPopMatrix();
}

void draw_door(){
    glPushMatrix();
    glTranslated(0, 0, 0.501);
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON);
    glVertex2f(0.1, 0.2);
    glVertex2f(0.4, 0.2);
    glVertex2f(0.4, -0.5);
    glVertex2f(0.1, -0.5);
    glEnd();
}

void draw_Fence() {
    glColor3f(0.8, 1, 0.8);
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
    glVertex3f(1.0, -0.2, -1.0);
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
}

void draw_law(){
    glColor3f(0, 1, 0);
    glBegin(GL_POLYGON);
    glVertex3f(2.0, -0.5, 2.0);
    glVertex3f(-2.0, -0.5, 2.0);
    glVertex3f(-2.0, -0.5, -2.0);
    glVertex3f(2.0, -0.5, -2.0);
    glEnd();
}

void draw_man(){
    //glTranslated(xPosition, -0.15, 1.5);
    glColor3f(0.8, 0.5, 0.8);
    //头
    drawBall(0.2, 0, 0.6, -1.2, SOLID);
    //肩膀
    drawHalfBall(0.11, -0.25,0.4, -1.2, SOLID);
    drawHalfBall(0.11, 0.25,0.4, -1.2, SOLID);
    //身体
    drawSkewed(0.25, 0.8, 0.15, 0, 0, -8, SOLID);
    //胳膊
    drawSkewed(0.1, 0.4, 0.1, 2.45, 0.4, -12, SOLID);
    drawSkewed(0.1, 0.4, 0.1, -2.45, 0.4,-12, SOLID);
    //手
    drawBall(0.06, 0.25, -0.1, -1.2, SOLID);
    drawBall(0.06, -0.25, -0.1, -1.2, SOLID);
    //腿
    drawSkewed(0.12, 0.5, 0.2, 0.6, -0.4, -6, SOLID);
    drawSkewed(0.12, 0.5, 0.2, -0.6, -0.4, -6, SOLID);
    //脚
    drawSkewed(0.15, 0.1, 0.2, 0.6, -4.5, -6, SOLID);
    drawSkewed(0.15, 0.1, 0.2, -0.6, -4.5, -6, SOLID);

}

void draw_sun1(){
    glColor3f(1, 0, 0.1);
    drawBall(0.19, 0, 2, -1.2, SOLID);
}

void draw_sun2(){
    glColor3f(1, 0, 0.1);
    drawBall(0.21, 0, 2.5, -1.3, SOLID);
}

void draw_sun3(){
    glColor3f(1, 0, 0.1);
    drawBall(0.18, 0, 3, -1.1, SOLID);
}

float theta_random=0;
void draw() {
    // draw things
    draw_init();
    draw_wall();
    draw_chimney();
    draw_roof();
    draw_door();
    draw_window();
    draw_Fence();
    draw_law();

    glTranslated(xPosition, -0.15, 1.5);
    drawCar();
    glTranslated(-xPosition, 0.15, -1.5);
    
    glTranslated(0,zPosition+0.2,0);
    draw_man();
    glTranslated(0,-zPosition-0.2,0);
    
    glTranslated(xPosition, -0.15, 1.5);
    glRotatef(sin(rotate_theta)*cos(rotate_theta)*4000, 0.0f, 1.0f,0.0f);
    draw_sun1();
    glRotatef(-sin(rotate_theta)*cos(rotate_theta)*4000, 0.0f, 1.0f,0.0f);
    glTranslated(-xPosition, 0.15, -1.5);
    
    glTranslated(xPosition*0.4, -0.15, 1.5);
    glRotatef(sin(rotate_theta+1)*sin(rotate_theta)*4000, 0.0f, -1.0f,1.0f);
    draw_sun2();
    glRotatef(-sin(rotate_theta+1)*sin(rotate_theta)*2500, 0.0f, -1.0f,1.0f);
    glTranslated(-xPosition*0.4, 0.15, -1.5);
    
    glTranslated(xPosition*0.1, -0.015, 0.15);
    glRotatef(sin(rotate_theta)*cos(rotate_theta-0.5)*2500, 1.0f, 1.0f,0.0f);
    draw_sun3();
    glRotatef(-sin(rotate_theta)*cos(rotate_theta-0.5)*2500, 1.0f, 1.0f,0.0f);
    glTranslated(-xPosition*0.1, 0.15, -1.5);
    
    
    //glClear (GL_COLOR_BUFFER_BIT);
    //for (c = string; *c != '\0'; c++) {
    //        glutBitmapCharacter(font, *c);
    //}
    glColor3f(1.0,1.0,1.0);
    char text[] = {'T','h','e',' ','t','h','r','e','e',' ','b','o','d','y',' ','p','r','o','b','l','e','m'};
    glRasterPos3f(1,2,1);
    for (int k=0;k<24;k++)
        glutBitmapCharacter(font,text[k]);
    glScalef(0.1,0.1,0.0);
    glutSwapBuffers();
    
    glFlush();
}

//按键输入处理回调函数
void specialKey(int key,int x,int y){
    if(key==GLUT_KEY_UP){
        gamma_-=0.2f;
        //y_temp+=0.4f;
        //gluLookAt(cos(theta), 0.4, sin(theta)+y_temp/abs(y_temp), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    }
    else if(key==GLUT_KEY_DOWN){
        gamma_+=0.2f;
        //theta+=0.5f;
        //gluLookAt(cos(theta), 0.4, sin(theta)+y_temp/abs(y_temp), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    }
    else if(key==GLUT_KEY_LEFT){
        theta-=0.3f;
    }
    else if(key==GLUT_KEY_RIGHT){
        theta+=0.3f;
    }
    //重新绘制
    glutPostRedisplay();
}

// 鼠标移动事件
int last_x = -1;
int last_y = -1;
int mouseMove_flag=0;
void mouseMove(int x, int y) {
    if(last_x==-1){
        last_x=x;
    }else if(last_y==-1){
        last_y=y;
    }else{
        theta += (x-last_x)*0.005;
        last_x=x;
        gamma_ -= (y-last_y)*0.005;
        last_y=y;
    }
}
void mouseLeave(int button,int state,int x,int y){
    if(state==0){
        last_x=-1;
        last_y=-1;
    }
}

// Memu
void processMenuStatus(int status, int x, int y)
{
    if (status == GLUT_MENU_IN_USE)
        menuFlag = 1;
    else
        menuFlag = 0;
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

void processNormalKeys(unsigned char key, int xx, int yy)
{
    printf("111");
    switch (key)
    {
    case 27:
        //glutDestroyMenu(mainMenu);
        //glutDestroyMenu(fillMenu);
        //glutDestroyMenu(colorMenu);
        glutDestroyMenu(fontMenu);
        exit(0);
        break;
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
    
    // attach the menu to the right button
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    // this will allow us to know if the menu is active
    glutMenuStatusFunc(processMenuStatus);
}

void init_configure(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("3D Drawing with Visualised Axis");
    glutIdleFunc(idle);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_position[] = { 1.0, 1.0, 0.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3.0, 3.0, -3.0, 3.0, -3.0, 100.0);
    glEnable(GL_DEPTH_TEST);

    //设置按键输入处理回调函数
    glutSpecialFunc(specialKey);
    //鼠标移动事件，鼠标按下并移动时调用
    glutMotionFunc(mouseMove);
    glutMouseFunc(mouseLeave);
    //
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(processNormalKeys);
    createPopupMenus();
}

int main(int argc, char** argv) {
    init_configure(argc,argv);
    glutDisplayFunc(draw);
    glutMainLoop();
}




//----------------------------------------------------------------------
//----------------------------------------------------------------------
//
//  main.cpp
//  well
//
//  Created by Zhaoyang Ma on 2021/11/3.
//
/*
#include <stdio.h>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// 旋转
GLfloat angle1 = 10; //初始化
GLfloat angle2 = -30; //初始化

float bucketPosition = -0.5;
float vapourX = -0.15;
float vapourY = -0.245;
int flag = 0;

void idle() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(0, 1.0, 0.0, 0.0);
    glRotatef(angle2, 0.0, 1.0, 0.0);
    glRotatef(0, 0.0, 0.0, 1.0);
    glRotatef(angle1, 1.0, 0.0, 0.0);
    glRotatef(0, 0.0, 1.0, 0.0);
    glRotatef(0, 0.0, 0.0, 1.0);

    // bucket move
    if (bucketPosition < 0 && flag == 0)
        bucketPosition += 0.05;
    else if (bucketPosition >= 0 && flag == 0)
        flag = 1;
    else if (bucketPosition > -0.5 && flag == 1)
        bucketPosition -= 0.05;
    else if (bucketPosition <= -0.5 && flag == 1)
        flag = 0;
    //vapourPosition = 0.3 * abs(sin(bucketPosition * 2));

    // vapour move
    if (vapourX >= -0.9) {
        vapourX -= 0.03;
        vapourY = - 2*vapourX*vapourX - 2*vapourX - 0.5;
    }
    else {
        vapourX = -0.15;
        vapourY = -0.245;
    }
    

    glutPostRedisplay();
}

void drawRope(GLfloat length) {
    glPushMatrix();
    glLineWidth (3);
    glBegin(GL_LINES);
    glColor3f (0.3, 0.3, 0.3);
    glVertex3f(0.15, 0.5, 0);
    glVertex3f(0.15, length+0.2, 0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f (0.3, 0.3, 0.3);
    glVertex3f(-0.15, 0.5, 0);
    glVertex3f(-0.15, length+0.2, 0);
    glEnd();
    glPopMatrix();

    glBegin(GL_LINES);
    glColor3f (0.3, 0.3, 0.3);
    glVertex3f(1, 0.5, 0);
    glVertex3f(1, -length-0.2, 0);
    glEnd();
    glPopMatrix();
}

//画坠物
void drawWeight() {
    glRotated(90, 1, 0, 0);
    glColor3f(0, 0, 1);
    glutSolidCone(0.1, 0.15, 10, 10);
}
void drawWeight2() {
    glRotatef(90, 1, 0, 0);
    glColor3f(0, 0, 1);
    float r = 0.1;
    int num_segments = 100;
    glLineWidth(5);
    glBegin(GL_TRIANGLE_FAN);
    for (int i=0; i<num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

//画支架
void drawHolder(GLfloat x1, GLfloat z1, GLfloat x2, GLfloat z2) {
    glPushMatrix();
    glLineWidth(3);
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex3f(x1, 0.5, z1);
    glVertex3f(x2, 0.5, z2);
    glEnd();
    glPopMatrix();
}

//水蒸气
void drawVapour() {
    glPushMatrix();
    glColor3f(0.55, 0.85, 1);
    glutSolidSphere(0.05, 5, 5);
    glPopMatrix();
}

void drawBucket() {
    //桶身
    for (float i=0; i<=0.2; i+= 0.001) {
        glPushMatrix();
        glTranslated(0, i, 0);
        glRotatef(90, -1.0, 0.0, 0.0);
        glColor3f(0.49, 0.34, 0.16);
        float r = 0.15;
        int num_segments = 100;
        glLineWidth(3);
        glBegin(GL_LINE_LOOP);
        for (int i=0; i<num_segments; i++) {
            float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
            float x = r * cosf(theta);
            float y = r * sinf(theta);
            glVertex2f(x, y);
        }
        glEnd();
        glPopMatrix();
    }
    //桶底
    glPushMatrix();
    glTranslated(0, 0, 0);
    glRotatef(90, -1.0, 0, 0);
    glColor3f(0.49, 0.34, 0.16);
    float rb = 0.15;
    int num_segments = 100;
    glLineWidth(1);
    glBegin(GL_TRIANGLE_FAN);
    for (int i=0; i<num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = rb * cosf(theta);
        float y = rb * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    //桶水
    glPushMatrix();
    glTranslated(0, 0.15, 0);
    glRotatef(90, -1, 0, 0);
    glColor3f(0.4, 0.7, 1.0);
    float rw = 0.15;
    int num_segments2 = 100;
    glLineWidth(1);
    glBegin(GL_TRIANGLE_FAN);
    for (int i=0; i<num_segments2; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments2);
        float x = rw * cosf(theta);
        float y = rw * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
}

void drawPillar1(GLfloat Tx, GLfloat Ty, GLfloat Tz) {
    glPushMatrix();

    glTranslated(Tx, Ty, Tz);
    glRotatef(90, 0, 1.0, 0);
    glColor3f(0, 0, 0);

    glBegin(GL_POLYGON);
    glVertex2f(-1, -0.5);
    glVertex2f(-1, 0.7);
    glVertex2f(-0.9, 0.7);
    glVertex2f(-0.9, -0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(1, -0.5);
    glVertex2f(1, 0.7);
    glVertex2f(0.9, 0.7);
    glVertex2f(0.9, -0.5);
    glEnd();

    glPopMatrix();
}

void drawPillar2(GLfloat Tx, GLfloat Ty, GLfloat Tz) {
    glPushMatrix();

    glTranslated(Tx, Ty, Tz);
    //glRotatef(90, 0, 1.0, 0);
    glColor3f(0, 0, 0);

    glBegin(GL_POLYGON);
    glVertex2f(-1, -0.5);
    glVertex2f(-1, 0.7);
    glVertex2f(-0.9, 0.7);
    glVertex2f(-0.9, -0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(1, -0.5);
    glVertex2f(1, 0.7);
    glVertex2f(0.9, 0.7);
    glVertex2f(0.9, -0.5);
    glEnd();

    glPopMatrix();
}

// 画滑轮
void drawPully(GLfloat Tx, GLfloat Ty, GLfloat Tz) {
    glPushMatrix();
    glTranslated(Tx, Ty, Tz);
    //glRotated();
    glColor3f(0.3, 0.3, 0.3);
    float r = 0.11;
    int num_segments = 100;
    glLineWidth(5);
    glBegin(GL_TRIANGLE_FAN);
    for (int i=0; i<num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //摄像机视角方向
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    //gluLookAt(1.0, 1.0, 1.0 , 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    //坐标系
    glColor3f (1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(2, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 2, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 2);
    glEnd();

    //画水蒸气
    glPushMatrix();
    glTranslated(vapourX, vapourY, 0);
    drawVapour();

    glPopMatrix();



    //用2D画草地
    glPushMatrix();
    glTranslated(0, -0.502, 0);
    glRotatef(90, -1.0, 0.0, 0.0); //度数，x轴， y轴， z轴
    glColor3f(0.30, 0.62, 0.27);
    glBegin(GL_POLYGON);
    glVertex2f(1, 1);
    glVertex2f(1, -1);
    glVertex2f(-1, -1);
    glVertex2f(-1, 1);
    glEnd();
    glPopMatrix();

    //井
    for (float i=-0.5; i<-0.1; i+= 0.001) {
        glPushMatrix();
        glTranslated(0, i, 0);
        glRotatef(90, -1.0, 0.0, 0.0);
        glColor3f(0.2, 0.2, 0.2);
        float r1 = 0.4;
        int num_segments = 100;
        glLineWidth(1);
        glBegin(GL_LINE_LOOP);
        for (int i=0; i<num_segments; i++) {
            float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
            float x = r1 * cosf(theta);
            float y = r1 * sinf(theta);
            glVertex2f(x, y);
        }
        glEnd();
        glPopMatrix();
    }
    for (float i=-0.5; i<-0.1; i+= 0.001) {
        glPushMatrix();
        glTranslated(0, i, 0);
        glRotatef(90, -1.0, 0.0, 0.0);
        glColor3f(0.2, 0.2, 0.2);
        float r2 = 0.5;
        int num_segments = 100;
        glLineWidth(1);
        glBegin(GL_LINE_LOOP);
        for (int i=0; i<num_segments; i++) {
            float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
            float x = r2 * cosf(theta);
            float y = r2 * sinf(theta);
            glVertex2f(x, y);
        }
        glEnd();
        glPopMatrix();
    }

    for (float r3=-0.5; r3<=-0.4; r3+= 0.001) {
        glPushMatrix();
        glTranslated(0, -0.1, 0);
        glRotatef(90, -1.0, 0.0, 0.0);
        glColor3f(0.2, 0.2, 0.2);
        int num_segments = 100;
        glLineWidth(1);
        glBegin(GL_LINE_LOOP);
        for (int i=0; i<num_segments; i++) {
            float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
            float x = r3 * cosf(theta);
            float y = r3 * sinf(theta);
            glVertex2f(x, y);
        }
        glEnd();
        glPopMatrix();
    }

    //水面
    glPushMatrix();
    glTranslated(0, -0.2, 0);
    glRotatef(90, -1.0, 0.0, 0.0);
    glColor3f(0.49, 0.8, 0.97);
    float r2 = 0.4;
    int num_segments2 = 100;
    glLineWidth(5);
    glBegin(GL_TRIANGLE_FAN);
    for (int i=0; i<num_segments2; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments2);
        float x = r2 * cosf(theta);
        float y = r2 * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslated(0, -0.51, 0);
    glRotatef(90, -1.0, 0.0, 0.0);
    glColor3f(0.49, 0.8, 0.97);
    float r3 = 0.4;
    int num_segments3 = 100;
    glLineWidth(10);
    glBegin(GL_TRIANGLE_FAN);
    for (int i=0; i<num_segments3; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments3);
        float x = r3 * cosf(theta);
        float y = r3 * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    //柱子
    drawPillar1(1.0, 0, 0);
    drawPillar1(-1.0, 0, 0);
    drawPillar1(0.9, 0, 0);
    drawPillar1(-0.9, 0, 0);
    drawPillar2(0, 0, 1.0);
    drawPillar2(0, 0, -1.0);
    drawPillar2(0, 0, 0.9);
    drawPillar2(0, 0, -0.9);

    //顶
    glPushMatrix();
    glTranslated(0, 0.7, 0);
    glRotated(90, 1.0, 0, 0);
    glColor3f(0.79, 0.18, 0.2);
    glBegin(GL_POLYGON);
    glVertex2f(-1, -1);
    glVertex2f(-1, 1);
    glVertex2f(1, 1);
    glVertex2f(1, -1);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.79, 0.18, 0.2);
    glBegin(GL_POLYGON);
    glVertex3f(1, 0.7, -1);
    glVertex3f(1, 0.7, 1);
    glVertex3f(0, 1.2, 1);
    glVertex3f(0, 1.2, -1);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.79, 0.18, 0.2);
    glBegin(GL_POLYGON);
    glVertex3f(-1, 0.7, -1);
    glVertex3f(-1, 0.7, 1);
    glVertex3f(0, 1.2, 1);
    glVertex3f(0, 1.2, -1);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.18, 0.18, 0.18);
    glBegin(GL_POLYGON);
    glVertex3f(-1, 0.7, 0.95);
    glVertex3f(1, 0.7, 0.95);
    glVertex3f(0, 1.2, 0.95);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.18, 0.18, 0.18);
    glBegin(GL_POLYGON);
    glVertex3f(-1, 0.7, -0.95);
    glVertex3f(1, 0.7, -0.95);
    glVertex3f(0, 1.2, -0.95);
    glEnd();
    glPopMatrix();

    //滑轮
    drawPully(0.25, 0.5, 0);
    drawPully(-0.05, 0.5, 0);
    drawPully(0.9, 0.5, 0);

    //滑轮固定
    drawHolder(0.9, -1, 0.9, 1);
    drawHolder(0.25, -1, 0.25, 1);
    drawHolder(0.05, -1, 0.05, 1);
    drawHolder(1, 1, -1, 1);
    drawHolder(1, -1, -1, -1);

    //移动的桶
    glPushMatrix();
    glTranslated(0, bucketPosition, 0);
    drawBucket();
    //glTranslated(0, -bucketPosition, 0);
    glPopMatrix();

    //坠物
    glPushMatrix();
    glTranslated(1, -0.2-bucketPosition, 0);
    drawWeight();
    glPopMatrix();
    //坠物盖
    glPushMatrix();
    glTranslated(1, -0.2-bucketPosition, 0);
    drawWeight2();
    glPopMatrix();

    //静止的绳子
    glPushMatrix();
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-0.05, 0.6, 0);
    glVertex3f(0.9, 0.6, 0);
    glEnd();
    glPopMatrix();
    //移动的绳子
    glPushMatrix();
    drawRope(bucketPosition);
    glPopMatrix();


    glutSwapBuffers();

    glFlush();
}


// 摄像头旋转
void mySpecialKey(int key, int X, int Y) {
    if (key == GLUT_KEY_LEFT) angle2 += 2;
    if (key == GLUT_KEY_RIGHT) angle2 -= 2;

    if (key == GLUT_KEY_UP) angle1 += 2;
    if (key == GLUT_KEY_DOWN) angle1 -= 2;
}

// 鼠标移动事件
int x_final = -1;
int y_final = -1;
//int mouseMove_flag = 0;
void mouseStart(int x, int y) {
    if(x_final == -1){
        x_final = x;
    }else if(y_final == -1) {
        y_final = y;
    }else{
        angle2 += (x - x_final) * 0.5;
        x_final = x;
        angle1 += (y - y_final) * 0.5;
        y_final = y;
    }
}
void mouseEnd(int button, int state, int x, int y) {
    if(state == 0){
        x_final = -1;
        y_final = -1;
    }
}

void init () {
    glClearColor(0.0, 1.0, 1.0, 1.0);
    glColor3f (0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 100.0); // left, right, bottom, top, near, far
// /*
    //加入光源
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_position[] = {-1.0, 1.0, -1.0, 0.0}; // x, y, z, 光源大小
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_FLAT);
// * /
    //鼠标拖动
    glutMotionFunc(mouseStart);
    glutMouseFunc(mouseEnd);

    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Well");
    glutDisplayFunc(display);

    init();

    glutIdleFunc(idle); // 旋转
    glutSpecialFunc(mySpecialKey); //键盘操控

    glutMainLoop();
}
*/




