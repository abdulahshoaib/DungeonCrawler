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

private:
    bool facingLeft = false; // ADD THIS - tracks which direction character is facing

public:
    Vector2 Pos;
    AnimState animState;

    bool isAnimationLocked = false;

    Animation *currentAnim = nullptr;
    Animation *previousAnim = nullptr;

    bool IsAnimationLocked() const;
    void OnAnimationComplete();

    Character();

    float hp;
    float damage;
    float speed = 200.0f;

    // ===== MOVEMENT =====
    float velocityX = 0.0f;
    float velocityY = 0.0f;

    float gravity = 1200.0f;
    float jumpForce = -500.0f;

    bool isGrounded = false;

    // hitbox (relative to sprite top-left)
    float hitboxW = 64.0f;
    float hitboxH = 96.0f;
    float hitboxOffsetX = 32.0f;
    float hitboxOffsetY = 32.0f;

    Rectangle GetHitboxRect() const
    {
        return Rectangle{Pos.x + hitboxOffsetX, Pos.y + hitboxOffsetY, hitboxW, hitboxH};
    }

    void SetHitboxOffsetY(float y) { hitboxOffsetY = y; }
    void ChangeHitboxOffsetY(float dy) { hitboxOffsetY += dy; }
    float GetHitboxOffsetY() const { return hitboxOffsetY; }

    // ADD THESE TWO METHODS:
    void SetFacingLeft(bool left) { facingLeft = left; }
    bool IsFacingLeft() const { return facingLeft; }

    virtual void anim() = 0;
    void ApplyPhysics(float);
    void ChangeAnimState(AnimState);
};