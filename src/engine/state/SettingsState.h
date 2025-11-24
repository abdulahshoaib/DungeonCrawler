#include "GameState.h"
#include "MenuSettings.h"

class SettingsState : public GameState
{
private:
    MenuSettings settingsMenu;

public:
    void Update(Engine &);
    void Draw(Engine &);
};