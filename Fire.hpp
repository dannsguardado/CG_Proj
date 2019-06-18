//
//  Fire.hpp
//  EscadasMaximo
//
//  Created by Tiago Rodrigues on 17/06/19.
//  Copyright © 2019 Tiago Rodrigues. All rights reserved.
//

#ifndef Fire_hpp
#define Fire_hpp

#include <stdio.h>
#include <GLUT/GLUT.h>
#include <OpenGl/gl.h>
#include <cstdlib>
#include "variables.h"
#include "RgbImage.h"

class Fire {
    
public:
    typedef struct {
        float size;        // tamanho
        float life;        // vida
        float fade;        // fade
        float r, g, b;    // color
        GLfloat x, y, z, pix, piy, piz;    // posicao
        GLfloat vx, vy, vz; // velocidade
        GLfloat ax, ay, az; // aceleracao
    } Particle;
    
    Particle particles[MAX_PARTICULAS];
    
    void generateParticle(Particle *p);
    void initParticle(Particle *particle);
    void updateParticle(Particle *particle);
    void showParticle(Particle *particle);
    
};
#endif /* Fire_hpp */
