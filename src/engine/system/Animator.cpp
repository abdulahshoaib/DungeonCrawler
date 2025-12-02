#include "Animator.h"

Animator::Animator()
{
}

Animator::~Animator()
{
}

void Animator::Update(Character *c, float delta)
{
    Animation *anim = c->currentAnim;
    if (!anim)
        return;

    // Reset frame when animation changes
    if (c->previousAnim != anim)
    {
        anim->currentFrame = 0;
        anim->frameTimer = 0.0f;
        c->previousAnim = anim;
    }

    anim->frameTimer += delta;
    float frameTime = 1.0f / anim->fps;

    if (anim->frameTimer >= frameTime)
    {
        anim->frameTimer -= frameTime;
        int prevFrame = anim->currentFrame;
        anim->currentFrame++;

        // Check for attack hit trigger: call OnAttackHit() once when
        // animation reaches its midpoint for attack animations.
        int hitFrame = anim->frameCount / 2;
        bool isAttackState = (c->animState == AnimState::ATTACK1 || c->animState == AnimState::ATTACK2 ||
                              c->animState == AnimState::ATTACK3 || c->animState == AnimState::RUN_ATTACK);

        if (isAttackState && prevFrame < hitFrame && anim->currentFrame >= hitFrame)
        {
            // Mark the character as having triggered an attack this cycle.
            c->attackTriggered = true;
            c->OnAttackHit();
        }

        // Check if animation completed
        if (anim->currentFrame >= anim->frameCount)
        {
            // If this is the character's death animation, clamp to last frame
            // so it stays on the final pose instead of looping.
            if (c->GetDeadAnim() == anim)
            {
                anim->currentFrame = anim->frameCount - 1;
            }
            else
            {
                // Looping/default behaviour: wrap to first frame
                anim->currentFrame = 0;
            }

            // Unlock character when non-looping/locked animations complete
            if (c->IsAnimationLocked())
            {
                c->OnAnimationComplete();
            }
        }
    }
}

void Animator::Draw(Character *c)
{
    Animation *anim = c->currentAnim;
    if (!anim)
        DrawText("CURRENT ANIM NULL!", 50, 50, 20, RED);

    Rectangle src = {
        (float)(anim->currentFrame * anim->frameWidth),
        0,
        (float)anim->frameWidth,
        (float)anim->frameHeight};

    // Flip sprite based on facing direction
    if (c->IsFacingLeft())
    {
        src.width = -src.width;
    }

    Rectangle dest = {
        c->Pos.x,
        c->Pos.y,
        (float)anim->frameWidth,
        (float)anim->frameHeight};

    DrawTexturePro(anim->spriteSheet, src, dest, {0, 0}, 0.0f, WHITE);
}