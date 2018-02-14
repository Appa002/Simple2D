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

Simple2D::GameObject * Simple2D::cloneGameObject(GameObject *toClone, std::string newName) {
    GameObject* gameObject = new GameObject;
    gameObject->name = newName;
    gameObject->path = toClone->path;

    ExternalCode::Handle h = ExternalCode::open(toClone->path + "/external.so");
    ((void(*)(std::vector<GameObject*>*))(ExternalCode::find(h, "_prop_gameObjects")))(gameObjects);
    gameObject->behavior = ((Behavior*(*)())(ExternalCode::find(h, "_entry_point")))();

    gameObject->behavior->init();
    gameObject->preSetup();

    gameObjects->push_back(gameObject);

    std::cout << "Created new object" << std::endl;
    return gameObject;
}