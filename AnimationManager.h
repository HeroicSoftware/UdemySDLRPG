#pragma once
#include "Animation.h"
class AnimationManager
{
public:
  Animation *currentAnimation;
  int currentFrame; // Current frame (Index 0 is first frame)
  float timer;      // How long has the current frame been on screen
  bool hasAnimationEnded;
  bool isAnimationLooping; // True for keep animation, false to stop loop
  AnimationManager();
  void ChangeAnimation(Animation *newAnimation);
  void SetIsAnimationLooping(bool loopAnimation);
  void ResetAnimation();
  void UpdateAnimation(float deltaTime);
  void DrawAnimation(int x, int y);
};
