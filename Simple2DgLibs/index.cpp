#include <string>
#include "Simple2D.h"
#include "../Simple2DEngine/header/types.h"
#include <iostream>


std::string* myStr;
ADD_PROPERTY(std::string*, myStr);

export void init(){
    myStr = new std::string("Hello, World");
}

export void setup(){
    printf(findGameObject("testObj")->getAttribute<std::string*>("myStr")->c_str());
}

export void update(){

}
