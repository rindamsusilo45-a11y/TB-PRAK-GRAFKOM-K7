#include <GL/freeglut.h>
#include <cmath>

/* =====================================================
   KONSTANTA & SETTING KAMERA
   ===================================================== */
const float PI = 3.14159265f;
const float MOVE_SPEED = 0.1f;

float cameraPosX = 0.0f, cameraPosY = 3.0f, cameraPosZ = 12.0f;
float cameraYaw = 0.0f, cameraPitch = -20.0f;

float rotAngle = 0.0f;
bool keys[256] = {false};


/* =====================================================
   SISTEM PENCAYAHAN
   ===================================================== */
bool lampOn = true;
float lampScale = 1.0f;

void initLighting() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void updateLightingLogic() {
    if (!lampOn) {
        glDisable(GL_LIGHTING);
        return;
    }

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat pos[] = {-5.5f, 5.0f, 3.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
}


/* =====================================================
   OBJEK MOBIL
   ===================================================== */
float mobilPos = 12.0f;
bool mobilMaju = true;

void drawMobil() {
    glColor3f(0.7f, 0.0f, 0.0f);
    glPushMatrix();
        glScalef(1.0f, 0.4f, 1.8f);
        glutSolidCube(1.0);
    glPopMatrix();

    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix();
        glTranslatef(0.0f, 0.35f, -0.1f);
        glScalef(0.8f, 0.4f, 0.9f);
        glutSolidCube(1.0);
    glPopMatrix();

    glColor3f(0,0,0);
    float rX[4] = {-0.5f, 0.5f, -0.5f, 0.5f};
    float rZ[4] = {-0.6f, -0.6f, 0.6f, 0.6f};
    for(int i=0;i<4;i++){
        glPushMatrix();
            glTranslatef(rX[i], -0.2f, rZ[i]);
            glutSolidSphere(0.18, 10, 10);
        glPopMatrix();
    }
}


/* =====================================================
   STRUKTUR MASJID
   ===================================================== */
void drawMenara(float x, float z) {
    GLUquadric* q = gluNewQuadric();

    glColor3f(0.85f, 0.85f, 0.85f);
    glPushMatrix();
        glTranslatef(x, -1.25f, z);
        glRotatef(-90, 1, 0, 0);
        gluCylinder(q, 0.3, 0.3, 3.5, 16, 16);
    glPopMatrix();

    glColor3f(0.4f, 0.7f, 1.0f);
    glPushMatrix();
        glTranslatef(x, 2.25f, z);
        glutSolidSphere(0.35, 16, 16);
    glPopMatrix();

    gluDeleteQuadric(q);
}

void drawWindow(float x, float y, float z) {
    glColor3f(0.1f,0.1f,0.1f);
    glPushMatrix();
        glTranslatef(x,y,z);
        glScalef(0.7f,1.1f,0.05f);
        glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.5f,0.8f,1.0f);
    glPushMatrix();
        glTranslatef(x,y,z+0.03f);
        glScalef(0.6f,1.0f,0.02f);
        glutSolidCube(1);
    glPopMatrix();

    glDisable(GL_LIGHTING);
    glColor3f(0.1f,0.1f,0.1f);
    glPushMatrix();
        glTranslatef(x,y,z+0.05f);
        glBegin(GL_LINES);
            glVertex3f(-0.3f,0,0); glVertex3f(0.3f,0,0);
            glVertex3f(0,-0.5f,0); glVertex3f(0,0.5f,0);
        glEnd();
    glPopMatrix();
    if(lampOn) glEnable(GL_LIGHTING);
}

void drawMasjid() {
    glColor3f(0.9f,0.9f,0.9f);
    glPushMatrix();
        glScalef(4,2.5,4);
        glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.4f,0.7f,1.0f);
    glPushMatrix();
        glTranslatef(0,1.6f,0);
        glutSolidSphere(1.2,32,32);
    glPopMatrix();

    drawMenara(-1.8f,-1.8f);
    drawMenara( 1.8f,-1.8f);
    drawMenara(-1.8f, 1.8f);
    drawMenara( 1.8f, 1.8f);

    glColor3f(0.2f,0.1f,0.0f);
    glPushMatrix();
        glTranslatef(0,-0.3f,2.02f);
        glScalef(0.8f,1.4f,0.1f);
        glutSolidCube(1);
    glPopMatrix();

    drawWindow(-1.2f,0.1f,2.02f);
    drawWindow( 1.2f,0.1f,2.02f);
}


/* =====================================================
   KURSI TAMAN
   ===================================================== */
void drawBench() {
    glColor3f(0.4f,0.25f,0.1f);
    glPushMatrix();
        glScalef(2.0f,0.15f,0.7f);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,0.4f,-0.3f);
        glScalef(2.0f,0.7f,0.1f);
        glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.1f,0.1f,0.1f);
    float kX[4]={-0.8f,0.8f,-0.8f,0.8f};
    float kZ[4]={-0.25f,-0.25f,0.25f,0.25f};
    for(int i=0;i<4;i++){
        glPushMatrix();
            glTranslatef(kX[i],-0.4f,kZ[i]);
            glScalef(0.1f,0.7f,0.1f);
            glutSolidCube(1);
        glPopMatrix();
    }
}


/* =====================================================
   LAMPU TAMAN (BOLA BISA DI-SCALE)
   ===================================================== */
void drawGardenLamp() {
    GLUquadric* q = gluNewQuadric();

    glColor3f(0.15f,0.15f,0.15f);
    glPushMatrix();
        glRotatef(-90,1,0,0);
        gluCylinder(q,0.08,0.08,3.0,16,16);
    glPopMatrix();

    glDisable(GL_LIGHTING);
    glColor3f(1.0f,1.0f,0.7f);
    glPushMatrix();
        glTranslatef(0,3.0f,0);
        glScalef(lampScale,lampScale,lampScale);
        glutSolidSphere(0.35,20,20);
    glPopMatrix();

    if(lampOn) glEnable(GL_LIGHTING);
    gluDeleteQuadric(q);
}


/* =====================================================
   BULAN BERPUTAR
   PJ: Dicki
   ===================================================== */
void drawMoon() {
    glDisable(GL_LIGHTING);

    glPushMatrix();
        glRotatef(rotAngle, 0, 1, 0);
        glTranslatef(0.0f, 8.5f, 0.0f);

        glColor3f(1.0f, 1.0f, 0.85f);
        glutSolidSphere(0.4, 20, 20);

        glTranslatef(0.15f, 0.1f, 0.0f);
        glColor3f(0.05f, 0.05f, 0.1f);
        glutSolidSphere(0.4, 20, 20);
    glPopMatrix();

    if (lampOn) glEnable(GL_LIGHTING);
}


/* =====================================================
   GARIS PARKIRAN MOBIL
   ===================================================== */
void drawParkingLines() {
    glDisable(GL_LIGHTING);
    glColor3f(1.0f,1.0f,1.0f);

    float startX = -2.0f;
    float zPos = 6.0f;

    for(int i=0;i<3;i++){
        glBegin(GL_QUADS);
            glVertex3f(startX + i*1.9f, 0.02f, zPos);
            glVertex3f(startX + i*1.9f + 0.1f, 0.02f, zPos);
            glVertex3f(startX + i*1.9f + 0.1f, 0.02f, zPos+4.0f);
            glVertex3f(startX + i*1.9f, 0.02f, zPos+4.0f);
        glEnd();
    }

    if(lampOn) glEnable(GL_LIGHTING);
}


/* =====================================================
   LANTAI
   ===================================================== */
void drawFloor() {
    if(lampOn) glEnable(GL_LIGHTING); else glDisable(GL_LIGHTING);

    glColor3f(0.12f,0.12f,0.12f);
    glBegin(GL_QUADS);
        glNormal3f(0,1,0);
        glVertex3f(-20,0,-20);
        glVertex3f(-20,0,20);
        glVertex3f(20,0,20);
        glVertex3f(20,0,-20);
    glEnd();
}


/* =====================================================
   DISPLAY
   ===================================================== */
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float yaw = cameraYaw * PI / 180;
    float pitch = cameraPitch * PI / 180;

    gluLookAt(
        cameraPosX, cameraPosY, cameraPosZ,
        cameraPosX + sin(yaw),
        cameraPosY - sin(pitch),
        cameraPosZ - cos(yaw),
        0,1,0
    );

    updateLightingLogic();
    drawFloor();
    drawParkingLines();
    drawMoon();

    glPushMatrix();
        glTranslatef(0,1.25f,0);
        drawMasjid();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-5.0f,0.75f,4.0f);
        drawBench();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-6.5f,0,4.0f);
        drawGardenLamp();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.8f,0.25f,mobilPos);
        drawMobil();
    glPopMatrix();

    glutSwapBuffers();
}


/* =====================================================
   INPUT & UPDATE
   ===================================================== */
void idle() {
    rotAngle += 0.5f;

    if(mobilMaju){
        mobilPos -= 0.015f;
        if(mobilPos <= 6.0f) mobilMaju=false;
    } else {
        mobilPos += 0.015f;
        if(mobilPos >= 14.0f) mobilMaju=true;
    }

    float yaw = cameraYaw * PI / 180;
    float pitch = cameraPitch * PI / 180;

    float fx = sin(yaw)*cos(pitch);
    float fy = -sin(pitch);
    float fz = -cos(yaw)*cos(pitch);
    float rx = sin(yaw + PI/2);
    float rz = -cos(yaw + PI/2);

    if(keys['w']||keys['W']){ cameraPosX+=fx*MOVE_SPEED; cameraPosY+=fy*MOVE_SPEED; cameraPosZ+=fz*MOVE_SPEED; }
    if(keys['s']||keys['S']){ cameraPosX-=fx*MOVE_SPEED; cameraPosY-=fy*MOVE_SPEED; cameraPosZ-=fz*MOVE_SPEED; }
    if(keys['a']||keys['A']){ cameraPosX-=rx*MOVE_SPEED; cameraPosZ-=rz*MOVE_SPEED; }
    if(keys['d']||keys['D']){ cameraPosX+=rx*MOVE_SPEED; cameraPosZ+=rz*MOVE_SPEED; }

    glutPostRedisplay();
}

void keyboard(unsigned char k,int,int){
    keys[k]=true;
    if(k=='l'||k=='L') lampOn=!lampOn;
    if(k=='+'||k=='=') lampScale+=0.1f;
    if(k=='-'){ lampScale-=0.1f; if(lampScale<0.1f) lampScale=0.1f; }
    if(k==27) exit(0);
}
void keyboardUp(unsigned char k,int,int){ keys[k]=false; }

void mouseMotion(int x,int y){
    static bool first=true;
    static int lx,ly;
    if(first){ lx=x; ly=y; first=false; }
    cameraYaw += (x-lx)*0.2f;
    cameraPitch += (y-ly)*0.2f;
    if(cameraPitch>89) cameraPitch=89;
    if(cameraPitch<-89) cameraPitch=-89;
    lx=x; ly=y;
}

void reshape(int w,int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,(float)w/h,0.1,100);
    glMatrixMode(GL_MODELVIEW);
}


/* =====================================================
   MAIN
   ===================================================== */
int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(1200,800);
    glutCreateWindow("Masjid 3D");

    initLighting();
    glClearColor(0.05f,0.05f,0.1f,1.0f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutPassiveMotionFunc(mouseMotion);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}

