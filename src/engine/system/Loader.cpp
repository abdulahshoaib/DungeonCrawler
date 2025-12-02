#include "Loader.h"

void Loader::LoadSkeletonSpearman()
{
    int frameSize = 128;
    SkeletonSpearmanAttack1 = {LoadTexture("assets/Skeleton/Skeleton_Spearman/Attack_1.png"), frameSize, frameSize, 4, 26};
    SkeletonSpearmanAttack2 = {LoadTexture("assets/Skeleton/Skeleton_Spearman/Attack_2.png"), frameSize, frameSize, 4, 26};
    SkeletonSpearmanDead = {LoadTexture("assets/Skeleton/Skeleton_Spearman/Dead.png"), frameSize, frameSize, 5, 14};
    SkeletonSpearmanHurt = {LoadTexture("assets/Skeleton/Skeleton_Spearman/Hurt.png"), frameSize, frameSize, 3, 18};
    SkeletonSpearmanIdle = {LoadTexture("assets/Skeleton/Skeleton_Spearman/Idle.png"), frameSize, frameSize, 7, 14};
    SkeletonSpearmanProtect = {LoadTexture("assets/Skeleton/Skeleton_Spearman/Protect.png"), frameSize, frameSize, 2, 12};
    SkeletonSpearmanRun = {LoadTexture("assets/Skeleton/Skeleton_Spearman/Run.png"), frameSize, frameSize, 6, 24};
    SkeletonSpearmanRunAttack = {LoadTexture("assets/Skeleton/Skeleton_Spearman/Walk.png"), frameSize, frameSize, 5, 22};
    SkeletonSpearmanWalk = {LoadTexture("assets/Skeleton/Skeleton_Spearman/Run+Attack.png"), frameSize, frameSize, 8, 14};
}

void Loader::UnLoadSkeletonSpearman()
{
    UnloadTexture(SkeletonSpearmanAttack1.spriteSheet);
    UnloadTexture(SkeletonSpearmanAttack2.spriteSheet);
    UnloadTexture(SkeletonSpearmanDead.spriteSheet);
    UnloadTexture(SkeletonSpearmanHurt.spriteSheet);
    UnloadTexture(SkeletonSpearmanIdle.spriteSheet);
    UnloadTexture(SkeletonSpearmanProtect.spriteSheet);
    UnloadTexture(SkeletonSpearmanRun.spriteSheet);
    UnloadTexture(SkeletonSpearmanRunAttack.spriteSheet);
    UnloadTexture(SkeletonSpearmanWalk.spriteSheet);
}

void Loader::LoadKarasuTengu()
{
    int frameSize = 128;
    KarasuTenguAttack1 = {LoadTexture("assets/Yokai/Karasu_tengu/Attack_1.png"), frameSize, frameSize, 6, 28};
    KarasuTenguAttack2 = {LoadTexture("assets/Yokai/Karasu_tengu/Attack_2.png"), frameSize, frameSize, 4, 26};
    KarasuTenguAttack3 = {LoadTexture("assets/Yokai/Karasu_tengu/Attack_3.png"), frameSize, frameSize, 3, 26};
    KarasuTenguDead = {LoadTexture("assets/Yokai/Karasu_tengu/Dead.png"), frameSize, frameSize, 6, 14};
    KarasuTenguHurt = {LoadTexture("assets/Yokai/Karasu_tengu/Hurt.png"), frameSize, frameSize, 3, 18};
    KarasuTenguRun = {LoadTexture("assets/Yokai/Karasu_tengu/Run.png"), frameSize, frameSize, 8, 26};
    KarasuTenguWalk = {LoadTexture("assets/Yokai/Karasu_tengu/Walk.png"), frameSize, frameSize, 8, 14};
    KarasuTenguIdle1 = {LoadTexture("assets/Yokai/Karasu_tengu/Idle.png"), frameSize, frameSize, 6, 14};
    KarasuTenguIdle2 = {LoadTexture("assets/Yokai/Karasu_tengu/Idle_2.png"), frameSize, frameSize, 5, 14};
}
void Loader::UnLoadKarasuTengu()
{
    UnloadTexture(KarasuTenguAttack1.spriteSheet);
    UnloadTexture(KarasuTenguAttack2.spriteSheet);
    UnloadTexture(KarasuTenguAttack3.spriteSheet);
    UnloadTexture(KarasuTenguDead.spriteSheet);
    UnloadTexture(KarasuTenguHurt.spriteSheet);
    UnloadTexture(KarasuTenguRun.spriteSheet);
    UnloadTexture(KarasuTenguWalk.spriteSheet);
    UnloadTexture(KarasuTenguIdle1.spriteSheet);
    UnloadTexture(KarasuTenguIdle2.spriteSheet);
}

void Loader::LoadSkeletonWarrior()
{
    int frameSize = 128;
    SkeletonWarriorAttack1 = {LoadTexture("assets/Skeleton/Skeleton_Warrior/Attack_1.png"), frameSize, frameSize, 5, 11};
    SkeletonWarriorAttack2 = {LoadTexture("assets/Skeleton/Skeleton_Warrior/Attack_2.png"), frameSize, frameSize, 6, 13};
    SkeletonWarriorAttack3 = {LoadTexture("assets/Skeleton/Skeleton_Warrior/Attack_3.png"), frameSize, frameSize, 4, 13};
    SkeletonWarriorDead = {LoadTexture("assets/Skeleton/Skeleton_Warrior/Dead.png"), frameSize, frameSize, 4, 7};
    SkeletonWarriorHurt = {LoadTexture("assets/Skeleton/Skeleton_Warrior/Hurt.png"), frameSize, frameSize, 2, 9};
    SkeletonWarriorIdle = {LoadTexture("assets/Skeleton/Skeleton_Warrior/Idle.png"), frameSize, frameSize, 7, 7};
    SkeletonWarriorProtect = {LoadTexture("assets/Skeleton/Skeleton_Warrior/Protect.png"), frameSize, frameSize, 1, 9};
    SkeletonWarriorRun = {LoadTexture("assets/Skeleton/Skeleton_Warrior/Run.png"), frameSize, frameSize, 8, 8};
    SkeletonWarriorRunAttack = {LoadTexture("assets/Skeleton/Skeleton_Warrior/Run+Attack.png"), frameSize, frameSize, 7, 11};
    SkeletonWarriorWalk = {LoadTexture("assets/Skeleton/Skeleton_Warrior/Walk.png"), frameSize, frameSize, 7, 5};
}
void Loader::UnLoadSkeletonWarrior()
{
    UnloadTexture(SkeletonWarriorAttack1.spriteSheet);
    UnloadTexture(SkeletonWarriorAttack2.spriteSheet);
    UnloadTexture(SkeletonWarriorAttack3.spriteSheet);
    UnloadTexture(SkeletonWarriorDead.spriteSheet);
    UnloadTexture(SkeletonWarriorHurt.spriteSheet);
    UnloadTexture(SkeletonWarriorIdle.spriteSheet);
    UnloadTexture(SkeletonWarriorProtect.spriteSheet);
    UnloadTexture(SkeletonWarriorRun.spriteSheet);
    UnloadTexture(SkeletonWarriorRunAttack.spriteSheet);
    UnloadTexture(SkeletonWarriorWalk.spriteSheet);
}

void Loader::LoadSkeletonArcher()
{
    int frameSize = 128;
    SkeletonArcherAttack1 = {LoadTexture("assets/Skeleton/Skeleton_Archer/Attack_1.png"), frameSize, frameSize, 5, 22};
    SkeletonArcherAttack2 = {LoadTexture("assets/Skeleton/Skeleton_Archer/Attack_2.png"), frameSize, frameSize, 4, 24};
    SkeletonArcherAttack3 = {LoadTexture("assets/Skeleton/Skeleton_Archer/Attack_3.png"), frameSize, frameSize, 3, 24};
    SkeletonArcherDead = {LoadTexture("assets/Skeleton/Skeleton_Archer/Dead.png"), frameSize, frameSize, 5, 14};
    SkeletonArcherEvasion = {LoadTexture("assets/Skeleton/Skeleton_Archer/Evasion.png"), frameSize, frameSize, 6, 18};
    SkeletonArcherHurt = {LoadTexture("assets/Skeleton/Skeleton_Archer/Hurt.png"), frameSize, frameSize, 2, 14};
    SkeletonArcherIdle = {LoadTexture("assets/Skeleton/Skeleton_Archer/Idle.png"), frameSize, frameSize, 7, 28};
    SkeletonArcherShot1 = {LoadTexture("assets/Skeleton/Skeleton_Archer/Shot_1.png"), frameSize, frameSize, 15, 24};
    SkeletonArcherShot2 = {LoadTexture("assets/Skeleton/Skeleton_Archer/Shot_2.png"), frameSize, frameSize, 15, 16};
    SkeletonArcherWalk = {LoadTexture("assets/Skeleton/Skeleton_Archer/Walk.png"), frameSize, frameSize, 8, 14};
}

void Loader::UnLoadSkeletonArcher()
{
    UnloadTexture(SkeletonArcherAttack1.spriteSheet);
    UnloadTexture(SkeletonArcherAttack2.spriteSheet);
    UnloadTexture(SkeletonArcherAttack3.spriteSheet);
    UnloadTexture(SkeletonArcherDead.spriteSheet);
    UnloadTexture(SkeletonArcherEvasion.spriteSheet);
    UnloadTexture(SkeletonArcherHurt.spriteSheet);
    UnloadTexture(SkeletonArcherIdle.spriteSheet);
    UnloadTexture(SkeletonArcherShot1.spriteSheet);
    UnloadTexture(SkeletonArcherShot2.spriteSheet);
    UnloadTexture(SkeletonArcherWalk.spriteSheet);
}

void Loader::LoadKnight1()
{
    int frameSize = 128;
    Knight1Attack1 = {LoadTexture("assets/Knight/Knight_1/Attack1.png"), frameSize, frameSize, 5, 12};
    Knight1Attack2 = {LoadTexture("assets/Knight/Knight_1/Attack2.png"), frameSize, frameSize, 6, 12};
    Knight1Attack3 = {LoadTexture("assets/Knight/Knight_1/Attack3.png"), frameSize, frameSize, 6, 12};
    Knight1Dead = {LoadTexture("assets/Knight/Knight_1/Dead.png"), frameSize, frameSize, 5, 12};
    Knight1Defend = {LoadTexture("assets/Knight/Knight_1/Defend.png"), frameSize, frameSize, 1, 16};
    Knight1Hurt = {LoadTexture("assets/Knight/Knight_1/Hurt.png"), frameSize, frameSize, 2, 12};
    Knight1Idle = {LoadTexture("assets/Knight/Knight_1/Idle.png"), frameSize, frameSize, 7, 18};
    Knight1Jump = {LoadTexture("assets/Knight/Knight_1/Jump.png"), frameSize, frameSize, 3, 12};
    Knight1Protect = {LoadTexture("assets/Knight/Knight_1/Protect.png"), frameSize, frameSize, 1, 12};
    Knight1Run = {LoadTexture("assets/Knight/Knight_1/Run.png"), frameSize, frameSize, 8, 18};
    Knight1RunAttack = {LoadTexture("assets/Knight/Knight_1/Run+Attack.png"), frameSize, frameSize, 6, 18};
    Knight1Walk = {LoadTexture("assets/Knight/Knight_1/Walk.png"), frameSize, frameSize, 8, 12};
}
void Loader::UnLoadKnight1()
{
    UnloadTexture(Knight1Attack1.spriteSheet);
    UnloadTexture(Knight1Attack2.spriteSheet);
    UnloadTexture(Knight1Attack3.spriteSheet);
    UnloadTexture(Knight1Dead.spriteSheet);
    UnloadTexture(Knight1Defend.spriteSheet);
    UnloadTexture(Knight1Hurt.spriteSheet);
    UnloadTexture(Knight1Idle.spriteSheet);
    UnloadTexture(Knight1Jump.spriteSheet);
    UnloadTexture(Knight1Protect.spriteSheet);
    UnloadTexture(Knight1Run.spriteSheet);
    UnloadTexture(Knight1RunAttack.spriteSheet);
    UnloadTexture(Knight1Walk.spriteSheet);
}

void Loader::LoadKnight2()
{
    int frameSize = 128;
    Knight2Attack1 = {LoadTexture("assets/Knight/Knight_2/Attack1.png"), frameSize, frameSize, 5, 12};
    Knight2Attack2 = {LoadTexture("assets/Knight/Knight_2/Attack2.png"), frameSize, frameSize, 4, 12};
    Knight2Attack3 = {LoadTexture("assets/Knight/Knight_2/Attack3.png"), frameSize, frameSize, 4, 12};
    Knight2Dead = {LoadTexture("assets/Knight/Knight_2/Dead.png"), frameSize, frameSize, 6, 12};
    Knight2Defend = {LoadTexture("assets/Knight/Knight_2/Defend.png"), frameSize, frameSize, 5, 16};
    Knight2Hurt = {LoadTexture("assets/Knight/Knight_2/Hurt.png"), frameSize, frameSize, 2, 12};
    Knight2Idle = {LoadTexture("assets/Knight/Knight_2/Idle.png"), frameSize, frameSize, 4, 18};
    Knight2Jump = {LoadTexture("assets/Knight/Knight_2/Jump.png"), frameSize, frameSize, 6, 12};
    Knight2Protect = {LoadTexture("assets/Knight/Knight_2/Protect.png"), frameSize, frameSize, 1, 12};
    Knight2Run = {LoadTexture("assets/Knight/Knight_2/Run.png"), frameSize, frameSize, 7, 18};
    Knight2RunAttack = {LoadTexture("assets/Knight/Knight_2/Run+Attack.png"), frameSize, frameSize, 6, 18};
    Knight2Walk = {LoadTexture("assets/Knight/Knight_2/Walk.png"), frameSize, frameSize, 8, 12};
}
void Loader::UnLoadKnight2()
{
    UnloadTexture(Knight2Attack1.spriteSheet);
    UnloadTexture(Knight2Attack2.spriteSheet);
    UnloadTexture(Knight2Attack3.spriteSheet);
    UnloadTexture(Knight2Dead.spriteSheet);
    UnloadTexture(Knight2Defend.spriteSheet);
    UnloadTexture(Knight2Hurt.spriteSheet);
    UnloadTexture(Knight2Idle.spriteSheet);
    UnloadTexture(Knight2Jump.spriteSheet);
    UnloadTexture(Knight2Protect.spriteSheet);
    UnloadTexture(Knight2Run.spriteSheet);
    UnloadTexture(Knight2RunAttack.spriteSheet);
    UnloadTexture(Knight2Walk.spriteSheet);
}

void Loader::LoadKnight3()
{
    int frameSize = 128;
    Knight3Attack1 = {LoadTexture("assets/Knight/Knight_3/Attack1.png"), frameSize, frameSize, 3, 12};
    Knight3Attack2 = {LoadTexture("assets/Knight/Knight_3/Attack2.png"), frameSize, frameSize, 4, 12};
    Knight3Attack3 = {LoadTexture("assets/Knight/Knight_3/Attack3.png"), frameSize, frameSize, 4, 12};
    Knight3Dead = {LoadTexture("assets/Knight/Knight_3/Dead.png"), frameSize, frameSize, 6, 12};
    Knight3Defend = {LoadTexture("assets/Knight/Knight_3/Defend.png"), frameSize, frameSize, 5, 16};
    Knight3Hurt = {LoadTexture("assets/Knight/Knight_3/Hurt.png"), frameSize, frameSize, 2, 12};
    Knight3Idle = {LoadTexture("assets/Knight/Knight_3/Idle.png"), frameSize, frameSize, 4, 18};
    Knight3Jump = {LoadTexture("assets/Knight/Knight_3/Jump.png"), frameSize, frameSize, 6, 12};
    Knight3Protect = {LoadTexture("assets/Knight/Knight_3/Protect.png"), frameSize, frameSize, 1, 12};
    Knight3Run = {LoadTexture("assets/Knight/Knight_3/Run.png"), frameSize, frameSize, 7, 18};
    Knight3RunAttack = {LoadTexture("assets/Knight/Knight_3/Run+Attack.png"), frameSize, frameSize, 6, 18};
    Knight3Walk = {LoadTexture("assets/Knight/Knight_3/Walk.png"), frameSize, frameSize, 8, 12};
}

void Loader::UnLoadKnight3()
{
    UnloadTexture(Knight3Attack1.spriteSheet);
    UnloadTexture(Knight3Attack2.spriteSheet);
    UnloadTexture(Knight3Attack3.spriteSheet);
    UnloadTexture(Knight3Dead.spriteSheet);
    UnloadTexture(Knight3Defend.spriteSheet);
    UnloadTexture(Knight3Hurt.spriteSheet);
    UnloadTexture(Knight3Idle.spriteSheet);
    UnloadTexture(Knight3Jump.spriteSheet);
    UnloadTexture(Knight3Protect.spriteSheet);
    UnloadTexture(Knight3Run.spriteSheet);
    UnloadTexture(Knight3RunAttack.spriteSheet);
    UnloadTexture(Knight3Walk.spriteSheet);
}

void Loader::LoadYamabushiTengu()
{
    int frameSize = 128;

    YamabushiTenguAttack1 = {LoadTexture("assets/Yokai/Yamabushi_tengu/Attack_1.png"), frameSize, frameSize, 3, 26};
    YamabushiTenguAttack2 = {LoadTexture("assets/Yokai/Yamabushi_tengu/Attack_2.png"), frameSize, frameSize, 6, 28};
    YamabushiTenguAttack3 = {LoadTexture("assets/Yokai/Yamabushi_tengu/Attack_3.png"), frameSize, frameSize, 4, 28};
    YamabushiTenguDead = {LoadTexture("assets/Yokai/Yamabushi_tengu/Dead.png"), frameSize, frameSize, 6, 14};
    YamabushiTenguHurt = {LoadTexture("assets/Yokai/Yamabushi_tengu/Hurt.png"), frameSize, frameSize, 3, 18};
    YamabushiTenguIdle1 = {LoadTexture("assets/Yokai/Yamabushi_tengu/Idle.png"), frameSize, frameSize, 6, 14};
    YamabushiTenguIdle2 = {LoadTexture("assets/Yokai/Yamabushi_tengu/Idle_2.png"), frameSize, frameSize, 5, 14};
    YamabushiTenguRun = {LoadTexture("assets/Yokai/Yamabushi_tengu/Run.png"), frameSize, frameSize, 8, 26};
    YamabushiTenguWalk = {LoadTexture("assets/Yokai/Yamabushi_tengu/Walk.png"), frameSize, frameSize, 8, 14};
}

void Loader::UnLoadYamabushiTengu()
{
    UnloadTexture(YamabushiTenguAttack1.spriteSheet);
    UnloadTexture(YamabushiTenguAttack2.spriteSheet);
    UnloadTexture(YamabushiTenguAttack3.spriteSheet);
    UnloadTexture(YamabushiTenguDead.spriteSheet);
    UnloadTexture(YamabushiTenguHurt.spriteSheet);
    UnloadTexture(YamabushiTenguIdle1.spriteSheet);
    UnloadTexture(YamabushiTenguIdle2.spriteSheet);
    UnloadTexture(YamabushiTenguRun.spriteSheet);
    UnloadTexture(YamabushiTenguWalk.spriteSheet);
}

void Loader::LoadSamurai()
{
    int frameSize = 128;
    SamuraiAttack1 = {LoadTexture("assets/Samurai_Char/Samurai/Attack_1.png"), frameSize, frameSize, 4, 26};
    SamuraiAttack2 = {LoadTexture("assets/Samurai_Char/Samurai/Attack_2.png"), frameSize, frameSize, 5, 26};
    SamuraiAttack3 = {LoadTexture("assets/Samurai_Char/Samurai/Attack_3.png"), frameSize, frameSize, 4, 26};
    SamuraiDead = {LoadTexture("assets/Samurai_Char/Samurai/Dead.png"), frameSize, frameSize, 6, 14};
    SamuraiHurt = {LoadTexture("assets/Samurai_Char/Samurai/Hurt.png"), frameSize, frameSize, 3, 18};
    SamuraiIdle = {LoadTexture("assets/Samurai_Char/Samurai/Idle.png"), frameSize, frameSize, 6, 14};
    SamuraiJump = {LoadTexture("assets/Samurai_Char/Samurai/Jump.png"), frameSize, frameSize, 9, 20};
    SamuraiRun = {LoadTexture("assets/Samurai_Char/Samurai/Run.png"), frameSize, frameSize, 8, 26};
    SamuraiWalk = {LoadTexture("assets/Samurai_Char/Samurai/Walk.png"), frameSize, frameSize, 9, 14};
    SamuraiProtect = {LoadTexture("assets/Samurai_Char/Samurai/Protection.png"), frameSize, frameSize, 2, 12};
}

void Loader::UnLoadSamurai()
{
    UnloadTexture(SamuraiAttack1.spriteSheet);
    UnloadTexture(SamuraiAttack2.spriteSheet);
    UnloadTexture(SamuraiAttack3.spriteSheet);
    UnloadTexture(SamuraiDead.spriteSheet);
    UnloadTexture(SamuraiHurt.spriteSheet);
    UnloadTexture(SamuraiIdle.spriteSheet);
    UnloadTexture(SamuraiJump.spriteSheet);
    UnloadTexture(SamuraiRun.spriteSheet);
    UnloadTexture(SamuraiWalk.spriteSheet);
    UnloadTexture(SamuraiProtect.spriteSheet);
}

void Loader::LoadSamuraiArcher()
{
    int frameSize = 128;
    SamuraiArcherAttack1 = {LoadTexture("assets/Samurai_Char/Samurai_archer/Attack_1.png"), frameSize, frameSize, 5, 24};
    SamuraiArcherAttack2 = {LoadTexture("assets/Samurai_Char/Samurai_archer/Attack_2.png"), frameSize, frameSize, 5, 24};
    SamuraiArcherAttack3 = {LoadTexture("assets/Samurai_Char/Samurai_archer/Attack_3.png"), frameSize, frameSize, 6, 26};
    SamuraiArcherDead = {LoadTexture("assets/Samurai_Char/Samurai_archer/Dead.png"), frameSize, frameSize, 3, 14};
    SamuraiArcherIdle = {LoadTexture("assets/Samurai_Char/Samurai_archer/Idle.png"), frameSize, frameSize, 9, 14};
    SamuraiArcherJump = {LoadTexture("assets/Samurai_Char/Samurai_archer/Jump.png"), frameSize, frameSize, 9, 20};
    SamuraiArcherRun = {LoadTexture("assets/Samurai_Char/Samurai_archer/Run.png"), frameSize, frameSize, 8, 24};
    SamuraiArcherWalk = {LoadTexture("assets/Samurai_Char/Samurai_archer/Walk.png"), frameSize, frameSize, 8, 14};
    SamuraiArcherShot = {LoadTexture("assets/Samurai_Char/Samurai_archer/Shot.png"), frameSize, frameSize, 15, 28};
}

void Loader::UnLoadSamuraiArcher()
{
    UnloadTexture(SamuraiArcherAttack1.spriteSheet);
    UnloadTexture(SamuraiArcherAttack2.spriteSheet);
    UnloadTexture(SamuraiArcherAttack3.spriteSheet);
    UnloadTexture(SamuraiArcherDead.spriteSheet);
    UnloadTexture(SamuraiArcherIdle.spriteSheet);
    UnloadTexture(SamuraiArcherJump.spriteSheet);
    UnloadTexture(SamuraiArcherRun.spriteSheet);
    UnloadTexture(SamuraiArcherWalk.spriteSheet);
    UnloadTexture(SamuraiArcherShot.spriteSheet);
}

void Loader::LoadSamuraiCommander()
{
    int frameSize = 128;
    SamuraiCommanderAttack1 = {LoadTexture("assets/Samurai_Char/Samurai_commander/Attack_1.png"), frameSize, frameSize, 4, 26};
    SamuraiCommanderAttack2 = {LoadTexture("assets/Samurai_Char/Samurai_commander/Attack_2.png"), frameSize, frameSize, 5, 26};
    SamuraiCommanderAttack3 = {LoadTexture("assets/Samurai_Char/Samurai_commander/Attack_3.png"), frameSize, frameSize, 4, 26};
    SamuraiCommanderDead = {LoadTexture("assets/Samurai_Char/Samurai_commander/Dead.png"), frameSize, frameSize, 6, 14};
    SamuraiCommanderHurt = {LoadTexture("assets/Samurai_Char/Samurai_commander/Hurt.png"), frameSize, frameSize, 2, 18};
    SamuraiCommanderIdle = {LoadTexture("assets/Samurai_Char/Samurai_commander/Idle.png"), frameSize, frameSize, 5, 14};
    SamuraiCommanderJump = {LoadTexture("assets/Samurai_Char/Samurai_commander/Jump.png"), frameSize, frameSize, 7, 10};
    SamuraiCommanderRun = {LoadTexture("assets/Samurai_Char/Samurai_commander/Run.png"), frameSize, frameSize, 8, 26};
    SamuraiCommanderWalk = {LoadTexture("assets/Samurai_Char/Samurai_commander/Walk.png"), frameSize, frameSize, 9, 14};
    SamuraiCommanderProtect = {LoadTexture("assets/Samurai_Char/Samurai_commander/Protection.png"), frameSize, frameSize, 2, 12};
}

void Loader::UnLoadSamuraiCommander()
{
    UnloadTexture(SamuraiCommanderAttack1.spriteSheet);
    UnloadTexture(SamuraiCommanderAttack2.spriteSheet);
    UnloadTexture(SamuraiCommanderAttack3.spriteSheet);
    UnloadTexture(SamuraiCommanderDead.spriteSheet);
    UnloadTexture(SamuraiCommanderHurt.spriteSheet);
    UnloadTexture(SamuraiCommanderIdle.spriteSheet);
    UnloadTexture(SamuraiCommanderJump.spriteSheet);
    UnloadTexture(SamuraiCommanderRun.spriteSheet);
    UnloadTexture(SamuraiCommanderWalk.spriteSheet);
    UnloadTexture(SamuraiCommanderProtect.spriteSheet);
}

void Loader::LoadBackgrounds()
{
    MainMenuBackground = LoadTexture("assets/images/menu_bg.png");
    LoadMenuBackground = LoadTexture("assets/images/loadmenu_bg.jpeg");
    SelectionMenuBackground = LoadTexture("assets/images/selection.png");
    TileSet = LoadTexture("assets/maps/map.png");
}

void Loader::UnLoadBackgrounds()
{
    UnloadTexture(MainMenuBackground);
    UnloadTexture(LoadMenuBackground);
    UnloadTexture(SelectionMenuBackground);
}

void Loader::LoadCollectables()
{
    int frameSize = 120;
    CoinAnim = {LoadTexture("assets/images/coin_anim.png"), frameSize, frameSize, 8, 10};
    Coin = LoadTexture("assets/images/coin.png");
}

void Loader::UnLoadCollectables()
{
    UnloadTexture(CoinAnim.spriteSheet);
    UnloadTexture(Coin);
}

void Loader::LoadSpecialItems()
{
    Torch = {LoadTexture("assets/maps/torch.png"), 32, 64, 4, 30};
    Arrow = LoadTexture("assets/images/Arrow.png");
}

void Loader::UnLoadSpecialItems()
{
    UnloadTexture(Arrow);
    UnloadTexture(Torch.spriteSheet);
}

void Loader::LoadFont()
{
    TitleFont = LoadFontEx("assets/fonts/StarCrush.otf", 64, nullptr, 0);
}

void Loader::UnLoadFont()
{
    UnloadFont(TitleFont);
}

void Loader::LoadPotraitCards()
{
    Knight1Potrait = LoadTexture("assets/images/Potraits/Knight1.png");
    Knight2Potrait = LoadTexture("assets/images/Potraits/Knight2.png");
    Knight3Potrait = LoadTexture("assets/images/Potraits/Knight3.png");
    SamuraiPotrait = LoadTexture("assets/images/Potraits/Samurai.png");
    SamuraiArcherPotrait = LoadTexture("assets/images/Potraits/SamuraiArcher.png");
    SamuraiCommanderPotrait = LoadTexture("assets/images/Potraits/SamuraiCommander.png");
}

void Loader::UnLoadPotraitCards()
{
    UnloadTexture(Knight1Potrait);
    UnloadTexture(Knight2Potrait);
    UnloadTexture(Knight3Potrait);
    UnloadTexture(SamuraiPotrait);
    UnloadTexture(SamuraiArcherPotrait);
    UnloadTexture(SamuraiCommanderPotrait);
}

void Loader::LoadHUDPotraits()
{
    Knight1HUD = LoadTexture("assets/images/HUD/Knight1HUD.png");
    Knight2HUD = LoadTexture("assets/images/HUD/Knight2HUD.png");
    Knight3HUD = LoadTexture("assets/images/HUD/Knight3HUD.png");
    SamuraiHUD = LoadTexture("assets/images/HUD/SamuraiHUD.png");
    SamuraiArcherHUD = LoadTexture("assets/images/HUD/SamuraiArcherHUD.png");
    SamuraiCommanderHUD = LoadTexture("assets/images/HUD/SamuraiCommanderHUD.png");
}

void Loader::UnLoadHUDPotraits()
{
    UnloadTexture(Knight1HUD);
    UnloadTexture(Knight2HUD);
    UnloadTexture(Knight3HUD);
    UnloadTexture(SamuraiHUD);
    UnloadTexture(SamuraiArcherHUD);
    UnloadTexture(SamuraiCommanderHUD);
}

void Loader::UnloadAssets()
{
    UnLoadSkeletonSpearman();
    UnLoadSkeletonArcher();
    UnLoadSkeletonWarrior();

    UnLoadKnight1();
    UnLoadKnight2();
    UnLoadKnight3();

    UnLoadSamurai();
    UnLoadSamuraiArcher();
    UnLoadSamuraiCommander();

    UnLoadKarasuTengu();
    UnLoadYamabushiTengu();

    UnLoadBackgrounds();
    UnLoadFont();
    UnLoadHUDPotraits();
    UnLoadCollectables();
    UnLoadPotraitCards();
    UnLoadSpecialItems();
}