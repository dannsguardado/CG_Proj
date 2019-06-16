//
//  Teclado.cpp
//  EscadasMaximo
//
//  Created by Tiago Rodrigues on 14/06/19.
//  Copyright © 2019 Tiago Rodrigues. All rights reserved.
//

#include "Desenho.hpp"
//================================================================================
//================== OBJECTOS
//================================================================================

void Desenho::drawSkybox(Skybox skybox){
    glPushMatrix();
    glTranslatef (0, 0, 100);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,skybox.skyboxFace[4]);
    glColor3f(1.0,1.0,1.0);
    
    glBegin(GL_POLYGON);//back
    glTexCoord2f(1.0f,0.0f);  glVertex3f(150, 0, 0);
    glTexCoord2f(0.0f,0.0f);  glVertex3f(-150, 0, 0);
    glTexCoord2f(0.0f,1.0f);  glVertex3f(-150, 200, 0);
    glTexCoord2f(1.0f,1.0f);  glVertex3f(150, 200, 0);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,skybox.skyboxFace[2]);
    
    glBegin(GL_POLYGON);//top
    glTexCoord2f(0.0f,0.0f);glVertex3f(150, 200, 0);
    glTexCoord2f(1.0f,0.0f);glVertex3f(-150, 200, 0);
    glTexCoord2f(1.0,1.0f);glVertex3f(-150, 200, -150);
    glTexCoord2f(0.0,1.0);glVertex3f(150, 200, -150);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,skybox.skyboxFace[3]);
    
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f,0.0f);  glVertex3f(-150, 0, -150);
    glTexCoord2f(1.0f,0.0f);  glVertex3f(-150, 0, 0);
    glTexCoord2f(1.0f,1.0f);  glVertex3f(-150, 200, 0);
    glTexCoord2f(0.0f,1.0f);  glVertex3f(-150, 200, -150);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,skybox.skyboxFace[1]);
    
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f,0.0f);glVertex3f(150, 0, -150);
    glTexCoord2f(0.0f,0.0f);glVertex3f(150, 0, 0);
    glTexCoord2f(0.0f,1.0f);glVertex3f(150, 200, 0);
    glTexCoord2f(1.0f,1.0f);glVertex3f(150, 200, -150);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,skybox.skyboxFace[6]);
    
   /* glBegin(GL_POLYGON);
    glTexCoord2f(0.0f,0.0f);glVertex3f(150, 0, 0);
    glTexCoord2f(0.0f,1.0f);glVertex3f(-150, 0, 0);
    glTexCoord2f(1.0f,1.0f);glVertex3f(-150, 0, -150);
    glTexCoord2f(1.0f,0.0f);glVertex3f(150, 0, -150);
    glEnd();*/
    
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,skybox.skyboxFace[5]);
    
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f,0.0f);  glVertex3f(150, 0, -150);
    glTexCoord2f(0.0f,0.0f);  glVertex3f(-150, 0, -150);
    glTexCoord2f(0.0f,1.0f);  glVertex3f(-150, 200, -150);
    glTexCoord2f(1.0f,1.0f);  glVertex3f(150, 200, -150);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glPopMatrix();
    glFlush();

}

void Desenho::drawBall(GLfloat obsPfin[])
{
    GLfloat whitePlasticAmb []={ 0.8 ,0.8 ,0.8 };
    GLfloat whitePlasticDif []={   0.55 ,0.55 ,0.55 };
    GLfloat whitePlasticSpec []={ 0.870 ,0.870 ,0.870 };
    GLint whitePlasticCoef = 0.25 *128;
    GLfloat no_mat[] = {0.6, 0.5, 0.6, 0.2};
    GLfloat mat_diffuse[] = { 0.4, 0.2, 0, 1.0 };
    GLfloat mat_specular[] = { 0.774597, 0.774597, 0.774597, 1.0 };
    GLfloat mat_shine = 26;
    
    glMaterialfv (GL_FRONT, GL_AMBIENT, whitePlasticAmb);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, whitePlasticDif);
    glMaterialfv (GL_FRONT, GL_SPECULAR, whitePlasticSpec);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, mat_shine);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    
    glPushMatrix();
    glTranslatef (obsPfin[0], obsPfin[1], obsPfin[2]);
    glColor4d(AMARELO);
    glNormal3f(0,0,1);
    
    glutSolidSphere(2, 10, 10);
    glPopMatrix();
    glFlush();
}


void Desenho::drawEscada(Texturas texture,GLuint poligono[],int facesESC, GLint numDegraus[], int lancesESC)
{
    glPushMatrix();
    glTranslatef ( 1, 0, 1);
    glEnable(GL_TEXTURE_2D);
    glDisableClientState(GL_COLOR_ARRAY);
    for(int k=0 ; k<lancesESC; k++){
        for(int j=0; j<numDegraus[k]; j++){//j<num_degraus[k]
            for( int p = 0; p < facesESC; p++ ){
                if (p == 1)
                    glBindTexture(GL_TEXTURE_2D, texture.texturasT[2]);
                else if (p == 2)
                    glBindTexture(GL_TEXTURE_2D,texture.texturasT[2]);
                else
                    glBindTexture(GL_TEXTURE_2D,texture.texturasT[1]);
                
                
                poligono[0]= p*4+0;
                poligono[1]= p*4+1 ;
                poligono[2]= p*4+2 ;
                poligono[3]= p*4+3 ;
                glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, poligono);
            }
            glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, poligono);

            glTranslatef ( 0, 2, -5);
        }
        glBindTexture(GL_TEXTURE_2D,texture.texturasT[2]);
        poligono[0]= 4*4+0;
        poligono[1]= 4*4+1 ;
        poligono[2]= 4*4+2 ;
        poligono[3]= 4*4+3 ;
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, poligono);
        
        glTranslatef(-5, 0,0);

        glRotatef(90, 0, 1, 0);
        for(int j=0; j<numDegraus[k]; j++){//j<num_degraus[k]
            for( int p = 0; p < facesESC; p++ ){
                if (p == 1)
                    glBindTexture(GL_TEXTURE_2D,texture.texturasT[2]);
                else if (p == 2)
                    glBindTexture(GL_TEXTURE_2D,texture.texturasT[2]);
                else
                    glBindTexture(GL_TEXTURE_2D,texture.texturasT[2]);
                
                poligono[0]= p*4+0;
                poligono[1]= p*4+1 ;
                poligono[2]= p*4+2 ;
                poligono[3]= p*4+3 ;
                
                glDisable(GL_CULL_FACE);
                glShadeModel(GL_SMOOTH);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                
                glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, poligono);
                
            }
            glTranslatef ( 0, 2, -5);
            
        }
        glDisableClientState(GL_COLOR_ARRAY);
        glBindTexture(GL_TEXTURE_2D,texture.texturasT[2]);
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
    glFlush();

}

void Desenho::drawFloor(){
    glPushMatrix();
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f,0.0f);glVertex3f(150, 0, 150);
    glTexCoord2f(0.0f,1.0f);glVertex3f(-150, 0, 150);
    glTexCoord2f(1.0f,1.0f);glVertex3f(-150, 0, -150);
    glTexCoord2f(1.0f,0.0f);glVertex3f(150, 0, -150);
    glEnd();
    glPopMatrix();
}

/*
void Desenho::drawColunas(int top){
    GLUquadric* qobj;

    qobj = gluNewQuadric();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluQuadricNormals(qobj, GLU_SMOOTH);
    gluCylinder(qobj,1, 1, top, 20, 20);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

}
*/




