//
//  Texturas.cpp
//  EscadasMaximo

#include "Texturas.hpp"

GLuint texturasT[5];

void Texturas::initTexturas(RgbImage imagTex)
{
    //----------------------------------------- Chao
    glGenTextures(1, &texturasT[0]);
    glBindTexture(GL_TEXTURE_2D, texturasT[0]);
    imagTex.LoadBmpFile("/Users/tiagorodrigues/Desktop/Filipa/EscadasMaximo/EscadasMaximo/textures/Grass01.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imagTex.GetNumCols(),
                 imagTex.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imagTex.ImageData());
    
    glGenTextures(1, &texturasT[1]);
    glBindTexture(GL_TEXTURE_2D, texturasT[1]);
    imagTex.LoadBmpFile("/Users/tiagorodrigues/Desktop/Filipa/EscadasMaximo/EscadasMaximo/textures/brick.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imagTex.GetNumCols(),
                 imagTex.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imagTex.ImageData());
    
    glGenTextures(1, &texturasT[2]);
    glBindTexture(GL_TEXTURE_2D, texturasT[2]);
    imagTex.LoadBmpFile("/Users/tiagorodrigues/Desktop/Filipa/EscadasMaximo/EscadasMaximo/textures/pedra.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imagTex.GetNumCols(),
                 imagTex.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imagTex.ImageData());
    
    glGenTextures(1, &texturasT[3]);
    glBindTexture(GL_TEXTURE_2D, texturasT[3]);
    imagTex.LoadBmpFile("/Users/tiagorodrigues/Desktop/Filipa/EscadasMaximo/EscadasMaximo/textures/Grass01.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imagTex.GetNumCols(),
                 imagTex.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imagTex.ImageData());
    
    glGenTextures(1, &texturasT[4]);
    glBindTexture(GL_TEXTURE_2D, texturasT[4]);
    imagTex.LoadBmpFile("/Users/tiagorodrigues/Desktop/Filipa/EscadasMaximo/EscadasMaximo/textures/brick.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 imagTex.GetNumCols(),
                 imagTex.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imagTex.ImageData());
    // Enable color material mode:
    // The ambient and diffuse color of the front faces will track the color set by glColor().
    glEnable(GL_BLEND); // Enable blending.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
}
