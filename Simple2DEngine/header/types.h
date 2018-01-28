//
// Created by albert on 1/27/18.
//

#ifndef SIMPLE2D_TYPES_H
#define SIMPLE2D_TYPES_H

namespace Simple2D{
    struct Vec3{
        float x,y,z;

        Vec3() = default;

        Vec3(float x, float y, float z){
            this->x = x; this->y = y; this->z = z;
        }
    };
}

#endif //SIMPLE2D_TYPES_H
