#include "AnimationManager.h"

AnimationManager::AnimationManager()
{
    currentAnimation = NULL;
    currentFrame = 0;
    timer = 0;
    hasAnimationEnded = false;
    isAnimationLooping = true;
}

void AnimationManager::ChangeAnimation(Animation *newAnimation)
{
    currentAnimation = newAnimation;
    ResetAnimation();
}

void AnimationManager::SetIsAnimationLooping(bool loopAnimation)
{
    isAnimationLooping = loopAnimation;
}

void AnimationManager::ResetAnimation()
{
    currentFrame = 0;
    timer = 0;
    hasAnimationEnded = false;
}

void AnimationManager::UpdateAnimation(float deltaTime)
{
    if (currentAnimation != NULL)
    {
        // Update timer
        timer += deltaTime;

        // Check if frame has been show its whole duration
        if (timer >= currentAnimation->frameDuration)
        {
            // Move to next frame
            currentFrame++;
            // Reset timer
            timer = 0;

            // Check spriteSheet number of frames
            if (currentFrame >= currentAnimation->numberOfFrames)
            {
                if (isAnimationLooping == true)
                {
                    // Loop back to first frame
                    currentFrame = 0;
                }
                else
                {
                    // Finish animation
                    hasAnimationEnded = true;
                    // Make currentFrame equal to last frame
                    currentFrame = currentAnimation->numberOfFrames - 1;
                }
            }
        }
    }
}

void AnimationManager::DrawAnimation(int x, int y)
{
    if (currentAnimation != NULL)
    {
        currentAnimation->Draw(currentFrame, x, y);
    }
}
