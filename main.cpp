
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <GL\gl.h>
#include <cstdlib>
#include <time.h>
#include "variables.h"



//==================================================================== Definir cores
#define AZUL     0.0, 0.0, 1.0, 1.0
#define VERMELHO 1.0, 0.0, 0.0, 1.0
#define AMARELO  1.0, 1.0, 0.0, 1.0
#define VERDE    0.0, 1.0, 0.0, 1.0
#define LARANJA  0.8, 0.6, 0.1, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define GRAY1    0.2, 0.2, 0.2, 1.0
#define GRAY2    0.9, 0.9, 0.9, 1.0
#define PRETO    0.0, 0.0, 0.0, 1.0

#define   PI 3.14159


//================================================================================
//===========================================================Variaveis e constantes

//------------------------------------------------------------ Sistema Coordenadas
GLfloat  xC=50.0, zC=50.0;
GLint    wScreen=800, hScreen=500;
GLfloat obsPY =1.0;
//------------------------------------------------------------ Observador
GLfloat  rVisao=3.8, aVisao=0.5*PI, incVisao=0.1;
GLfloat  angPersp=129.0;
GLfloat  obsPini[] ={1, obsPY, (GLfloat)0.5*xC};
GLfloat  obsPfin[] ={(GLfloat)(obsPini[0]-rVisao*cos(aVisao)), obsPini[1], (GLfloat)(obsPini[2]-rVisao*sin(aVisao))};
bool luzLigada = true;
bool luzBola = true;
int lancesESC = 8;

int numDegraus[8];
GLboolean fog = false;

int  facesESC   = 6;
int  degrausESC= 3;
static GLuint    poligono[] = {};


static GLfloat vertices[]={
    5, 0, 0,
    -5, 0, 0,
    -5, 2, 0,
    5, 2, 0,
    
    5, 2, 0,
    -5, 2, 0,
    -5, 2, -5,
    5, 2, -5,
    
    -5, 0, -5,
    -5, 0, -0,
    -5, 2, -0,
    -5, 2, -5,
    
    5, 0, -5,
    5, 0, -0,
    5, 2, -0,
    5, 2, -5,
    
    5, 0, 0,
    -5, 0, 0,
    -5, 0, -5,
    5, 0, -5,
    
    5, 0, -2,
    -5, 0, -2,
    -5, 2, -2,
    5, 2, -2,
};
static GLfloat normais[] = {
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    
    -1.0, 0.0, 0.0,
    -1.0, 0.0, 0.0,
    -1.0, 0.0, 0.0,
    -1.0, 0.0, 0.0,
    
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    
    0.0, 1.0, 0.0,
    0.0,1.0, 0.0,
    0.0,1.0, 0.0,
    0.0,1.0, 0.0,
    
    0.0, 1.0, 0.0,
    0.0,1.0, 0.0,
    0.0,1.0, 0.0,
    0.0,1.0, 0.0
};
static GLfloat cores[]={
    0.000000, 1.000000, 0.000000,
    0.000000, 1.000000, 0.000000,
    0.000000, 1.000000, 0.000000,
    0.000000, 1.000000, 0.000000,
    
    0.000000, 0.000000, 1.000000,
    0.000000, 0.000000, 1.000000,
    0.000000, 0.000000, 1.000000,
    0.000000, 0.000000, 1.000000,
    
    1.000000, 0.000000, 0.000000,
    1.000000, 0.000000, 0.000000,
    1.000000, 0.000000, 0.000000,
    1.000000, 0.000000, 0.000000,
    
    0.000000, 1.000000, 0.000000,
    0.000000, 1.000000, 0.000000,
    0.000000, 1.000000, 0.000000,
    0.000000, 1.000000, 0.000000,
    
    0.000000, 0.000000, 1.000000,
    0.000000, 0.000000, 1.000000,
    0.000000, 0.000000, 1.000000,
    0.000000, 0.000000, 1.000000,
    
    0.000000, 0.000000, 1.000000,
    0.000000, 0.000000, 1.000000,
    0.000000, 0.000000, 1.000000,
    0.000000, 0.000000, 1.000000
};


//=================================================================== TEXTURAS

//------------------------------------------------------------ Skybox
GLUquadricObj*  bola = gluNewQuadric ( );

//------------------------------------------------------------ Texturas
GLuint   texture[5];
GLuint skybox[7];
RgbImage imag;
static GLfloat arrayTexture[]={
    0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1,  0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1
};

void initLight(){
    GLfloat corDifusa [ ] ={0.0,0.4,1.0,0.0};
    GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat spotLight [ ] ={0.0,0.0,1.0,0.7};
    GLfloat angulo =20.0;
    
    float pos[]={10,20,20};
    glEnable(GL_LIGHTING);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3,GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, normais);
    glPointSize(2.0);
    glClearColor(0.0,0.0,0.0,0.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, whitePlasticAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whitePlasticDif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, whitePlasticSpec);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glEnable(GL_LIGHT0);
    
    //glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotLight);
    /*
     glLightfv(GL_LIGHT1, GL_POSITION, obsPfin);
     glEnable(GL_LIGHT1);*/
    
    glFrontFace(GL_CCW);
    glShadeModel(GL_SMOOTH);
    
}


//================================================================================
//=========================================================================== INIT
//================================================================================
void initTexturas()
{
    //----------------------------------------- Chao
    glGenTextures(1, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    imag.LoadBmpFile("textures/Grass01.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
    glGenTextures(1, &texture[1]);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    imag.LoadBmpFile("textures/brick.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
    glGenTextures(1, &texture[2]);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    imag.LoadBmpFile("textures/pedra.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
    glGenTextures(1, &texture[3]);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    imag.LoadBmpFile("textures/Grass01.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
    glGenTextures(1, &texture[4]);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    imag.LoadBmpFile("textures/brick.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    // Enable color material mode:
    // The ambient and diffuse color of the front faces will track the color set by glColor().
    glEnable(GL_BLEND); // Enable blending.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    ////////////////////////skybox
    
}

void initSkybox(){
    
    //skybox bottom
    glGenTextures(1, &skybox[0]);
    glBindTexture(GL_TEXTURE_2D, skybox[0]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    imag.LoadBmpFile("skybox/floor.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
    //skybox top
    glGenTextures(1, &skybox[1]);
    glBindTexture(GL_TEXTURE_2D, skybox[1]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    imag.LoadBmpFile("skybox/left.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
    //skybox right
    glGenTextures(1, &skybox[2]);
    glBindTexture(GL_TEXTURE_2D, skybox[2]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    imag.LoadBmpFile("skybox/sky.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
    //skybox left
    glGenTextures(1, &skybox[3]);
    glBindTexture(GL_TEXTURE_2D, skybox[3]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    imag.LoadBmpFile("skybox/front.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
    //skybox front
    glGenTextures(1, &skybox[4]);
    glBindTexture(GL_TEXTURE_2D, skybox[4]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    imag.LoadBmpFile("skybox/back.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
    //skybox back
    glGenTextures(1, &skybox[5]);
    glBindTexture(GL_TEXTURE_2D, skybox[5]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    imag.LoadBmpFile("skybox/right.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
    
    glGenTextures(1, &skybox[6]);
    glBindTexture(GL_TEXTURE_2D, skybox[6]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    imag.LoadBmpFile("skybox/floor.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 imag.GetNumCols(),
                 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
}

//================================================================================
//================== OBJECTOS
//================================================================================

void drawSkybox(){
    glPushMatrix();
    glTranslatef (0, 0, 100);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,skybox[4]);
    glColor3f(1.0,1.0,1.0);
    
    glBegin(GL_POLYGON);//back
    glTexCoord2f(1.0f,0.0f);  glVertex3f(200, 0, 0);
    glTexCoord2f(0.0f,0.0f);  glVertex3f(-200, 0, 0);
    glTexCoord2f(0.0f,1.0f);  glVertex3f(-200, 200, 0);
    glTexCoord2f(1.0f,1.0f);  glVertex3f(200, 200, 0);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,skybox[2]);
    
    glBegin(GL_POLYGON);//top
    glTexCoord2f(0.0f,0.0f);glVertex3f(200, 200, 0);
    glTexCoord2f(1.0f,0.0f);glVertex3f(-200, 200, 0);
    glTexCoord2f(1.0,1.0f);glVertex3f(-200, 200, -200);
    glTexCoord2f(0.0,1.0);glVertex3f(200, 200, -200);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,skybox[3]);
    
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f,0.0f);  glVertex3f(-200, 0, -200);
    glTexCoord2f(1.0f,0.0f);  glVertex3f(-200, 0, 0);
    glTexCoord2f(1.0f,1.0f);  glVertex3f(-200, 200, 0);
    glTexCoord2f(0.0f,1.0f);  glVertex3f(-200, 200, -200);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,skybox[1]);
    
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f,0.0f);glVertex3f(200, 0, -200);
    glTexCoord2f(0.0f,0.0f);glVertex3f(200, 0, 0);
    glTexCoord2f(0.0f,1.0f);glVertex3f(200, 200, 0);
    glTexCoord2f(1.0f,1.0f);glVertex3f(200, 200, -200);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,skybox[6]);
    
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f,0.0f);glVertex3f(200, 0, 0);
    glTexCoord2f(0.0f,1.0f);glVertex3f(-200, 0, 0);
    glTexCoord2f(1.0f,1.0f);glVertex3f(-200, 0, -200);
    glTexCoord2f(1.0f,0.0f);glVertex3f(200, 0, -200);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,skybox[5]);
    
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f,0.0f);  glVertex3f(200, 0, -200);
    glTexCoord2f(0.0f,0.0f);  glVertex3f(-200, 0, -200);
    glTexCoord2f(0.0f,1.0f);  glVertex3f(-200, 200, -200);
    glTexCoord2f(1.0f,1.0f);  glVertex3f(200, 200, -200);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glPopMatrix();
}

void drawChao(){
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texture[0]);
    GLfloat coef_shy = 2.0;
    glMaterialfv (GL_FRONT, GL_AMBIENT, greenRubberAmb);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, greenRubberDif);
    glMaterialfv (GL_FRONT, GL_SPECULAR, greenRubberSpec);
    glMaterialfv (GL_FRONT, GL_SHININESS, &coef_shy);
    
    glPushMatrix();
    
    glColor4f(LARANJA);
    glTranslatef(0,-5,0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3i( -xC,  0, -xC );glNormal3f(0.0f,1.0f,0.0f);
    glTexCoord2f(30.0f, 0.0f); glVertex3i( -xC,   0,  xC );glNormal3f(0.0f,1.0f,0.0f);
    glTexCoord2f(30.0f, 30.0f); glVertex3i(  xC,   0,  xC);glNormal3f(0.0f,1.0f,0.0f);
    glTexCoord2f(0.0f, 30.0f); glVertex3i(  xC,     0,  -xC);glNormal3f(0.0f,1.0f,0.0f);
    glEnd();
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
}

void drawBall()
{
    GLfloat no_mat[] = {0.6, 0.5, 0.6, 0.2};
    GLfloat mat_ambient[] = { 0.4, 0.5, 0, 1.0 };
    GLfloat mat_diffuse[] = { 0.4, 0.2, 0, 1.0 };
    GLfloat mat_specular[] = { 0.774597, 0.774597, 0.774597, 1.0 };
    GLfloat mat_shine = 26;
    
    glMaterialfv (GL_FRONT, GL_AMBIENT, whitePlasticAmb);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, whitePlasticDif);
    glMaterialfv (GL_FRONT, GL_SPECULAR, whitePlasticSpec);
    glMaterialf (GL_FRONT, GL_SHININESS, mat_shine);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    
    glPushMatrix();
    glTranslatef (obsPfin[0], obsPfin[1], obsPfin[2]);
    glColor4d(AMARELO);
    glNormal3f(0,0,1);
    
    glutSolidSphere(2, 10, 10);
    glPopMatrix();
    
    
}

void drawLights(int x, int z){
  
  glPushMatrix();
  glTranslatef(x, 0, z);

  glColor4f(1.0,1.0,0.0,1.0);
  //glRotatef(-90,1,0,0);
  
  GLUquadric *quadric;
  quadric = gluNewQuadric();
  gluQuadricNormals(quadric, GLU_SMOOTH);
  
  gluCylinder(quadric,0.05,0.05,5,50,50);

  //glTranslatef(0,5,0);
  
  //gluCylinder(quadric,0.05,0.05,5,50,50);

  glPopMatrix();


}

void drawEscada()
{
    GLfloat cor [] = {0.0,0.0,0.0,1.0};
    glPushMatrix();
    glTranslatef ( 1, 0, 1);
    glEnable(GL_TEXTURE_2D);
    
    for(int k=0 ; k<lancesESC; k++){
        for(int j=0; j<numDegraus[k]; j++){
            for( int p = 0; p < facesESC; p++ ){
                if (p == 1)
                    glBindTexture(GL_TEXTURE_2D,texture[1]);
                else if (p == 2)
                    glBindTexture(GL_TEXTURE_2D,texture[2]);
                else
                    glBindTexture(GL_TEXTURE_2D,texture[3]);
                
                
                poligono[0]= p*4+0;
                poligono[1]= p*4+1 ;
                poligono[2]= p*4+2 ;
                poligono[3]= p*4+3 ;
                glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, poligono);
            }
            //parede
            
            glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, poligono);
            
            glTranslatef ( 0, 2, -5);
            
        }
        glBindTexture(GL_TEXTURE_2D,texture[4]);
        poligono[0]= 4*4+0;
        poligono[1]= 4*4+1 ;
        poligono[2]= 4*4+2 ;
        poligono[3]= 4*4+3 ;
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, poligono);
        
        glTranslatef(-5, 0,0);
        glRotatef(90, 0, 1, 0);
        for(int j=0; j<numDegraus[k]; j++){
            for( int p = 0; p < facesESC; p++ ){
                if (p == 1)
                    glBindTexture(GL_TEXTURE_2D,texture[1]);
                else if (p == 2)
                    glBindTexture(GL_TEXTURE_2D,texture[2]);
                else
                    glBindTexture(GL_TEXTURE_2D,texture[2]);
                
                poligono[0]= p*4+0;
                poligono[1]= p*4+1 ;
                poligono[2]= p*4+2 ;
                poligono[3]= p*4+3 ;
                
                glDisable(GL_CULL_FACE);
                glShadeModel(GL_SMOOTH);
                glPolygonMode(GL_FRONT, GL_FILL);
                
                glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
                glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
                
                glEnableClientState(GL_VERTEX_ARRAY);
                
                glEnableClientState(GL_NORMAL_ARRAY);
                
                glVertexPointer(3,GL_FLOAT,0,vertices);
                glNormalPointer(GL_FLOAT,0,normais);
                
                glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, poligono);
                
            }
            glTranslatef ( 0, 2, -5);
            
        }
        glBindTexture(GL_TEXTURE_2D,texture[4]);
        poligono[0]= 4*4+0;
        poligono[1]= 4*4+1 ;
        poligono[2]= 4*4+2 ;
        poligono[3]= 4*4+3 ;
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, poligono);
        
        glTranslatef(-5, 0,0);
        glRotatef(90, 0, 1, 0);
    }
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
}

void init(void) {
    glClearColor(WHITE);
    glShadeModel(GL_SMOOTH);
    initSkybox();
    initTexturas();
    glEnable(GL_DEPTH_TEST);
    
    //------------------------------- ESCADA
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glEnableClientState(GL_VERTEX_ARRAY);
    glNormalPointer(GL_FLOAT, 0, normais);
    glEnableClientState(GL_NORMAL_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, cores);
    glEnableClientState(GL_COLOR_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, arrayTexture);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    //--------------Luzes
    glEnable(GL_COLOR_MATERIAL);
    glEnable (GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    initLight();
    //glLightModel(GL_LIGHT_MODEL_AMBIENT, {0.5, 0.8, 0.3});
    
 
}

void drawFog(){
  GLfloat colorN[3] = {0.8,0.8,0.8};
  glFogfv(GL_FOG_COLOR, colorN); //Cor do nevoeiro
  glFogi(GL_FOG_MODE, GL_EXP); //Equa‹o do nevoeiro - linear
  glFogf(GL_FOG_START, 40.0); // Dist‰ncia a que ter‡ in’cio o nevoeiro
  glFogf(GL_FOG_END, 60.0); // Dist‰ncia a que o nevoeiro terminar‡
  glFogf (GL_FOG_DENSITY, 0.02);
 
}

GLvoid resize(GLsizei width, GLsizei height)
{
    wScreen=width;
    hScreen=height;
    glViewport( 0, 0, wScreen,hScreen );
    glutPostRedisplay();
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glViewport (0, 0, wScreen, hScreen);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angPersp, (float)wScreen/hScreen, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(obsPini[0], obsPini[1]+5.5, obsPini[2], obsPfin[0], obsPfin[1], obsPfin[2], 0, 1, 0);
    
    drawSkybox();
    drawBall();
    drawLights(50, 20);
    //drawChao();    
    drawEscada();
    drawFog();
    glutSwapBuffers();
    
}


void updateVisao(int caso ){
    
    if(caso==1){
        obsPini[0]=obsPfin[0]+rVisao*cos(aVisao);
        obsPini[2]=obsPfin[2]+rVisao*sin(aVisao);
    }
    glutPostRedisplay();
}

void updateVisaoSubida(){
    obsPfin[1] = obsPini[1];
    glutPostRedisplay();
}



//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y){
	printf("tecla %d\n", key);
    switch (key) {
    	case 97:
            aVisao+=PI/2;
            updateVisao(1);
            break;
        case 100:
            aVisao-=PI/2;
            updateVisao(1);
            break;
        case 32:
            obsPini[1] += 2;
            updateVisaoSubida();
            break;
        case 108:
            if(luzLigada){
                luzLigada=false;
                glDisable(GL_LIGHT0);
            }
            else{
                luzLigada=true;
                glEnable(GL_LIGHT0);
            }
            glutPostRedisplay();
            break;
            
        case 120:
            obsPini[1] -= 2;
            updateVisaoSubida();
            break;
            
        case 105:
            if(luzBola){
                luzBola=false;
                glDisable(GL_LIGHT1);
            }
            else{
                luzBola=true;
                glEnable(GL_LIGHT1);
            }
            glutPostRedisplay();
            break;
            //--------------------------- Escape
        case 102:
        	fog = !fog;
        	 if(fog)glEnable(GL_FOG);
  else glDisable(GL_FOG);
        	glutPostRedisplay();
			break;
		case 27:
            exit(0);
            break;
        
    }
}

void esquerda(int value){
    obsPfin[0]-=value;
    obsPini[0]-=value;
    updateVisao(0);
}

void direita(int value){
    obsPfin[0]+=value;
    obsPini[0]+=value;
    updateVisao(0);
}

void avanca(int value){
    obsPfin[2]-=value;
    obsPini[2]-=value;
    updateVisao(0);
}

void retrocede(int value){
    obsPfin[2]+=value;
    obsPini[2]+=value;
    updateVisao(0);
}

void teclasNotAscii(int key, int x, int y)
{
    int value = PI/2;
    
    if(cos(aVisao)<=cos(3*PI/4) && cos(aVisao)<=cos(5*PI/4) && sin(aVisao)<=sin(3*PI/4) && sin(aVisao)>= sin(5*PI/4)){
        if(key == GLUT_KEY_UP){
            key = GLUT_KEY_RIGHT;
        }
        else if(key == GLUT_KEY_DOWN){
            key = GLUT_KEY_LEFT;
        }
        else if(key == GLUT_KEY_LEFT){
            key = GLUT_KEY_UP;
        }
        else if(key == GLUT_KEY_RIGHT){
            key = GLUT_KEY_DOWN;
        }
    }
    else if(cos(aVisao)>=cos(5*PI/4) && cos(aVisao) <= cos(7*PI/4) && sin(aVisao)<= sin(5*PI/4) && sin(aVisao)<=sin(7*PI/4)){
        if(key == GLUT_KEY_UP){
            key = GLUT_KEY_DOWN;
        }
        else if(key == GLUT_KEY_DOWN){
            key = GLUT_KEY_UP;
        }
        else if(key == GLUT_KEY_LEFT){
            key = GLUT_KEY_RIGHT;
        }
        else if(key == GLUT_KEY_RIGHT){
            key = GLUT_KEY_LEFT;
        }
    }
    else if(cos(aVisao)>=cos(PI/4) && cos(aVisao)>=cos(7*PI/4) && sin(aVisao)>=sin(7*PI/4) && sin(aVisao)<=sin(PI/4)){
        if(key == GLUT_KEY_UP){
            key = GLUT_KEY_LEFT;
        }
        else if(key == GLUT_KEY_DOWN){
            key = GLUT_KEY_RIGHT;
        }
        else if(key == GLUT_KEY_LEFT){
            key = GLUT_KEY_DOWN;
        }
        else if(key == GLUT_KEY_RIGHT){
            key = GLUT_KEY_UP;
        }
    }
    if(key == GLUT_KEY_UP) {
        avanca(value);
    }
    if(key == GLUT_KEY_DOWN) {
        retrocede(value);
    }
    if(key == GLUT_KEY_LEFT){
        esquerda(value);
    }
    if(key == GLUT_KEY_RIGHT){
        direita(value);
    }
}

void initializeRandomVariables(){
    srand (time(NULL));
    for(int i = 0; i < lancesESC; i++){
        numDegraus[i] = rand() %6 + 3;
    }
    //for(int i = 0; i < lancesESC; i++){
    //	printf("%d", numDegraus[i]);
    //}
}
// ===================================================== sistema de particulas



//======================================================= MAIN
int main(int argc, char** argv){
    initializeRandomVariables();
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize (wScreen, hScreen);
    glutInitWindowPosition (400, 100);
    glutCreateWindow ("Escadas");
    
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(teclasNotAscii);
    
    glutMainLoop();
    
    return 0;
}

