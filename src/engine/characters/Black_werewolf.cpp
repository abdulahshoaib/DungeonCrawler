#include "Black_werewolf.h"

void Black_werewolf::LoadTex(){
    attack[0] = LoadTexture("assets/WereWolf/Black_Werewolf/Attack_1.png");
    attack[1] = LoadTexture("assets/WereWolf/Black_Werewolf/Attack_2.png");
    attack[2] = LoadTexture("assets/WereWolf/Black_Werewolf/Attack_3.png");
    dead       = LoadTexture("assets/WereWolf/Black_Werewolf/Dead.png");
    hurt = LoadTexture("assets/WereWolf/Black_Werewolf/Hurt.png");
    idle[0]       = LoadTexture("assets/WereWolf/Black_Werewolf/Idle.png");
    jump       = LoadTexture("assets/WereWolf/Black_Werewolf/Jump.png");
    run        = LoadTexture("assets/WereWolf/Black_Werewolf/Run.png");
    walk       = LoadTexture("assets/WereWolf/Black_Werewolf/Walk.png");
    run_attack = LoadTexture("assets/WereWolf/Black_Werewolf/Run+Attack.png");
}

void Black_werewolf::UnloadTex(){
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
    UnloadTexture(run_attack);
}