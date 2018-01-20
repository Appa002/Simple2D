#include "../header/GameObject.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../header/stb_image.h"


void Simple2D::GameObject::render(){
    // Copy Sprite into opengl texture
    GLuint tex = 0;
    glGenTextures(1, &tex);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *x, *y, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


    GLfloat texcoords[]{
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
    };

    GLuint vtVbo;
    glGenBuffers(1, &vtVbo);
    glBindBuffer(GL_ARRAY_BUFFER, vtVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);

    glBindVertexArray(*vao);
    glBindBuffer(GL_ARRAY_BUFFER, vtVbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);


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



    glBindVertexArray(*vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);

}


void Simple2D::GameObject::preSetup() {
    glGenVertexArrays(1, vao);

    imageData = stbi_load((path + "/sprite.bmp").c_str(), x, y, n, forceChannels);
    if(!imageData) {
        printf("GameObject \"%s\" doesn't contain a sprite.png at \"%s\"! \n", name.c_str(), path.c_str());
        return;
    }

    // Check if dimensions are not a power of two.
    // Older GPUs can't handel textures which are not a power of two.
    if((*x & (*x - 1)) != 0 || (*y & (*y - 1)) != 0){
        printf("WARNING: Dimensions not a power of two for GameObject \"%s\" \n", name.c_str());
    }


    // Filp Images upside down
    int widthInBytes = 4 * *x;
    unsigned char* top = nullptr;
    unsigned char* bottom = nullptr;
    unsigned char tmp = 0;
    int halfHeight = *y / 2;

    for(int row = 0; row < halfHeight; row++){
        top = imageData + row * widthInBytes;
        bottom = imageData + (*y - row - 1) * widthInBytes;
        for(int col = 0; col < widthInBytes; col++){
            tmp = *top;
            *top = *bottom;
            *bottom = tmp;
            top++;
            bottom++;
        }
    }
}
