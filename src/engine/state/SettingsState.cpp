#include "SettingsState.h"

void SettingsState::Update(Engine &engine)
{
    settingsMenu.HandleInput(engine);
}

void SettingsState::Draw(Engine &)
{
    settingsMenu.Draw();
}

SettingsState::~SettingsState() {}