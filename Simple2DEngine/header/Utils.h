//
// Created by albert on 1/9/18.
//

#ifndef SIMPLE2D_UTILS_H
#define SIMPLE2D_UTILS_H

#include <string>
#include <lua.hpp>
#include <iostream>


namespace Simple2D::Utils{

    inline int pushToTop(std::string name, lua_State *L) {
        std::string subPropertyName;			//example: "foo.bar.x": here foo, bar and x are subPropertyNames as they are seperated by a .
        for (unsigned int i = 0; i < name.size(); i++) {

            if (name.at(i) != '.') {
                subPropertyName += name.at(i);
            }

            if (name.at(i) == '.' || i + (unsigned int)(1) >= name.size())
            {
                lua_getglobal(L, subPropertyName.c_str());
                if(lua_isnil(L, -1)){
                    lua_remove(L, -1);
                    lua_getfield(L, -1, subPropertyName.c_str());
                }

                if (lua_isnil(L, -1)) {
                    printf("%s in %s is nil \n", subPropertyName.c_str(), name.c_str());
                    lua_pop(L, 1);
                    return -1;
                }

                subPropertyName = "";
            }

        }
        return 0;
    }

}

#endif //SIMPLE2D_UTILS_H
