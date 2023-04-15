#include "BattleVisualEffects.h"

void BattleVisualEffects::Initialize(SDL_Renderer *renderer, int x, int y)
{
    this->renderer = renderer;
    this->x = x;
    this->y = y;
    this->animationHit.SetupAnimation("assets/effectHit.png", renderer, EFFECT_NUMBER_OF_FRAMES, EFFECT_ANIMATION_DURATION);
    this->animationHeal.SetupAnimation("assets/effectHeal.png", renderer, EFFECT_NUMBER_OF_FRAMES, EFFECT_ANIMATION_DURATION);
    this->animationExplode.SetupAnimation("assets/effectExplode.png", renderer, EFFECT_NUMBER_OF_FRAMES, EFFECT_ANIMATION_DURATION);
    this->animationAttackBoost.SetupAnimation("assets/effectAttackBoost.png", renderer, EFFECT_NUMBER_OF_FRAMES, EFFECT_ANIMATION_DURATION);
    this->animationDefenseBoost.SetupAnimation("assets/effectDefenseBoost.png", renderer, EFFECT_NUMBER_OF_FRAMES, EFFECT_ANIMATION_DURATION);
}

void BattleVisualEffects::SetEffectPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

void BattleVisualEffects::PlayHit()
{
    this->animationManager.ChangeAnimation(&animationHit);
    this->animationManager.SetIsAnimationLooping(false);
    this->hasBattleVisualEffectPlayed = true;
}

void BattleVisualEffects::PlayHeal()
{
    this->animationManager.ChangeAnimation(&animationHeal);
    this->animationManager.SetIsAnimationLooping(false);
    this->hasBattleVisualEffectPlayed = true;
}

void BattleVisualEffects::PlayDeath()
{
    this->animationManager.ChangeAnimation(&animationExplode);
    this->animationManager.SetIsAnimationLooping(false);
    this->hasBattleVisualEffectPlayed = true;
}

void BattleVisualEffects::PlayAttackBoost()
{
    this->animationManager.ChangeAnimation(&animationAttackBoost);
    this->animationManager.SetIsAnimationLooping(false);
    this->hasBattleVisualEffectPlayed = true;
}

void BattleVisualEffects::PlayDefenseBoost()
{
    this->animationManager.ChangeAnimation(&animationDefenseBoost);
    this->animationManager.SetIsAnimationLooping(false);
    this->hasBattleVisualEffectPlayed = true;
}
void BattleVisualEffects::Update(float deltaTime)
{
    if (hasBattleVisualEffectPlayed == true)
    {
        animationManager.UpdateAnimation(deltaTime);
        if (animationManager.hasAnimationEnded == true)
        {
            hasBattleVisualEffectPlayed = false;
        }
    }
}
void BattleVisualEffects::Draw()
{
    if (hasBattleVisualEffectPlayed == true)
    {
        animationManager.DrawAnimation(x, y);
    }
}