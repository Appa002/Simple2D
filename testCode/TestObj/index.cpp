#include <string>
#include "../../Simple2DEngine/header/Simple2D.h"
#include "../../Simple2DEngine/header/types.h"
#include <iostream>


Simple2D::Vec3* position;
ADD_PROPERTY(Simple2D::Vec3*, position);

void testUpdate(){
    std::cout << "Sup dawg guess whos being called and shit" << std::endl;
}

export void init(){
    position = new Simple2D::Vec3(-0.5f, 0.5f, 0);
}

export void setup(){
    Simple2D::cloneGameObject(Simple2D::findGameObject("TestObj"), "NewTestObj");
    Simple2D::findGameObject("NewTestObj")->updatePointer = testUpdate;
}

export void update(){
    std::cout << "-";
}


