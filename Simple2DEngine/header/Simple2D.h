//h
// Created by albert on 1/4/18.
//

#ifndef SIMPLE2DENGINE_SIMPLE2D_H
#define SIMPLE2DENGINE_SIMPLE2D_H

#include <vector>
#include <string>
#include "../Simple2DEngine/header/GameObject.h"

#ifdef WIN32
#define export extern "C" __declspec(dllexport)
#else
#define export extern "C"
#endif

#define ADD_PROPERTY(type, name) export type _prop_ ## name(){ return name; }

namespace Simple2D{
    Simple2D::GameObject* findGameObject(std::string name);
}


#endif //SIMPLE2DENGINE_SIMPLE2D_H
