#include "Skeleton_archer.h"

void Skeleton_archer::LoadTex()
{
    attack[0] = LoadTexture("assets/Skeleton/Skeleton_Archer/Attack_1.png");
    attack[1] = LoadTexture("assets/Skeleton/Skeleton_Archer/Attack_2.png");
    attack[2] = LoadTexture("assets/Skeleton/Skeleton_Archer/Attack_3.png");
    dead       = LoadTexture("assets/Skeleton/Skeleton_Archer/Dead.png");
    hurt       = LoadTexture("assets/Skeleton/Skeleton_Archer/Hurt.png");
    idle[0]       = LoadTexture("assets/Skeleton/Skeleton_Archer/Idle.png");
    arrow = LoadTexture("assets/Skeleton/Skeleton_Archer/Arrow.png");
    shot[0] = LoadTexture("assets/Skeleton/Skeleton_Archer/Shot_1.png");
    shot[1] = LoadTexture("assets/Skeleton/Skeleton_Archer/Shot_2.png");    
    evasion   = LoadTexture("assets/Skeleton/Skeleton_Archer/Evasion.png");
    walk       = LoadTexture("assets/Skeleton/Skeleton_Archer/Walk.png");
    
}