#include "Samurai_commander.h"

Samurai_Commander::Samurai_Commander(){}
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

void Samurai_Commander::UnloadTex()
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
    UnloadTexture(protect);
    UnloadTexture(run);
    UnloadTexture(walk);
}
Samurai_Commander::~Samurai_Commander() {
    UnloadTex();
}