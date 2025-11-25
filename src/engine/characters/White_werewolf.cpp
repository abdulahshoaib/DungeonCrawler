#include "White_werewolf.h"

void White_werewolf::LoadTex(){
    attack[0] = LoadTexture("assests/WereWolf/White_Werewolf/Attack_1.png");
    attack[1] = LoadTexture("assests/WereWolf/White_Werewolf/Attack_2.png");
    attack[2] = LoadTexture("assests/WereWolf/White_Werewolf/Attack_3.png");
    dead       = LoadTexture("assests/WereWolf/White_Werewolf/Dead.png"); 
    hurt = LoadTexture("assests/WereWolf/White_Werewolf/Hurt.png");
    idle[0]       = LoadTexture("assests/WereWolf/White_Werewolf/Idle.png");
    jump       = LoadTexture("assests/WereWolf/White_Werewolf/Jump.png");
    run        = LoadTexture("assests/WereWolf/White_Werewolf/Run.png");
    walk       = LoadTexture("assests/WereWolf/White_Werewolf/Walk.png");
    run_attack = LoadTexture("assests/WereWolf/White_Werewolf/Run+Attack.png");
}