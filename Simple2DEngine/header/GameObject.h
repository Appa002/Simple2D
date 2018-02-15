//
// Created by albert on 1/3/18.
//


#ifndef SIMPLE2DENGINE_GAMEOBJECT_H
#define SIMPLE2DENGINE_GAMEOBJECT_H

#include "ExternalCodeLoadingWrapper.h"
#include "Utils.h"
#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "Behavior.h"

namespace Simple2D{
    class  GameObject {
    private:
        int* spriteWidth;
        int* spriteHeight;
        unsigned char* imageData;
        GLuint* vao;
        bool markedForDeletion = false;

    public:
        GameObject();
        ~GameObject();

        Behavior* behavior;
        std::string name;
        std::string path;

        bool isMarkedForDeletion();
        void render(GLuint shaderProgramme);
        void preSetup();
        void loadNewSprite(std::string path);
        void remove();

    private:
        GameObject* findOtherGameObject(std::string name);
    };
}
#endif //SIMPLE2DENGINE_GAMEOBJECT_H
