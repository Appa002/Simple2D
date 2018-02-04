#include <string>
#include "../../Simple2DEngine/header/Simple2D.h"
#include "../../Simple2DEngine/header/types.h"
#include <iostream>
#include <SDL2/SDL.h>


Simple2D::Vec3* position;
ADD_PROPERTY(Simple2D::Vec3*, position);

export void init(){
    position = new Simple2D::Vec3(-0.5f, 0.5f, 0);
}

export void setup(){
}

export void update(){
}

