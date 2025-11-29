#pragma once

#include "AnimStates.h"
#include <raylib.h>
#include "Animation.h"

class Character
{
protected:
    Animation *idle1Anim = nullptr;
    Animation *idle2Anim = nullptr;

    Animation *runAnim = nullptr;
    Animation *walkAnim = nullptr;

    Animation *jumpAnim = nullptr;
    Animation *fallAnim = nullptr;

    Animation *attack1Anim = nullptr;
    Animation *attack2Anim = nullptr;
    Animation *attack3Anim = nullptr;

    Animation *runAttackAnim = nullptr;

    Animation *defendAnim = nullptr;
    Animation *hurtAnim = nullptr;
    Animation *deadAnim = nullptr;
    Animation *protectAnim = nullptr;

    Animation *shot1Anim = nullptr;
    Animation *shot2Anim = nullptr;

    Animation *arrowAnim = nullptr;

    Animation *chargeAnim = nullptr;
    Animation *evasionAnim = nullptr;

    Animation *fire1Anim = nullptr;
    Animation *fire2Anim = nullptr;

    Animation *currentAnim = nullptr;

    AnimState animState;

public:
    Character();

    // subject to change in each derived class
    float hp;
    float damage;
    float speed;

    virtual void anim() = 0;
    void ChangeAnimState(AnimState);
};