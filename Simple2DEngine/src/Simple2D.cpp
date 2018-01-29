#include "../Simple2DEngine/header/Simple2D.h"

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
