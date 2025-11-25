#include "Samurai_commander.h"

void Samurai_Commander::LoadTex()
{
    attack[0] = LoadTexture("assets/Samurai_Char/Samurai_Commander/Attack_1.png");
    attack[1] = LoadTexture("assets/Samurai_Char/Samurai_Commander/Attack_2.png");
    attack[2] = LoadTexture("assets/Samurai_Char/Samurai_Commander/Attack_3.png");
    dead       = LoadTexture("assets/Samurai_Char/Samurai_Commander/Dead.png");
    hurt       = LoadTexture("assets/Samurai_Char/Samurai_Commander/Hurt.png");
    idle[0]       = LoadTexture("assets/Samurai_Char/Samurai_Commander/Idle.png");
    jump       = LoadTexture("assets/Samurai_Char/Samurai_Commander/Jump.png");
    protect    = LoadTexture("assets/Samurai_Char/Samurai_Commander/Protect.png");
    run        = LoadTexture("assets/Samurai_Char/Samurai_Commander/Run.png");
    walk       = LoadTexture("assets/Samurai_Char/Samurai_Commander/Walk.png");

}