#include "Samurai_archer.h"

void Samurai_archer::LoadTex()
{
    attack[0] = LoadTexture("assets/Samurai_Char/Samurai_Archer/Attack_1.png");
    attack[1] = LoadTexture("assets/Samurai_Char/Samurai_Archer/Attack_2.png");
    attack[2] = LoadTexture("assets/Samurai_Char/Samurai_Archer/Attack_3.png");
    dead       = LoadTexture("assets/Samurai_Char/Samurai_Archer/Dead.png");
    hurt       = LoadTexture("assets/Samurai_Char/Samurai_Archer/Hurt.png");
    idle[0]       = LoadTexture("assets/Samurai_Char/Samurai_Archer/Idle.png");
    jump       = LoadTexture("assets/Samurai_Char/Samurai_Archer/Jump.png");
    run        = LoadTexture("assets/Samurai_Char/Samurai_Archer/Run.png");
    walk       = LoadTexture("assets/Samurai_Char/Samurai_Archer/Walk.png");
    arrow = LoadTexture("assets/Samurai_Char/Samurai_Archer/Arrow.png");
    shot[0] = LoadTexture("assets/Samurai_Char/Samurai_Archer/Shot.png");

}

void Samurai_archer::UnloadTex()
{
    for (int i = 0; i < 3; ++i) {
        UnloadTexture(attack[i]);
    }
    UnloadTexture(dead);
    UnloadTexture(hurt);
    for (int i = 0; i < 1; ++i) {
        UnloadTexture(idle[i]);
    }
    UnloadTexture(jump);
    UnloadTexture(run);
    UnloadTexture(walk);
    UnloadTexture(arrow);
    for (int i = 0; i < 1; ++i) {
        UnloadTexture(shot[i]);
    }
}