#include <stb_image.h>
#include <iostream>
#include "../header/GameObject.h"
#include "../header/types.h"
#include "../header/MapManager.h"

Simple2D::GameObject::GameObject() {
    spriteHeight = new int(0);
    spriteWidth = new int(0);
    vao = new GLuint(0);

    Attribute attr;
    attr.content = new int(0);
    attr.hash = typeid(int).hash_code();
    attr.name = "";

    GameObject::attributes.push_back(attr);

}

Simple2D::GameObject::~GameObject() {

    delete spriteHeight;
    delete spriteWidth;
    delete vao;

    GameObject::removeAttribute<int>("");
    if (!GameObject::attributes.empty())
        std::cout << "Not all attributes have been removed" << std::endl;
}

void Simple2D::GameObject::render(GLuint shaderProgramme) {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER,0.4);
    glEnable(GL_BLEND);
    glColor4f(1.0,1.0,1.0,1.0);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    if(!imageData)
        return;

    if(findAttribute<Vec3*>("position").isValid()){
        auto* posVec = getAttribute<Simple2D::Vec3*>("position");
        GLint loc = glGetUniformLocation(shaderProgramme, "pos");
        if(loc != -1){
            float data[3];
            *data = posVec->x;
            *(data + 1) = posVec->y;
            *(data + 2) = posVec->z;
            glUniform3fv(loc, 1, data);
        }
    }

    if(findAttribute<Vec3*>("scale").isValid()){
        auto* scaleVec = getAttribute<Simple2D::Vec3*>("scale");
        GLint loc = glGetUniformLocation(shaderProgramme, "scale");
        if(loc != -1){
            float data[3];
            *data = scaleVec->x;
            *(data + 1) = scaleVec->y;
            *(data + 2) = scaleVec->z;
            glUniform3fv(loc, 1, data);
        }
    }else{
        GLint loc = glGetUniformLocation(shaderProgramme, "scale");
        if(loc != -1){
            float data[3];
            *data = 1;
            *(data + 1) = 1;
            *(data + 2) = 1;
            glUniform3fv(loc, 1, data);
        }
    }

    GameObject* camObj = findOtherGameObject("Camera");
    if(camObj != nullptr){
        if(camObj->getAttribute<Simple2D::Vec3*>("position")){
            auto* camPos = camObj->getAttribute<Simple2D::Vec3*>("position");
            GLint loc = glGetUniformLocation(shaderProgramme, "camPos");
            if(loc != -1){
                float data[3];
                *data = camPos->x;
                *(data + 1) = camPos->y;
                *(data + 2) = camPos->z;
                glUniform3fv(loc, 1, data);
            }
        }
    }else{
        GLint loc = glGetUniformLocation(shaderProgramme, "camPos");
        if(loc != -1){
            float data[3] {0.0f, 0.0f, 0.0f};
            glUniform3fv(loc, 1, data);
        }
    }


    GLfloat pos[]{
            -0.5f, 0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,

            -0.5f, 0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f
    };

    GLuint posVbo;
    glGenBuffers(1, &posVbo);
    glBindBuffer(GL_ARRAY_BUFFER, posVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);

    glBindVertexArray(*vao);
    glBindBuffer(GL_ARRAY_BUFFER, posVbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);


    // Copy Sprite into opengl texture
    GLuint tex = 0;
    glGenTextures(1, &tex);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *spriteWidth, *spriteHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


    GLfloat texcoords[]{
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,

            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f
    };

    GLuint vtVbo;
    glGenBuffers(1, &vtVbo);
    glBindBuffer(GL_ARRAY_BUFFER, vtVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);

    glBindVertexArray(*vao);
    glBindBuffer(GL_ARRAY_BUFFER, vtVbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);


    glBindVertexArray(*vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);

}

void Simple2D::GameObject::preSetup() {
    glGenVertexArrays(1, vao);

    int n;
    imageData = stbi_load((path + "/sprite.png").c_str(), spriteWidth, spriteHeight, &n, 4);

    if(!imageData){
        printf("[WARNING] GameObject \"%s\" does not contain sprite.png at %s \n", name.c_str(), path.c_str());
        return;
    }

    // Check if dimensions are not a power of two.
    // Older GPUs can't handel textures which are not a power of two.
    if((*spriteWidth & (*spriteWidth - 1)) != 0 || (*spriteWidth & (*spriteHeight - 1)) != 0){
        printf("WARNING: Dimensions not a power of two for GameObject \"%s\" \n", name.c_str());
    }

    // Filp Images upside down
    int widthInBytes = 4 * *spriteWidth;
    unsigned char* top = nullptr;
    unsigned char* bottom = nullptr;
    unsigned char tmp = 0;
    int halfHeight = *spriteHeight / 2;

    for(int row = 0; row < halfHeight; row++){
        top = imageData + row * widthInBytes;
        bottom = imageData + (*spriteHeight - row - 1) * widthInBytes;
        for(int col = 0; col < widthInBytes; col++){
            tmp = *top;
            *top = *bottom;
            *bottom = tmp;
            top++;
            bottom++;
        }
    }
}

Simple2D::GameObject *Simple2D::GameObject::findOtherGameObject(std::string name) {
    for(auto gObj : *MapManager::get()->getCurrentMap()->gameObjects){
        if(gObj->name == name){
            return gObj;
        }
    }

    return nullptr;
}

void Simple2D::GameObject::loadNewSprite(std::string path) {
    int n;
    imageData = stbi_load(path.c_str(), spriteWidth, spriteHeight, &n, 4);

    if(!imageData){
        printf("[WARNING] GameObject \"%s\" does not contain sprite.png at %s \n", name.c_str(), path.c_str());
        return;
    }

    // Check if dimensions are not a power of two.
    // Older GPUs can't handel textures which are not a power of two.
    if((*spriteWidth & (*spriteWidth - 1)) != 0 || (*spriteWidth & (*spriteHeight - 1)) != 0){
        printf("[WARNING] Dimensions not a power of two for GameObject \"%s\" \n", name.c_str());
    }

    // Filp Images upside down
    int widthInBytes = 4 * *spriteWidth;
    unsigned char* top = nullptr;
    unsigned char* bottom = nullptr;
    unsigned char tmp = 0;
    int halfHeight = *spriteHeight / 2;

    for(int row = 0; row < halfHeight; row++){
        top = imageData + row * widthInBytes;
        bottom = imageData + (*spriteHeight - row - 1) * widthInBytes;
        for(int col = 0; col < widthInBytes; col++){
            tmp = *top;
            *top = *bottom;
            *bottom = tmp;
            top++;
            bottom++;
        }
    }
}

std::vector<Simple2D::Attribute>* Simple2D::GameObject::getAttributeVec() {
    return &this->attributes;
}
