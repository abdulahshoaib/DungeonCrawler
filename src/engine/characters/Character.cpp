#include "Character.h"

bool Character::IsAnimationLocked() const
{
    return isAnimationLocked;
}

void Character::OnAnimationComplete()
{
    // If death animation finished while death was pending, mark it so
    // the game manager can show the DeathState (don't transition to IDLE).
    if (animState == AnimState::DEAD && deathPending)
    {
        isAnimationLocked = false;
        deathAnimationFinished = true;
        // leave animState as DEAD and don't switch to IDLE
        return;
    }

    isAnimationLocked = false;
    ChangeAnimState(AnimState::IDLE);
}

Character::Character()
{
    Pos.x = 100;
    Pos.y = 500;
    hp = 100;
    maxHp = hp;
    // Start on ground by default so player can jump immediately
    isGrounded = true;
    // Ensure velocities are initialized to zero
    velocityX = 0.0f;
    velocityY = 0.0f;
    // Default animation state
    animState = AnimState::IDLE;

    // Set a reasonable default hitbox relative offsets for 128x128 sprites
    // Reduced default hitbox size for tighter collisions
    hitboxW = 48.0f;
    hitboxH = 64.0f; // lowered height
    hitboxOffsetX = 32.0f;
    hitboxOffsetY = 48.0f; // move hitbox further down to keep feet alignment
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

void Character::ForceChangeAnimState(AnimState newState)
{
    // Force the animation state regardless of lock (for interrupts like HURT/DEAD)
    animState = newState;

    // Lock animations that shouldn't be interrupted
    if (newState == AnimState::ATTACK1 ||
        newState == AnimState::ATTACK2 ||
        newState == AnimState::ATTACK3 ||
        newState == AnimState::SHOT1 ||
        newState == AnimState::SHOT2 ||
        newState == AnimState::RUN_ATTACK ||
        newState == AnimState::HURT ||
        newState == AnimState::DEAD)
    {
        isAnimationLocked = true;
    }
    else
    {
        isAnimationLocked = false;
    }

    // Reset previousAnim so Animator will reinitialize frame timers on next Update
    previousAnim = nullptr;
}
