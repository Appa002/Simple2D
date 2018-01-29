#include <string>
#include "../../Simple2DEngine/header/Simple2D.h"
#include "../../Simple2DEngine/header/types.h"
#include <iostream>


Simple2D::Vec3* position;
ADD_PROPERTY(Simple2D::Vec3*, position);

export void init(){
    position = new Simple2D::Vec3(-0.5f, 0.5f, 0);
}

export void setup(){
    printf("In GameObject: %f, %f, %f\n", position->x, position->y, position->z);
}

export void update(){

}
