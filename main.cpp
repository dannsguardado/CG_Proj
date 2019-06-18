
#include <stdio.h>
#include "variables.h"
#include "Texturas.hpp"
#include "Skybox.hpp"
#include "Desenho.hpp"
#include "Fire.hpp"

Skybox skybox;
Texturas texture;
Desenho canvas;
Fire fire;

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
GLint lancesESC = 8;
GLint numDegraus[8];

GLint  facesESC   = 6;
GLint  degrausESC= 3;
static GLuint poligono[] = {};

//-------------------------------------------------------------Focos de luz

// Info lanterna - luz 1
GLfloat qaAmbientLight[]    = {0.1, 0.1, 0.1, 1.0};
GLfloat qaDiffuseLight[]    = {1, 1, 1, 1.0};
GLfloat qaSpecularLight[]    = {1.0, 1.0, 1.0, 1.0};
GLfloat emitLight[] = {0.9, 0.9, 0.9, 0.01};
GLfloat Noemit[] = {0.0, 0.0, 0.0, 1.0};
// Posiçao e direcçao
GLfloat qaLightPosition[]    = {0, 0, 0, 1};
GLfloat qaLightDirection[]    = {0, 0, 1, 0};
GLfloat dirVector0[]={ 0.0, 0.50, -0.5, 1.0};

GLfloat whitePlasticAmb []={ 0.8 ,0.8 ,0.8 };
GLfloat whitePlasticDif []={   0.55 ,0.55 ,0.55 };
GLfloat whitePlasticSpec []={ 0.870 ,0.870 ,0.870 };
GLint whitePlasticCoef = 0.25 *128;

GLfloat whiteDif[] = { 0.75 ,0.75 ,0.75 };

RgbImage imag;
GLboolean fog = false;
GLboolean showFire = false;


typedef struct {
    float   size;		// tamanho
    float	life;		// vida
    float	fade;		// fade
    GLfloat x, y, z;    // posicao
    GLfloat vx, vy, vz; // velocidade
} Particle;

Particle  particula1[MAX_PARTICULAS];

static GLfloat verticesEscadas[]={
    5, 0, 0,
    -5, 0, 0,
    -5, 2, 0,
    5, 2, 0,
    
    5, 2, 0,
    -5, 2, 0,
    -5, 2, -5,
    5, 2, -5,
    
    -5, 0, -5,
    -5, 0, 0,
    -5, 2, 0,
    -5, 2, -5,
    
    5, 0, -5,
    5, 0, 0,
    5, 2, 0,
    5, 2, -5,
    
    5, 0, 0,
    -5, 0, 0,
    -5, 0, -5,
    5, 0, -5,
    
    5, 2, -5,
    -5, 0, -5,
    -5, 2, -5,
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

GLUquadricObj*  bola = gluNewQuadric ( );

static GLfloat arrayTexture[]={
    0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1,  0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1
};

//======================================================= EVENTOS
GLvoid resize(GLsizei width, GLsizei height)
{
    wScreen=width;
    hScreen=height;
    glViewport( 0, 0, wScreen,hScreen );
    glutPostRedisplay();
}

const GLfloat gravity = -9.8;
GLfloat velocity = 0;

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

bool collision(){
    return false;
}

void timer(GLint t=1)
{
    GLfloat calc=obsPfin[1] + velocity * t/1000;
    if(calc >0){
        velocity += gravity * t/1000;
        obsPfin[1] += velocity * t/1000;
        obsPini[1] += velocity * t/1000;
        
    }
    if(showFire){
        fire.updateParticle(fire.particles);
    }
    glutPostRedisplay();
    glutTimerFunc(100, timer, 1);

}

void keyboard(unsigned char key, int x, int y){
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
            if(obsPini[1] - 2 >0){
                obsPini[1] -= 2;
                updateVisaoSubida();
            }
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
        case 102:
            fog = !fog;
            if(fog)glEnable(GL_FOG);
            else glDisable(GL_FOG);
            break;
        case 'z':
            showFire=!showFire;
            if(showFire) fire.initParticle(fire.particles);
            break;
                  //--------------------------- Escape
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
    GLint value = PI/2;

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

void drawFloor(){
    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    
    //................................................................................................
    glEnable(GL_STENCIL_TEST);
    glColorMask(0, 0, 0, 0);
    glClear(GL_STENCIL_BUFFER_BIT);
    glStencilMask(0xFF);
    //......................		..............................................................................
    glStencilFunc(GL_ALWAYS, 1, 1);
    glStencilOp( GL_REPLACE, GL_REPLACE, GL_REPLACE); // substitui por ref=1    //desenha chao
    canvas.drawFloor();
    
    glColorMask( 1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
    
    glClear(GL_DEPTH_BUFFER_BIT);
    // Escrever colorBuffer // Enable Zbuffer
    // Garantir apaga zbuffer
    //----------------------------------------------
    glStencilFunc(GL_EQUAL, 1, 1); // Desenha so na zona do StencilBuff
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); // Stencil fica igual !
    glFrontFace(GL_CW);

    glPushMatrix();
        glScalef(1.0, -1.0, 1.0);
    if(showFire){
        fire.showParticle(fire.particles);
    }
        canvas.drawSkybox(skybox);
        canvas.drawBall(obsPfin);
        canvas.drawEscada(texture, poligono, facesESC, numDegraus, lancesESC);
    glPopMatrix();
    glFrontFace(GL_CCW);

    glDisable(GL_STENCIL_TEST);
    
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.7, 0.7, 0.7, 0.40);  /* 40% dark red floor color */
    canvas.drawFloor();
    glDisable(GL_BLEND);
}

void initializeRandomVariables(){
    srand (time(NULL));
    for(int i = 0; i < lancesESC; i++){
        numDegraus[i] = rand() %6 + 3;
    }
}

void initLight(){
    GLfloat corDifusa [ ] ={0.0,0.4,1.0,0.0};
    GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 0.6f};
    GLfloat spotLight [ ] ={0.0,0.0,1.0,0.7};
    GLfloat angulo =20.0;
    
    GLfloat pos[]={10,20,20};
    glEnable(GL_LIGHTING);
    
    glEnable(GL_DEPTH_TEST);
    
    //Luz Ambiente Branca - começa ligada
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, whitePlasticAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whitePlasticDif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, whitePlasticSpec);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glEnable(GL_LIGHT0);
    
    //Luz pontual
    glLightfv(GL_LIGHT1, GL_AMBIENT, qaAmbientLight);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight);
    glLightfv(GL_LIGHT1, GL_POSITION, qaLightPosition);
    glLightfv(GL_LIGHT1, GL_SPECULAR, qaSpecularLight);
    ////////////////////////////////////////////////
    
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF,angulo);// set cutoff angle
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dirVector0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.5); // set focusing strength
    
    glEnable(GL_LIGHT1);
    glFrontFace(GL_CCW);
    glShadeModel(GL_SMOOTH);
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
    //mistura cor do chao com o reflexo
    drawFloor();


    canvas.drawSkybox(skybox);
    canvas.drawBall(obsPfin);
    canvas.drawEscada(texture, poligono, facesESC, numDegraus, lancesESC);
    if(showFire){
        fire.showParticle(fire.particles);
    }
    glutSwapBuffers();
}

void init(void) {
    glClearColor(WHITE);
    glShadeModel(GL_SMOOTH);
    skybox.initSkybox(imag);
    texture.initTexturas(imag);
    glEnable(GL_DEPTH_TEST);
    
    //------------------------------- ESCADA
    glVertexPointer(3, GL_FLOAT, 0, verticesEscadas);
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
    fire.initParticle(fire.particles);
    timer();
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
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(teclasNotAscii);
    
    glutMainLoop();
    
    return 0;
}
