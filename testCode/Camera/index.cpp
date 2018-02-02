#include <string>
#include <iostream>
#include "../../Simple2DEngine/header/Simple2D.h"
#include "../../Simple2DEngine/header/types.h"


Simple2D::Vec3* position;
ADD_PROPERTY(Simple2D::Vec3*, position);


export void init() {
    position = new Simple2D::Vec3(0.0f, 0.0f, 0);
}

export void setup() {
    //Simple2D::findGameObject("TestObj")->loadNewSprite("./TestObj/sprite.png");
}


export void update() {

}
