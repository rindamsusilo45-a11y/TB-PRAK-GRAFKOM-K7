#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const float PI = 3.14159265f;
const float MOVE_SPEED = 0.05f;

float cameraPosX = 0.0f, cameraPosY = 3.0f, cameraPosZ = 12.0f;
float cameraYaw = 0.0f, cameraPitch = -20.0f;

bool keys[256] = {false};
int windowWidth = 1200, windowHeight = 800;
bool lampOn = true; 

GLuint floorTexture;

// Fungsi Load Tekstur (Versi Bersih)
GLuint loadTexture(const char* filename) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); 
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    
    if (data) {
        glBindTexture(GL_TEXTURE_2D, textureID);
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        stbi_image_free(data);
    } else {
        return 0;
    }
    return textureID;
}

void initLighting() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_TEXTURE_2D);
    
  
    floorTexture = loadTexture("textures/rumput.jpg"); 
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
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    GLfloat pos[] = {-5.5f, 5.0f, 3.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
}

void drawMasjid() {
    glColor3f(0.9f, 0.9f, 0.9f);
    glPushMatrix();
    glScalef(4, 2.5, 4);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.4f, 0.7f, 1.0f);
    glPushMatrix();
    glTranslatef(0, 1.6f, 0);
    glutSolidSphere(1.2, 32, 32);
    glPopMatrix();

    glColor3f(0.3f, 0.2f, 0.1f);
    glPushMatrix();
    glTranslatef(0, -0.3f, 2.05f);
    glScalef(0.8f, 1.4f, 0.1f);
    glutSolidCube(1);
    glPopMatrix();
}

void drawBench() {
    glColor3f(0.5f, 0.3f, 0.1f);
    glPushMatrix();
    glScalef(2.5f, 0.2f, 0.8f);
    glutSolidCube(1);
    glPopMatrix();
}

void drawGardenLamp() {
    GLUquadric* q = gluNewQuadric();
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    gluCylinder(q, 0.1, 0.1, 3.5, 16, 16);
    glPopMatrix();
    
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 0.8f);
    glPushMatrix();
    glTranslatef(0, 3.5f, 0);
    glutSolidSphere(0.4, 20, 20);
    glPopMatrix();
    if (lampOn) glEnable(GL_LIGHTING);
    gluDeleteQuadric(q);
}

void drawFloor() {
    glDisable(GL_LIGHTING);
    
    if (floorTexture != 0) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, floorTexture);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    }

    glColor3f(1.0f, 1.0f, 1.0f); 
    
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);   glVertex3f(-25, 0, -25);
    glTexCoord2f(10.0f, 0.0f);  glVertex3f(-25, 0, 25);
    glTexCoord2f(10.0f, 10.0f); glVertex3f(25, 0, 25);
    glTexCoord2f(0.0f, 10.0f);  glVertex3f(25, 0, -25);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    if (lampOn) glEnable(GL_LIGHTING);
}

void updateCamera() {
    float yaw = cameraYaw * PI / 180;
    float pitch = cameraPitch * PI / 180;
    float fx = sin(yaw) * cos(pitch);
    float fy = -sin(pitch);
    float fz = -cos(yaw) * cos(pitch);
    float rx = sin(yaw + PI/2);
    float rz = -cos(yaw + PI/2);

    if (keys['w'] || keys['W']) { cameraPosX += fx * MOVE_SPEED; cameraPosY += fy * MOVE_SPEED; cameraPosZ += fz * MOVE_SPEED; }
    if (keys['s'] || keys['S']) { cameraPosX -= fx * MOVE_SPEED; cameraPosY -= fy * MOVE_SPEED; cameraPosZ -= fz * MOVE_SPEED; }
    if (keys['a'] || keys['A']) { cameraPosX -= rx * MOVE_SPEED; cameraPosZ -= rz * MOVE_SPEED; }
    if (keys['d'] || keys['D']) { cameraPosX += rx * MOVE_SPEED; cameraPosZ += rz * MOVE_SPEED; }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)windowWidth/windowHeight, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float yaw = cameraYaw * PI / 180;
    float pitch = cameraPitch * PI / 180;

    gluLookAt(
        cameraPosX, cameraPosY, cameraPosZ,
        cameraPosX + sin(yaw), cameraPosY - sin(pitch), cameraPosZ - cos(yaw),
        0, 1, 0
    );

    updateLightingLogic();
    drawFloor();

    glPushMatrix();
    glTranslatef(0, 1.25f, 0);
    drawMasjid();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4, 0.4f, 3);
    drawBench();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5.5f, 0, 3);
    drawGardenLamp();
    glPopMatrix();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    keys[key] = true;
    if (key == 'l' || key == 'L') lampOn = !lampOn;
    if (key == 27) exit(0);
}
void keyboardUp(unsigned char key, int x, int y) { keys[key] = false; }

void mouseMotion(int x, int y) {
    static bool firstMouse = true;
    static int lastX, lastY;
    if (firstMouse) { lastX = x; lastY = y; firstMouse = false; }
    cameraYaw += (x - lastX) * 0.2f;
    cameraPitch += (y - lastY) * 0.2f;
    if (cameraPitch > 89) cameraPitch = 89;
    if (cameraPitch < -89) cameraPitch = -89;
    lastX = x; lastY = y;
}

void idle() { updateCamera(); glutPostRedisplay(); }
void reshape(int w, int h) { windowWidth = w; windowHeight = h; glViewport(0, 0, w, h); }

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Tugas Besar Grafkom - Masjid");

    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
    initLighting();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutPassiveMotionFunc(mouseMotion);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}

