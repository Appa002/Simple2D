#include "../header/Simple2D.h"
#include "../header/types.h"
#include "../header/Utils.h"
#include <lua.hpp>

std::vector<Simple2D::GameObject*>* gameObjects;

export void _prop_gameObjects(std::vector<Simple2D::GameObject*>* import){
    gameObjects = import;
}

Simple2D::GameObject* Simple2D::findGameObject(std::string name){
    for(auto gObj : *gameObjects){
        if(gObj->name == name){
            return gObj;
        }
    }
    return nullptr;
}

int Simple2D::cloneGameObject(GameObject *toClone, std::string newName) {
    std::cout << "Created new object" << std::endl;
    return 0;
}