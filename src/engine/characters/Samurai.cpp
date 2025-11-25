#include "Samurai.h"

void Samurai::LoadTex()
{
    attack[0] = LoadTexture("assets/Samurai_Char/Samurai/Attack_1.png");
    attack[1] = LoadTexture("assets/Samurai_Char/Samurai/Attack_2.png");
    attack[2] = LoadTexture("assets/Samurai_Char/Samurai/Attack_3.png");
    dead       = LoadTexture("assets/Samurai_Char/Samurai/Dead.png");
    hurt       = LoadTexture("assets/Samurai_Char/Samurai/Hurt.png");
    idle[0]       = LoadTexture("assets/Samurai_Char/Samurai/Idle.png");
    jump       = LoadTexture("assets/Samurai_Char/Samurai/Jump.png");
    protect    = LoadTexture("assets/Samurai_Char/Samurai/Protection.png");
    run        = LoadTexture("assets/Samurai_Char/Samurai/Run.png");
    walk       = LoadTexture("assets/Samurai_Char/Samurai/Walk.png");

}

void Samurai::UnloadTex()
{
    for (int i = 0; i < 3; i++) {UnloadTexture(attack[i]);}
    UnloadTexture(dead);
    UnloadTexture(hurt);
    UnloadTexture(idle[0]);
    UnloadTexture(jump);
    UnloadTexture(protect);
    UnloadTexture(run);
    UnloadTexture(walk);
}