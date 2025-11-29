#include "EnterNameState.h"

void EnterNameState::Update(Engine &engine)
{
    menu.HandleInput(engine);
}

void EnterNameState::Draw(Engine &engine)
{
    menu.Draw();
}
