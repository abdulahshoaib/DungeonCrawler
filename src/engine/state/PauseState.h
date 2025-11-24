#include "GameState.h"
#include "MenuPause.h"

class PauseState : public GameState
{
private:
    MenuPause pauseMenu;

public:
    void Update(Engine &);
    void Draw(Engine &);
};
