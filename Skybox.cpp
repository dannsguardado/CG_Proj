//
//  Skybox.cpp
//  EscadasMaximo
//
//  Created by Tiago Rodrigues on 14/06/19.
//  Copyright © 2019 Tiago Rodrigues. All rights reserved.
//

#include "Skybox.hpp"

GLuint skyboxFace[7];

void Skybox::initSkybox(RgbImage imagSk){
    
    //skybox bottom
    glGenTextures(1, &skyboxFace[0]);
    glBindTexture(GL_TEXTURE_2D, skyboxFace[0]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    imagSk.LoadBmpFile("/Users/tiagorodrigues/Desktop/Filipa/EscadasMaximo/EscadasMaximo/skybox/floor.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 imagSk.GetNumCols(),
                 imagSk.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imagSk.ImageData());
    
    //skybox top
    glGenTextures(1, &skyboxFace[1]);
    glBindTexture(GL_TEXTURE_2D, skyboxFace[1]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    imagSk.LoadBmpFile("/Users/tiagorodrigues/Desktop/Filipa/EscadasMaximo/EscadasMaximo/skybox/left.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 imagSk.GetNumCols(),
                 imagSk.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imagSk.ImageData());
    
    //skybox right
    glGenTextures(1, &skyboxFace[2]);
    glBindTexture(GL_TEXTURE_2D, skyboxFace[2]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    imagSk.LoadBmpFile("/Users/tiagorodrigues/Desktop/Filipa/EscadasMaximo/EscadasMaximo/skybox/sky.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 imagSk.GetNumCols(),
                 imagSk.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imagSk.ImageData());
    
    //skybox left
    glGenTextures(1, &skyboxFace[3]);
    glBindTexture(GL_TEXTURE_2D, skyboxFace[3]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    imagSk.LoadBmpFile("/Users/tiagorodrigues/Desktop/Filipa/EscadasMaximo/EscadasMaximo/skybox/front.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 imagSk.GetNumCols(),
                 imagSk.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imagSk.ImageData());
    
    //skybox front
    glGenTextures(1, &skyboxFace[4]);
    glBindTexture(GL_TEXTURE_2D, skyboxFace[4]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    imagSk.LoadBmpFile("/Users/tiagorodrigues/Desktop/Filipa/EscadasMaximo/EscadasMaximo/skybox/back.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 imagSk.GetNumCols(),
                 imagSk.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imagSk.ImageData());
    
    //skybox back
    glGenTextures(1, &skyboxFace[5]);
    glBindTexture(GL_TEXTURE_2D, skyboxFace[5]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    imagSk.LoadBmpFile("/Users/tiagorodrigues/Desktop/Filipa/EscadasMaximo/EscadasMaximo/skybox/right.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 imagSk.GetNumCols(),
                 imagSk.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imagSk.ImageData());
    
    
    glGenTextures(1, &skyboxFace[6]);
    glBindTexture(GL_TEXTURE_2D, skyboxFace[6]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    imagSk.LoadBmpFile("/Users/tiagorodrigues/Desktop/Filipa/EscadasMaximo/EscadasMaximo/skybox/floor.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 imagSk.GetNumCols(),
                 imagSk.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imagSk.ImageData());
    
}

