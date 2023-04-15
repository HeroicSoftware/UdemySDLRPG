#pragma once
#include "AnimationManager.h"
#include "CharacterType.h"
class CharacterAnimationSet
{
private:
    // Hero
    float heroHitFrameDuration = 0.1f;
    float heroIdleFrameDuration = 1.0f;
    float heroPunchFrameDuration = 0.1f;
    // klog
    float klobHitFrameDuration = 0.1f;
    float klobIdleFrameDuration = 1.0f;
    float klobBiteFrameDuration = 0.1f;
    // Sham
    float shamHitFrameDuration = 0.1f;
    float shamIdleFrameDuration = 1.0f;
    float shamAttackFrameDuration = 0.1f;
    // Hero
    int heroHitNumberOfFrames = 2;
    int heroIdleNumberOfFrames = 1;
    int heroPunchNumberOfFrames = 3;
    // klog
    int klobHitNumberOfFrames = 2;
    int klobIdleNumberOfFrames = 1;
    int klobBiteNumberOfFrames = 3;
    // Sham
    int shamHitNumberOfFrames = 2;
    int shamIdleNumberOfFrames = 1;
    int shamAttackNumberOfFrames = 4;

public:
    int x, y;
    SDL_Renderer *renderer;
    Animation idleAnimation, attackAnimation, hitAnimation;
    AnimationManager animationManager;
    bool hasAnimationBeenPlayed;
    void Setup(SDL_Renderer *renderer, int x, int y, CharacterType type);
    void PlayIdle();
    void PlayAttack();
    void PlayHit();
    void Update(float deltaTime);
    void Draw();
};
