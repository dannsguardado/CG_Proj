//
//  Fire.cpp
//  EscadasMaximo
//
//  Created by Tiago Rodrigues on 17/06/19.
//  Copyright © 2019 Tiago Rodrigues. All rights reserved.
//

#include "Fire.hpp"

//---------------------------------------- Particle attributes


void Fire::generateParticle(Particle *p) {
    GLfloat v, theta;
    GLfloat px, py, pz;
    GLfloat ps;
    
    px = ((rand()%10) - 5) * cos(theta);
    py = 0.0;
    pz = ((rand()%10) - 5) * sin(theta);
    ps = 0.2;
    
    //---------------------------------
    v = 1 * frand() + 0.02;
    theta = 2.0 * frand() * M_PI;   // [0..2pi]
    
    p->size = ps;        // tamanh de cada particula
    p->x = px + 0.1 * frand() * px;    // [-200 200]
    p->y = py + 0.1 * frand() * py;    // [-200 200]
    p->z = pz + 0.1 * frand() * pz;    // [-200 200]
    
    p->piy = p->y;
    p->pix = p->x;
    p->piz = p->z;
    
    p->vx = v * 0.1 * cos(theta);    // cone
    p->vy = 1.0;
    p->vz = v * 0.2 * sin(theta);
    
    p->ax = -0.001f;
    p->ay = -0.001f;
    p->az = -0.001f;
    
    p->r = 1.0f;
    p->g = 1.0f;
    p->b = 1.0f;
    p->life = 2 * frand();
    p->fade = .2 * frand();
    
}

//==========================================================
void Fire::initParticle(Particle *particle) {
    
    for (int i = 0; i < MAX_PARTICULAS; i++) {
        generateParticle(&particle[i]);
    }
}

void Fire::updateParticle(Particle *particle) {
    for (int i = 0; i < MAX_PARTICULAS; i++) {
        if(particle[i].life < 0.0 || (particle[i].y > (particle[i].piy + 250))) {
            generateParticle(&particle[i]);
        }
    }
}

void Fire::showParticle(Particle *particle) {
    int i;
    
    for (i = 0; i < MAX_PARTICULAS; i++) {
        
        glBegin(GL_QUADS);
        glColor3f(1, 0, 0);
        glTexCoord2d(0, 0);
        glVertex3f(particle[i].x - particle[i].size, particle[i].y - particle[i].size, particle[i].z);
        glTexCoord2d(1, 0);
        glVertex3f(particle[i].x + particle[i].size, particle[i].y - particle[i].size, particle[i].z);
        glTexCoord2d(1, 1);
        glVertex3f(particle[i].x + particle[i].size, particle[i].y + particle[i].size, particle[i].z);
        glTexCoord2d(0, 1);
        glVertex3f(particle[i].x - particle[i].size, particle[i].y + particle[i].size, particle[i].z);
        glEnd();
        particle[i].x += particle[i].vx;
        particle[i].y += particle[i].vy;
        particle[i].z += particle[i].vz;
        particle[i].vx += (particle[i].ax * cos(rand()));
        particle[i].vy += (particle[i].ay * cos(rand()));
        particle[i].vz += (particle[i].az * cos(rand()));
        particle[i].life -= (particle[i].fade * particle[i].y * .1);
    }
}

