//
//  Texturas.hpp
//  EscadasMaximo

#ifndef Texturas_hpp
#define Texturas_hpp

#include <stdio.h>
#include "RgbImage.h"
#include <OpenGl/gl.h>

class Texturas{
public:
    GLuint texturasT[5];
    void initTexturas(RgbImage imagTex);
};
#endif /* Texturas_hpp */
