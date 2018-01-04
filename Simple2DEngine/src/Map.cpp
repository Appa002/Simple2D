//
// Created by albert on 1/3/18.
//

#include "../header/Map.h"


Simple2D::Map::Map(std::string& path) {
    load(path);
}

Simple2D::Map::~Map() {
    remove();
}

int Simple2D::Map::load(std::string path) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    if (luaL_loadfile(L, path.c_str()) || lua_pcall(L, 0, 0, 0)) {
        printf("Error");
        return -1;
    }


    pushToTop("data.size", L);
    int amountOfGameObjects = (int)lua_tointeger(L, -1);
    lua_pop(L, 1);

    for(size_t i = 0; i < amountOfGameObjects; i++){
        pushToTop("data.object_" + std::to_string(i), L);
        std::string objectPath = lua_tostring(L, -1);
        lua_pop(L, 1);

        path = std::regex_replace(path, std::regex("\\/(?!.*\\/).*"), "");
        objectPath.insert(0, path + "/");

        loadGameObject(objectPath);
    }

}

int Simple2D::Map::loadGameObject(std::string path) {

    ExternalCode::Handle h = ExternalCode::open(path + "/external.so");
    auto* gObj = new GameObject();
    gObj->handle = h;

    gObj->setupPointer = (void(*)())(ExternalCode::find(h, "setup"));
    gObj->updatePointer = (void(*)())(ExternalCode::find(h, "update"));
    gameObjects.push_back(gObj);

    std::string luaPath = path + "/cfg.lua";
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    if (luaL_loadfile(L, luaPath.c_str()) || lua_pcall(L, 0, 0, 0)) {
        printf("GObj Error");
        return -1;
    }

    pushToTop("data.size", L);
    int attributeAmount = (int)lua_tointeger(L, -1);
    lua_pop(L, 1);

    for(size_t i = 0; i < attributeAmount; i++){
        pushToTop("data.attribute_" + std::to_string(i), L);

        queryScript(L, gObj, h);
        lua_pop(L, 1);
    }

    return 0;
}

int Simple2D::Map::queryScript(lua_State *L, GameObject *gObj, Simple2D::ExternalCode::Handle handle) {
    pushToTop("name", L);
    std::string name = (char*)lua_tostring(L, -1);
    lua_remove(L, -1);

    pushToTop("valType", L);
    std::string type = (char*)lua_tostring(L, -1);

    lua_remove(L, -1);


    if (type == "int") {
        gObj->addAttribute<int>(name, (int*)ExternalCode::find(handle, name));
    }

    else if (type == "string") {
        gObj->addAttribute<std::string>(name, (std::string*)ExternalCode::find(handle, name));
    }


    else if (type == "boolean") {
        gObj->addAttribute<bool>(name, (bool*)ExternalCode::find(handle, name));
    }


    else if (type == "double") {
        gObj->addAttribute<double>(name, (double*)ExternalCode::find(handle, name));
    }
    return 0;
}

void Simple2D::Map::remove() {

}

void Simple2D::Map::updateAll() {

}

void Simple2D::Map::renderAll() {

}

int Simple2D::Map::pushToTop(std::string name, lua_State *L) {
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

