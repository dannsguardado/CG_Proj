
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL\glut.h>
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
GLfloat  angPersp=109.0;
GLfloat  obsPini[] ={1, obsPY, (GLfloat)0.5*xC};
GLfloat  obsPfin[] ={(GLfloat)(obsPini[0]-rVisao*cos(aVisao)), obsPini[1], (GLfloat)(obsPini[2]-rVisao*sin(aVisao))};


int lancesESC = 8;

int numDegraus[8];

int   facesESC   = 4;		
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
	0.000000, 0.000000, 1.000000
};


//=================================================================== TEXTURAS

//------------------------------------------------------------ Skybox
GLUquadricObj*  bola = gluNewQuadric ( );

//------------------------------------------------------------ Texturas
GLuint   texture[4];
GLuint skybox[7];
RgbImage imag;
static GLfloat arrayTexture[]={ 
0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1,  0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1
};



//================================================================================
//=========================================================================== INIT
//================================================================================
void initTexturas()
{   
	//----------------------------------------- Chao
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	imag.LoadBmpFile("textures/grass01.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);  
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
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
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
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
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
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
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
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());  
		
		
		
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
  glTranslatef (0, 0, 50);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,skybox[4]);
  glColor3f(1.0,1.0,1.0);
  
  glBegin(GL_POLYGON);//back
  glTexCoord2f(1.0f,0.0f);  glVertex3f(100, 0, 0); 
  glTexCoord2f(0.0f,0.0f);  glVertex3f(-100, 0, 0); 
  glTexCoord2f(0.0f,1.0f);  glVertex3f(-100, 100, 0); 
  glTexCoord2f(1.0f,1.0f);  glVertex3f(100, 100, 0); 
  glEnd();
  
  glDisable(GL_TEXTURE_2D);
  glEnable(GL_TEXTURE_2D);  
  glBindTexture(GL_TEXTURE_2D,skybox[2]);
  
  glBegin(GL_POLYGON);//top
  glTexCoord2f(0.0,0.0);glVertex3f(100, 100, 0);
  glTexCoord2f(1.0,0.0);glVertex3f(-100, 100, 0);
  glTexCoord2f(1.0,1.0);glVertex3f(-100, 100, -100);
  glTexCoord2f(0.0,1.0);glVertex3f(100, 100, -100);
  glEnd();

  glDisable(GL_TEXTURE_2D);
  glEnable(GL_TEXTURE_2D);  
  glBindTexture(GL_TEXTURE_2D,skybox[3]);
  
  glBegin(GL_POLYGON);
  glTexCoord2f(0.0f,0.0f);  glVertex3f(-100, 0, -100);
  glTexCoord2f(1.0f,0.0f);  glVertex3f(-100, 0, -0);
  glTexCoord2f(1.0f,1.0f);  glVertex3f(-100, 100, -0);
  glTexCoord2f(0.0f,1.0f);  glVertex3f(-100, 100, -100);
  glEnd();
  
  glDisable(GL_TEXTURE_2D);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,skybox[1]);
  
  glBegin(GL_POLYGON);
  glTexCoord2f(1.0f,0.0f);glVertex3f(100, 0, -100);
  glTexCoord2f(0.0f,0.0f);glVertex3f(100, 0, -0);
  glTexCoord2f(0.0f,1.0f);glVertex3f(100, 100, -0);
  glTexCoord2f(1.0f,1.0f);glVertex3f(100, 100, -100);
  glEnd();

  glDisable(GL_TEXTURE_2D);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,skybox[6]);
  
  glBegin(GL_POLYGON);
  glTexCoord2f(0.0f,0.0f);glVertex3f(100, 0, 0);
  glTexCoord2f(0.0f,1.0f);glVertex3f(-100, 0, 0);
  glTexCoord2f(1.0f,1.0f);glVertex3f(-100, 0, -100);
  glTexCoord2f(1.0f,0.0f);glVertex3f(100, 0, -100);
  glEnd();
  
  glDisable(GL_TEXTURE_2D);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,skybox[5]);
  
  glBegin(GL_POLYGON);
  glTexCoord2f(1.0f,0.0f);  glVertex3f(100, 0, -100); 
  glTexCoord2f(0.0f,0.0f);  glVertex3f(-100, 0, -100); 
  glTexCoord2f(0.0f,1.0f);  glVertex3f(-100, 100, -100); 
  glTexCoord2f(1.0f,1.0f);  glVertex3f(100, 100, -100); 
  glEnd();
  glDisable(GL_TEXTURE_2D);

  
  
  glPopMatrix();

}


void drawBall()
{
    glPushMatrix();
	    glTranslatef (obsPfin[0], obsPfin[1], obsPfin[2]);
		
	    glColor4d(AMARELO);
	    glutSolidSphere(2, 10, 10);
    glPopMatrix();
    
}
void drawEscada()
{
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
    gluPerspective(angPersp, (float)wScreen/hScreen, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(obsPini[0], obsPini[1]+2.5, obsPini[2]+2.5, obsPfin[0], obsPfin[1], obsPfin[2], 0, 1, 0);
    drawSkybox();
    drawBall();
    //drawChao();    
    drawEscada();

    glutSwapBuffers();
    
}


void updateVisao(int caso ){
    
    if(caso==1){
        obsPini[0] =obsPfin[0]+rVisao*cos(aVisao);
        obsPini[2] =obsPfin[2]-rVisao*sin(aVisao);
    }
    glutPostRedisplay();
}

void updateVisaoSubida(){
    obsPfin[1] = obsPini[1];
    glutPostRedisplay();
}



//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y){
    switch (key) {
        case 97:
            aVisao+=0.5;
            updateVisao(1);
            break;
        case 100:
            aVisao-=0.5;
            updateVisao(1);
            break;
        case 32:
            obsPini[1] += 2;
            updateVisaoSubida();
            break;
            //--------------------------- Escape
        case 27:
            exit(0);
            break;
            
    }
}

void teclasNotAscii(int key, int x, int y)
{
    if(key == GLUT_KEY_UP) {
        obsPfin[2]-=0.3;
        obsPini[2]-=0.3;
        updateVisao(0);

    }
    if(key == GLUT_KEY_DOWN) {
        obsPfin[2]+=0.3;
        obsPini[2]+=0.3;
        updateVisao(0);
    }
    if(key == GLUT_KEY_LEFT){
        obsPfin[0]-=0.3;
        obsPini[0]-=0.3;
        updateVisao(0);
    }
    

    if(key == GLUT_KEY_RIGHT){
        obsPfin[0]+=0.3;
        obsPini[0]+=0.3;
        updateVisao(0);
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



//======================================================= MAIN
int main(int argc, char** argv){
    initializeRandomVariables();
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize (wScreen, hScreen); 
    glutInitWindowPosition (400, 100); 
    glutCreateWindow ("Escadas");
    
    init();
    glutSpecialFunc(teclasNotAscii); 
    glutReshapeFunc(resize);
    glutDisplayFunc(display); 
    glutKeyboardFunc(keyboard);
    
    
    glutMainLoop();
    
    return 0;
}

