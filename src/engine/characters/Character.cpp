#include "Character.h"

bool Character::IsAnimationLocked() const
{
    return isAnimationLocked;
}

void Character::OnAnimationComplete()
{
    isAnimationLocked = false;
    ChangeAnimState(AnimState::IDLE);
}

Character::Character()
{
    Pos.x = 100;
    Pos.y = 500;
    hp = 100;
    // Start on ground by default so player can jump immediately
    isGrounded = true;
    // Ensure velocities are initialized to zero
    velocityX = 0.0f;
    velocityY = 0.0f;
    // Default animation state
    animState = AnimState::IDLE;

    // Set a reasonable default hitbox relative offsets for 128x128 sprites
    hitboxW = 64.0f;
    hitboxH = 92.0f;
    hitboxOffsetX = 32.0f;
    hitboxOffsetY = 32.0f; // default offset for sprites (move hitbox down by 32px)
}

// optional helper to change offset at runtime
// (we already expose Set/Change via Character.h; no additional logic required here)

void Character::ApplyPhysics(float dt)
{
    // Only apply gravity if not grounded
    if (!isGrounded)
    {
        velocityY += gravity * dt;
    }
    else
    {
        // Keep grounded velocity at zero to prevent wobble
        velocityY = 0.0f;
    }

    Pos.x += velocityX * dt;
    Pos.y += velocityY * dt;

    // Grounded detection is handled by tile collisions in GameManager; avoid snapping to a fixed Y so tiles control landing
}

void Character::ChangeAnimState(AnimState newState)
{
    // Don't allow changes if locked
    if (isAnimationLocked && animState != newState)
        return;

    animState = newState;

    // Lock animations that shouldn't be interrupted
    if (newState == AnimState::ATTACK1 ||
        newState == AnimState::ATTACK2 ||
        newState == AnimState::ATTACK3 ||
        newState == AnimState::SHOT1 ||
        newState == AnimState::SHOT2 ||
        newState == AnimState::RUN_ATTACK ||
        /* Exclude JUMP from lock so physics/controls keep updating while in-air */
        newState == AnimState::HURT ||
        newState == AnimState::DEAD)
    {
        isAnimationLocked = true;
    }
}
