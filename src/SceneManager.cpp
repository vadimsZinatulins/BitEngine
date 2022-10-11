#include "SceneManager.h"

namespace be::scene {

SceneManager &SceneManager::getInstance() {
    static SceneManager instance;
    return instance;
}

void SceneManager::popScene() {
    if(m_scenes.size()) {
        m_scenesToFree.push_back(m_scenes.top());
        m_scenes.pop();
    }
}

void SceneManager::popAllScenes() {
    while(m_scenes.size()) {
        m_scenesToFree.push_back(m_scenes.top());
        m_scenes.pop();
    }
}

IScene *SceneManager::getActiveScene() const {
    if(m_scenes.size()) return m_scenes.top();
    return nullptr;
}

void SceneManager::updateState() {
    for(IScene *scene : m_scenesToAdd) {
        scene->initialize();
        m_scenes.push(scene);
    }

    for(IScene *scene : m_scenesToFree) {
        scene->shutdown();
        delete scene;
    }

    m_scenesToAdd.clear();
    m_scenesToFree.clear();
}

}
