#include "GameState.h"
#include "MenuPause.h"

class PauseState : public GameState
{
private:
    MenuPause pauseMenu;

public:
    void Enter(Engine &);
    void Update(Engine &);
    void Draw(Engine &);
};
