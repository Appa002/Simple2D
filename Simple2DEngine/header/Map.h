//
// Created by albert on 1/3/18.
//

#ifndef SIMPLE2DENGINE_MAP_H
#define SIMPLE2DENGINE_MAP_H

#include <string>
#include <regex>
#include <lua.hpp>
#include <iostream>
#include "types.h"
#include "ExternalCodeLoadingWrapper.h"
#include "GameObject.h"
#include "Utils.h"

namespace Simple2D{
    class Map {
    private:
        int loadGameObject(std::string path);
    public:
        Map(std::string& path);
        Map();
        ~Map();

        std::string name;
        int load(std::string path);
        void remove();
        void updateAll();
        void setupAll();
        void eventHandelAll(SDL_Event e);
        void renderAll(GLuint shaderProgramme);

        std::vector<GameObject*>* gameObjects;
    };
}



#endif //SIMPLE2DENGINE_MAP_H
