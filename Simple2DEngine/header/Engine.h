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

namespace Simple2D{
    int startEngine(){

        const char* vertex_shader = "#version 410\n in vec3 vp; void main(){ gl_Position = vec4(vp.x, vp.y, vp.z, 1.0f); }\n";
        const char* fragment_shader = "#version 410\n out vec4 fragment_color; void main(){ fragment_color = vec4(0.0f, 0.5f, 0.5f, 1.0f); }\n";


        SDL_Init(SDL_INIT_VIDEO);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        SDL_Window* window = SDL_CreateWindow("Simple2D Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        SDL_GLContext context = SDL_GL_CreateContext(window);

        SDL_GL_MakeCurrent(window, context);

        glewExperimental = GL_TRUE;
        glewInit();
        SDL_GL_SetSwapInterval(1);

        const GLubyte* renderer = glGetString(GL_RENDERER);
        const GLubyte* version = glGetString(GL_VERSION);

        printf("Renderer: %s\n", renderer);
        printf("OpenGL Version: %s\n", version);

        glEnable(GL_DEPTH);
        glDepthFunc(GL_LESS);


        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vertex_shader, NULL);
        glCompileShader(vs);

        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fragment_shader, NULL);
        glCompileShader(fs);

        GLuint shader_programme = glCreateProgram();
        glAttachShader(shader_programme, vs);
        glAttachShader(shader_programme, fs);
        glLinkProgram(shader_programme);

        SDL_Event event;
        glClearColor(0.6f, 0.6f, 0.8f, 1.0f);

        bool bQuit = false;
        while (!bQuit) {

            while (SDL_PollEvent(&event) != 0) {
                if (event.type == SDL_QUIT) {
                    bQuit = true;
                }
            }

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glUseProgram(shader_programme);
            // glBindVertexArray(vao);
            // glDrawArrays(GL_TRIANGLES, 0, 6);

            SDL_GL_SwapWindow(window);

        }

        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }
}

#endif //SIMPLE2DENGINE_ENGINE_H
