#include "Skeleton_spearman.h"

void Skeleton_spearman::LoadTex()
{
    attack[0] = LoadTexture("assets/Skeleton/Skeleton_Spearman/Attack_1.png");
    attack[1] = LoadTexture("assets/Skeleton/Skeleton_Spearman/Attack_2.png");
    dead       = LoadTexture("assets/Skeleton/Skeleton_Spearman/Dead.png");
    hurt       = LoadTexture("assets/Skeleton/Skeleton_Spearman/Hurt.png");
    idle[0]       = LoadTexture("assets/Skeleton/Skeleton_Spearman/Idle.png");
    run        = LoadTexture("assets/Skeleton/Skeleton_Spearman/Run.png");
    walk       = LoadTexture("assets/Skeleton/Skeleton_Spearman/Walk.png");
    protect    = LoadTexture("assets/Skeleton/Skeleton_Spearman/Protect.png");
    run_attack = LoadTexture("assets/Skeleton/Skeleton_Spearman/Run+Attack.png");
    fall = LoadTexture("assets/Skeleton/Skeleton_Spearman/Fall.png");
}

void Skeleton_spearman::UnloadTex()
{
    for (int i = 0; i < 2; i++) {UnloadTexture(attack[i]);}
    UnloadTexture(dead);
    UnloadTexture(hurt);
    UnloadTexture(idle[0]);
    UnloadTexture(run);
    UnloadTexture(walk);
    UnloadTexture(protect);
    UnloadTexture(run_attack);
    UnloadTexture(fall);
}