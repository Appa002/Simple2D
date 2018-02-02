#include "../header/Simple2D.h"

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

std::vector<Simple2D::GameObject *> *Simple2D::getVec() {
    return gameObjects;
}

void Simple2D::cloneGameObject(GameObject *toClone, std::string newName) {
    GameObject* gameObject = new GameObject();
    gameObject->handle = toClone->handle;
    gameObject->updatePointer = toClone->updatePointer;
    gameObject->setupPointer = toClone->setupPointer;
    gameObject->path = toClone->path;
    gameObject->name = newName;
    gameObject->preSetup();

    for(Attribute& attr : *toClone->getAttributeVec()){
        toClone->getAttributeVec()->push_back(attr);
    }

    gameObjects->push_back(gameObject);
    std::cout << "Created new object" << std::endl;
}
