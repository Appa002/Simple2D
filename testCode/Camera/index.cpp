#include "../../Simple2DEngine/header/Simple2D.h"

using namespace Simple2D;

class Camera : public Behavior{
    Vec3* position = nullptr;

    void init() override {
        position = new Vec3(0.0f, 0.0f, 0.0f);
    }

    void update() override {
        std::cout << "Oi, Oi" << std::endl;
    }

    void setup() override {
        std::cout << "SetmeUp inside" << std::endl;
    }

    void onEvent(SDL_Event& e) override {
        if(e.type == SDL_KEYDOWN){
            std::cout << "Aua" << std::endl;
        }
    }
};

REGISTER_GAME_OBJECT(Camera)