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
    auto* gObj = new GameObject();
    gameObjects->push_back(gObj);
    gObj->path = path;

    ExternalCode::Handle h = ExternalCode::open(path + "/external.so");
    gObj->behavior = ((Behavior*(*)())(ExternalCode::find(h, "_entry_point")))();

    auto loadFunc = (void(*)(std::vector<GameObject*>*))(ExternalCode::find(h, "_prop_gameObjects"));
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

    gObj->behavior->init();

    return 0;
}

void Simple2D::Map::remove() {
    for(auto* g : *gameObjects){
        delete g;
    }
    delete gameObjects;
    gameObjects = nullptr;
}

void Simple2D::Map::updateAll() {
    for(auto g : *this->gameObjects){
        try {
            try {
                g->behavior->update();
            } catch (std::exception& e){
                printf("[ERROR] GameObject \"%s\" threw error while executing \"update()()\", error: \n%s \n", name.c_str(), e.what());
            }
        } catch (...){
            printf("[ERROR] GameObject \"%s\" threw error while executing \"update()\",\nthis error is not of type std::exception\nno further information can be provided  \n", name.c_str());
        }
    }
}

void Simple2D::Map::renderAll(GLuint shaderProgramme) {
    for(auto* gameObject : *this->gameObjects){
        gameObject->render(shaderProgramme);
    }
}

void Simple2D::Map::setupAll() {
    for(auto g : *this->gameObjects){
        try {
            try {
                g->behavior->setup();
            } catch (std::exception& e){
                printf("[ERROR] GameObject \"%s\" threw error while executing \"setup()\", error: \n%s \n", name.c_str(), e.what());
            }
        } catch (...){
            printf("[ERROR] GameObject \"%s\" threw error while executing \"setup()\",\nthis error is not of type std::exception\nno further information can be provided  \n", name.c_str());
        }


    }
}

void Simple2D::Map::eventHandelAll(SDL_Event e) {
    for(auto g : *this->gameObjects){
        try {
            try {
                g->behavior->onEvent(e);
            } catch (std::exception& e){
                printf("[ERROR] GameObject \"%s\" threw error while executing \"onEvent(SDL_Event& e)\", error: \n%s \n", name.c_str(), e.what());
            }
        } catch (...){
            printf("[ERROR] GameObject \"%s\" threw error while executing \"onEvent(SDL_Event& e)\",\nthis error is not of type std::exception\nno further information can be provided  \n", name.c_str());
        }


    }
}

