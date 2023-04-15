#pragma once
#include "AnimationManager.h"
class BattleVisualEffects
{
public:
    Animation animationAttackBoost;
    Animation animationDefenseBoost;
    Animation animationExplode;
    Animation animationHeal;
    Animation animationHit;
    AnimationManager animationManager;
    float EFFECT_ANIMATION_DURATION = 0.083f;
    int EFFECT_NUMBER_OF_FRAMES = 4;
    int x;
    int y;
    SDL_Renderer *renderer;
    // Set true while effect on screen
    bool hasBattleVisualEffectPlayed;
    void Initialize(SDL_Renderer *renderer, int x, int y);
    void SetEffectPosition(int x, int y);
    void PlayHit();
    void PlayHeal();
    void PlayDeath();
    void Draw();
    void PlayAttackBoost();
    void PlayDefenseBoost();
    void Update(float deltaTime);
};
