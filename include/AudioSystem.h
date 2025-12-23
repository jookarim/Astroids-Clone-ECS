#pragma once

#include "System.h"
#include "PhysicsSystem.h"

class ActionManager;

class AudioSystem : public System
{
private:
    ActionManager& m_actions;
    PhysicsSystem& m_physics;
    bool m_musicStarted = false;
    bool m_audioDisabled = false;
public:
    AudioSystem(ActionManager& actions, PhysicsSystem& physics);

    void setAudioDisabled(bool audioDisabled) { m_audioDisabled = audioDisabled; }
    bool getAudioDisabled() const { return m_audioDisabled; }

    void update(float dt) override;
};
