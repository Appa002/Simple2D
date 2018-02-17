//
// Created by albert on 1/9/18.
//

#include "../header/MapManager.h"

Simple2D::Map* Simple2D::MapManager::getCurrentMap() {
    return this->curMap;
}

int Simple2D::MapManager::loadMap(std::string path) {
    this->curMap = new Map(path);
    for(auto gObj : *this->curMap->gameObjects){
        gObj->preSetup();
    }

    this->curMap->setupAll();

    return 0;
}

int Simple2D::MapManager::unloadMap() {
    this->curMap->remove();
    delete curMap;
    curMap = nullptr;

    return 0;
}