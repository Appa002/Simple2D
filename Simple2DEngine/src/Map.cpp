//
// Created by albert on 1/3/18.
//

#include "../header/Map.h"

Simple2D::Map::Map(){
    gameObjects = new std::vector<GameObject*>;
}

Simple2D::Map::Map(std::string& path) {
    gameObjects = new std::vector<GameObject*>;
    load(path);
}

Simple2D::Map::~Map() {
    if(gameObjects){
        remove();
    }
}

int Simple2D::Map::load(std::string path) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    if (luaL_loadfile(L, path.c_str()) || lua_pcall(L, 0, 0, 0)) {
        printf("Error");
        return -1;
    }

    Utils::pushToTop("data.name", L);
    this->name = lua_tostring(L, -1);
    lua_pop(L, 1);

    Utils::pushToTop("data.size", L);
    int amountOfGameObjects = (int)lua_tointeger(L, -1);
    lua_pop(L, 1);

    for(size_t i = 0; i < amountOfGameObjects; i++){
        Utils::pushToTop("data.object_" + std::to_string(i), L);
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

    gObj->path = path;
    gObj->handle = h;
    gObj->setupPointer = (void(*)())(ExternalCode::find(h, "setup"));
    gObj->updatePointer = (void(*)())(ExternalCode::find(h, "update"));
    gameObjects->push_back(gObj);

    auto loadFunc = (void(*)(std::vector<GameObject*>*))(ExternalCode::find(h, "load"));
    loadFunc(this->gameObjects);

    std::string luaPath = path + "/cfg.lua";
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    if (luaL_loadfile(L, luaPath.c_str()) || lua_pcall(L, 0, 0, 0)) {
        printf("GObj Error");
        return -1;
    }

    Utils::pushToTop("data.name", L);
    gObj->name = (char *)lua_tostring(L, -1);
    lua_pop(L, 1);

    Utils::pushToTop("data.size", L);
    int attributeAmount = (int)lua_tointeger(L, -1);
    lua_pop(L, 1);


    for(size_t i = 0; i < attributeAmount; i++){
        Utils::pushToTop("data.attribute_" + std::to_string(i), L);

        queryScript(L, gObj, h);
        lua_pop(L, 1);
    }

    return 0;
}

int Simple2D::Map::queryScript(lua_State *L, GameObject *gObj, Simple2D::ExternalCode::Handle handle) {
    Utils::pushToTop("name", L);
    std::string name = (char*)lua_tostring(L, -1);
    lua_remove(L, -1);

    Utils::pushToTop("valType", L);
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
    for(auto* g : *gameObjects){
        ExternalCode::close(g->handle);
        delete g;
    }
    delete gameObjects;
    gameObjects = nullptr;
}

void Simple2D::Map::updateAll() {
    for(auto g : *this->gameObjects){
        try {
            try {
                g->updatePointer();
            } catch (std::exception& e){
                printf("[ERROR] GameObject \"%s\" threw error while executing \"update()()\", error: \n%s \n", name.c_str(), e.what());
            }
        } catch (...){
            printf("[ERROR] GameObject \"%s\" threw error while executing \"update()\",\nthis error is not of type std::exception\nno further information can be provided  \n", name.c_str());
        }
    }
}

void Simple2D::Map::renderAll() {
    for(auto* gameObject : *this->gameObjects){
        gameObject->render();
    }
}

void Simple2D::Map::setupAll() {
    for(auto g : *this->gameObjects){
        try {
            try {
                g->setupPointer();
            } catch (std::exception& e){
                printf("[ERROR] GameObject \"%s\" threw error while executing \"setup()\", error: \n%s \n", name.c_str(), e.what());
            }
        } catch (...){
            printf("[ERROR] GameObject \"%s\" threw error while executing \"setup()\",\nthis error is not of type std::exception\nno further information can be provided  \n", name.c_str());
        }


    }
}

