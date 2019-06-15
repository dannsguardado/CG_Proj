//
//  Skybox.hpp
//  EscadasMaximo
//
//  Created by Tiago Rodrigues on 14/06/19.
//  Copyright © 2019 Tiago Rodrigues. All rights reserved.
//

#ifndef Skybox_hpp
#define Skybox_hpp

#include <stdio.h>
#include <GLUT/GLUT.h>
#include <OpenGl/gl.h>
#include <cstdlib>
#include "variables.h"
#include "RgbImage.h"

class Skybox {
   public:
    GLuint skyboxFace[7];
    void initSkybox(RgbImage imagSk);
};
#endif /* Skybox_hpp */
