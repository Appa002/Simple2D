//
// Created by albert on 1/3/18.
//

#ifndef SIMPLE2DENGINE_ENGINE_H
#define SIMPLE2DENGINE_ENGINE_H


#include <iostream>
#include <GL/glew.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <fstream>
#include "MapManager.h"


namespace Simple2D{
    int startEngine(){

        std::string vertex_shader;
        std::string fragment_shader;

        std::ifstream vsFile;
        std::ifstream fsFile;

        vsFile.open("./vertex.shader", std::ios::in);
        fsFile.open("./fragment.shader", std::ios::in);


        vsFile.seekg(0, std::ios::end);
        fsFile.seekg(0, std::ios::end);

        vertex_shader.reserve(vsFile.tellg());
        fragment_shader.reserve(fsFile.tellg());

        vsFile.seekg(0, std::ios::beg);
        fsFile.seekg(0, std::ios::beg);

        vertex_shader.assign((std::istreambuf_iterator<char>(vsFile)),
                   std::istreambuf_iterator<char>());

        fragment_shader.assign((std::istreambuf_iterator<char>(fsFile)),
                             std::istreambuf_iterator<char>());


        SDL_Init(SDL_INIT_VIDEO);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


        lua_State* L = luaL_newstate();
        luaL_openlibs(L);

        if (luaL_loadfile(L, "./0.lua") || lua_pcall(L, 0, 0, 0)) {
            printf("Error");
            return -1;
        }

        Utils::pushToTop("data.resolutionX", L);
        int resX = (int)lua_tointeger(L, -1);
        lua_pop(L, 1);

        Utils::pushToTop("data.resolutionY", L);
        int resY = (int)lua_tointeger(L, -1);
        lua_pop(L, 1);

        SDL_Window* window = SDL_CreateWindow("Simple2D Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resX, resY, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        SDL_GLContext context = SDL_GL_CreateContext(window);
        SDL_SetWindowResizable(window, SDL_TRUE);


        SDL_GL_MakeCurrent(window, context);

        glewExperimental = GL_TRUE;
        glewInit();
        SDL_GL_SetSwapInterval(1);

        const GLubyte* renderer = glGetString(GL_RENDERER);
        const GLubyte* version = glGetString(GL_VERSION);

        printf("Renderer: %s\n", renderer);
        printf("OpenGL Version: %s\n", version);
        std::cout << std::endl;

        glEnable(GL_DEPTH);
        glDepthFunc(GL_LESS);


        const char* tmp;

        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        tmp = vertex_shader.c_str();
        glShaderSource(vs, 1, &tmp, NULL);
        glCompileShader(vs);

        GLint succses = 0;
        glGetShaderiv(vs, GL_COMPILE_STATUS, &succses);
        if(!succses){
            GLint logSize = 0;
            glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &logSize);
            char* buffer = new char[logSize];
            glGetShaderInfoLog(vs, logSize, nullptr, buffer);
            std::cout << "Vertex Shader Compile Errors: " << "\n";
            std::cout << buffer << std::endl;
            delete buffer;
        }

        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        tmp = fragment_shader.c_str();
        glShaderSource(fs, 1, &tmp, NULL);
        glCompileShader(fs);

        succses = 0;
        glGetShaderiv(fs, GL_COMPILE_STATUS, &succses);
        if(!succses){
            GLint logSize = 0;
            glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &logSize);
            char* buffer = new char[logSize];
            glGetShaderInfoLog(fs, logSize, nullptr, buffer);
            std::cout << "Fragment Shader Compile Errors: " << "\n";
            std::cout << buffer << std::endl;
            delete buffer;
        }

        GLuint shader_programme = glCreateProgram();
        glAttachShader(shader_programme, vs);
        glAttachShader(shader_programme, fs);
        glLinkProgram(shader_programme);

        SDL_Event event;
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);


        Simple2D::MapManager::get()->loadMap("./0.lua");

        bool bQuit = false;
        while (!bQuit) {

            while (SDL_PollEvent(&event) != 0) {
                if (event.type == SDL_QUIT) {
                    Simple2D::MapManager::get()->getCurrentMap()->remove();
                    bQuit = true;
                }

                Simple2D::MapManager::get()->getCurrentMap()->eventHandelAll(event);

            }
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glUseProgram(shader_programme);

            Simple2D::MapManager::get()->getCurrentMap()->updateAll();
            Simple2D::MapManager::get()->getCurrentMap()->renderAll(shader_programme);

            SDL_GL_SwapWindow(window);

        }

        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }
}

#endif //SIMPLE2DENGINE_ENGINE_H
