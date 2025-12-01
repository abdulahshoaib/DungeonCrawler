#ifndef ENTER_NAME_STATE_H
#define ENTER_NAME_STATE_H

#include "GameState.h"
#include "../../ui/menus/MenuEnterName.h"

class EnterNameState : public GameState
{
private:
    MenuEnterName menu;

public:
    EnterNameState() = default;

    void Update(Engine &engine) override;
    void Draw(Engine &engine) override;
};

#endif
