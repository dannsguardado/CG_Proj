//
//  Teclado.hpp
//  EscadasMaximo
//
//  Created by Tiago Rodrigues on 14/06/19.
//  Copyright © 2019 Tiago Rodrigues. All rights reserved.
//

#ifndef Teclado_hpp
#define Teclado_hpp

#include <stdio.h>
#include <GLUT/GLUT.h>
#include <OpenGl/gl.h>
#include <cstdlib>
#include "variables.h"
#include "Skybox.hpp"
#include "Texturas.hpp"

#define   PI 3.14159
class Desenho{
public:
    void drawSkybox(Skybox skybox);
    void drawBall(GLfloat obsPfin[]);
    void drawEscada(Texturas texture, GLuint poligono[],int facesEsc, GLint numDegraus[], int lancesESC);
    void drawFloor();
   // void drawColunas(int top);
};

#endif /* Teclado_hpp */
