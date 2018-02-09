//h
// Created by albert on 1/4/18.
//

#ifndef SIMPLE2DENGINE_SIMPLE2D_H
#define SIMPLE2DENGINE_SIMPLE2D_H

#include <vector>
#include <string>
#include "GameObject.h"
#include "Behavior.h"

#ifdef WIN32
#define export extern "C" __declspec(dllexport)
#else
#define export extern "C"
#endif

#define REGISTER_GAME_OBJECT(name) export Simple2D::Behavior* _entry_point(){return new name;}

namespace Simple2D{
    Simple2D::GameObject* findGameObject(std::string name);
    int cloneGameObject(GameObject *toClone, std::string newName);
}


#endif //SIMPLE2DENGINE_SIMPLE2D_H
