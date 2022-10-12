#pragma once

namespace be::scene {

struct IScene {
    IScene() = default;
    virtual ~IScene() = default;
        
    virtual void initialize() = 0;
    virtual void shutdown() = 0;
        
    virtual void update() = 0;
    virtual void render() = 0;
};

}

