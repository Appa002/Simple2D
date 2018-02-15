#include "../../Simple2DEngine/header/Simple2D.h"

using namespace Simple2D;

class Camera : public Behavior{
    Vec3* position = nullptr;

    void init() override {
        position = new Vec3(0.0f, 0.0f, 0.0f);
        addAttribute<Vec3>("position", position);
    }

    void update() override {
    }

    void setup() override {
    }

    void onRemoval() override{
        deleteAttribute<Vec3>("position");
    }

    void onEvent(SDL_Event& e) override {
        if(e.type == SDL_KEYDOWN){
            std::cout << "Aua" << std::endl;
        }
    }
};

REGISTER_GAME_OBJECT(Camera)