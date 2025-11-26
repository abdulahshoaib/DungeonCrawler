#include "skeleton_warrior.h"

Skeleton_warrior::Skeleton_warrior(){}
void Skeleton_warrior::LoadTex(){
    attack[0] = LoadTexture("assets/Skeleton/Skeleton_Warrior/Attack_1.png");
    attack[1] = LoadTexture("assets/Skeleton/Skeleton_Warrior/Attack_2.png");
    attack[2] = LoadTexture("assets/Skeleton/Skeleton_Warrior/Attack_3.png");
    dead       = LoadTexture("assets/Skeleton/Skeleton_Warrior/Dead.png");
    hurt       = LoadTexture("assets/Skeleton/Skeleton_Warrior/Hurt.png");
    idle[0]       = LoadTexture("assets/Skeleton/Skeleton_Warrior/Idle.png");
    protect    = LoadTexture("assets/Skeleton/Skeleton_Warrior/Protect.png");
    run        = LoadTexture("assets/Skeleton/Skeleton_Warrior/Run.png");
    run_attack = LoadTexture("assets/Skeleton/Skeleton_Warrior/Run+Attack.png");
    walk       = LoadTexture("assets/Skeleton/Skeleton_Warrior/Walk.png");
}

void Skeleton_warrior::UnloadTex(){
    for (int i = 0; i < 3; i++) {UnloadTexture(attack[i]);}
    UnloadTexture(dead);
    UnloadTexture(hurt);
    UnloadTexture(idle[0]);
    UnloadTexture(protect);
    UnloadTexture(run);
    UnloadTexture(run_attack);
    UnloadTexture(walk);
}

Skeleton_warrior::~Skeleton_warrior() {
    UnloadTex();
}