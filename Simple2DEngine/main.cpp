#include "header/Engine.h"
#include "header/ExternalCodeLoadingWrapper.h"
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include "header/Map.h"

int main(){

    Simple2D::Map* m = new Simple2D::Map();

    m->load("./test.lua");

    std::cout << m->gameObjects.at(0)->getAttribute<std::string>("myStr") << std::endl;
    std::cout << *m->gameObjects.at(0)->getAttribute<std::string>("myStr") << std::endl;

    delete m;


//    Simple2D::startEngine();
    return 0;
}
