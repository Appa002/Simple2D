#include "Simple2D.h"

std::vector<Simple2D::GameObject*>* gameObjects;

export void load(std::vector<Simple2D::GameObject*>* gameObjectsImport){
    gameObjects = gameObjectsImport;
}

Simple2D::GameObject* findGameObject(std::string name){
    for(auto gObj : *gameObjects){
        if(gObj->name == name){
            return gObj;
        }
    }
    return nullptr;
}
