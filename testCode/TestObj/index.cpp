#include "../../Simple2DEngine/header/Simple2D.h"

using namespace Simple2D;

class TestObj : public Behavior{

    Vec3* scale = nullptr;

    void init() override {
        scale = new Vec3(0.5f, 0.5f, 0.5f);
        addAttribute<Vec3>("scale", scale);
        addAttribute<Vec3>("position", new Vec3(0.0f, 0.0f, 0.0f));
    }

    void update() override {
    }

    void setup() override {
        cloneGameObject(findGameObject("TestObj"), "0")->behavior->setAttribute<Vec3>("position", Vec3(0.05f, 0.5f, 0.0f));
    }

    void onEvent(SDL_Event& e) override {
    }
};

REGISTER_GAME_OBJECT(TestObj)