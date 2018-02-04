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


namespace Simple2D{
    class Attribute{
    public:

        bool isValid() {
            if (name == "")
                return false;
            if (content == nullptr)
                return false;
            if (hash == 0)
                return false;
            return true;
        }

        void* content = 0;
        size_t hash = 0;
        std::string name = "";
    };

    class  GameObject {
    private:
        int* spriteWidth;
        int* spriteHeight;
        unsigned char* imageData;
        GLuint* vao;
    public:
        GameObject();
        ~GameObject();

        std::string name;
        std::string path;
        ExternalCode::Handle handle;

        void(*updatePointer)();
        void(*setupPointer)();
        void(*onEventPointer)(SDL_Event e);

        template<typename T> T getAttribute(std::string name);
        template<typename T> void addAttribute(std::string name, T content);
        template<typename T> void setAttribute(std::string name, T content);
        template<typename T> void removeAttribute(std::string name);
        template<typename T> Attribute findAttribute(std::string name);
        template<typename T> Attribute findAttribute(std::string name, bool* error, unsigned int* idx);
        void render(GLuint shaderProgramme);
        void preSetup();
        void loadNewSprite(std::string path);

        std::vector<Attribute>* getAttributeVec();
    private:
        std::vector<Attribute> attributes;
        GameObject* findOtherGameObject(std::string name);
    };
}


template <typename T>
inline T  Simple2D::GameObject::getAttribute(std::string name)
{
    bool error = false;
    Attribute attr = findAttribute<T>(name, &error, 0);
    if(error || attr.name == ""){
        return 0;
    }

    return reinterpret_cast<T>(attr.content);

}

template<typename T>
inline Simple2D::Attribute Simple2D::GameObject::findAttribute(std::string name)
{
    return GameObject::findAttribute<T>(name, 0, 0);
}

template<typename T> Simple2D::Attribute Simple2D::GameObject::findAttribute(std::string name, bool* error, unsigned int* idx)
{
    for (unsigned int i = 0; i < GameObject::attributes.size(); i++) {

        std::string atrName = GameObject::attributes.at(i).name;

        if (atrName == name) {

            if (GameObject::attributes.at(i).hash != typeid(T).hash_code()) {
                throw std::runtime_error("Types don't match!");
            }
            if (idx != 0)
                *idx = i;

            if (error != 0)
                *error = false;

            return GameObject::attributes.at(i);
        }
    }
    if (error != 0)
        *error = true;

    return GameObject::findAttribute<int>("");
}

template<typename T>
inline void Simple2D::GameObject::setAttribute(std::string name, T content)
{
    Attribute attr = findAttribute<T>(name);
    *reinterpret_cast<T*>(attr.content) = content;
}

template<typename T>
inline void Simple2D::GameObject::removeAttribute(std::string name)
{
    unsigned int i = 0;
    Attribute attr = findAttribute<T>(name, 0, &i);
    delete reinterpret_cast<T*>(attr.content);
    GameObject::attributes.erase(GameObject::attributes.begin() + i);

}

template<typename T>
inline void Simple2D::GameObject::addAttribute(std::string name, T content)
{

    for (unsigned int i = 0; i < GameObject::attributes.size(); i++) {
        if (GameObject::attributes.at(i).name == name) {
            throw std::runtime_error("Such element already exists");
        }
    }

    Attribute attrib;
    attrib.name = name;
    attrib.content = content;
    attrib.hash = typeid(T).hash_code();

    GameObject::attributes.push_back(attrib);

}

#endif //SIMPLE2DENGINE_GAMEOBJECT_H
