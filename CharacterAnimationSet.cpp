#include "CharacterAnimationSet.h"

void CharacterAnimationSet::Setup(SDL_Renderer *renderer, int x, int y, CharacterType type)
{
    this->renderer = renderer;
    this->x = x;
    this->y = y;
    if (type == HeroType)
    {
        // Load Hero Animation
        idleAnimation.SetupAnimation("assets/heroIdle.png", renderer, heroIdleNumberOfFrames, heroIdleFrameDuration);
        attackAnimation.SetupAnimation("assets/heroPunch.png", renderer, heroPunchNumberOfFrames, heroPunchFrameDuration);
        hitAnimation.SetupAnimation("assets/heroHit.png", renderer, heroHitNumberOfFrames, heroHitFrameDuration);
    }
    else if (type == KlogType)
    {
        // Load Hero Animation
        idleAnimation.SetupAnimation("assets/klobIdle.png", renderer, klobIdleNumberOfFrames, klobIdleFrameDuration);
        attackAnimation.SetupAnimation("assets/klobBite.png", renderer, klobBiteNumberOfFrames, klobBiteFrameDuration);
        hitAnimation.SetupAnimation("assets/klobHit.png", renderer, klobHitNumberOfFrames, klobHitFrameDuration);
    }
    else if (type == ShamType)
    {
        // Load Hero Animation
        idleAnimation.SetupAnimation("assets/shamIdle.png", renderer, shamIdleNumberOfFrames, shamIdleFrameDuration);
        attackAnimation.SetupAnimation("assets/shamAttack.png", renderer, shamAttackNumberOfFrames, shamAttackFrameDuration);
        hitAnimation.SetupAnimation("assets/shamHit.png", renderer, shamHitNumberOfFrames, shamHitFrameDuration);
    }
    PlayIdle();
}
void CharacterAnimationSet::PlayIdle()
{
    animationManager.ChangeAnimation(&idleAnimation);
    animationManager.SetIsAnimationLooping(true);
    hasAnimationBeenPlayed = false;
}
void CharacterAnimationSet::PlayAttack()
{
    animationManager.ChangeAnimation(&attackAnimation);
    animationManager.SetIsAnimationLooping(false);
    hasAnimationBeenPlayed = true;
}
void CharacterAnimationSet::PlayHit()
{
    animationManager.ChangeAnimation(&hitAnimation);
    animationManager.SetIsAnimationLooping(false);
    hasAnimationBeenPlayed = true;
}
void CharacterAnimationSet::Update(float deltaTime)
{
    animationManager.UpdateAnimation(deltaTime);
    // If running action animation and that animation is finished
    if (animationManager.hasAnimationEnded && hasAnimationBeenPlayed)
    {
        PlayIdle();
    }
}
void CharacterAnimationSet::Draw()
{
    animationManager.DrawAnimation(x, y);
}
