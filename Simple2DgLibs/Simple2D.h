//
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

Simple2D::GameObject* findGameObject(std::string name);


#endif //SIMPLE2DENGINE_SIMPLE2D_H