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
        anim->currentFrame++;
        
        // Check if animation completed
        if (anim->currentFrame >= anim->frameCount)
        {
            anim->currentFrame = 0;
            
            // Unlock character when non-looping animations complete
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