#pragma once

#include "IScene.h"

#include <stack>
#include <vector>

namespace be {

class Engine;

}

namespace be::scene {

class SceneManager {
public:
    static SceneManager &getInstance();

    template<typename T>
    void pushScene() {
        m_scenesToAdd.push_back(new T());
    }

    template<typename T>
    void swap() {
        popScene();
        pushScene<T>();
    }

    void popScene();
    void popAllScenes();
private:
	friend class be::Engine;

    SceneManager() = default;
    ~SceneManager() = default;

    void updateState();

    IScene *getActiveScene() const;

    std::stack<IScene*> m_scenes;

    std::vector<IScene*> m_scenesToAdd;
    std::vector<IScene*> m_scenesToFree;
};

}

