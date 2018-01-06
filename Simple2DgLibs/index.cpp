#include <string>
#include "Simple2D.h"
#include <iostream>


extern "C" std::string myStr = "Trololololololololololol";


extern "C" void setup(){
    //std::cout << *gameObjects->at(0)->getAttribute<std::string>("myStr") << std::endl;
    std::cout << *findGameObject("testObj")->getAttribute<std::string>("myStr") << std::endl;
}

extern "C" void update(){
}
