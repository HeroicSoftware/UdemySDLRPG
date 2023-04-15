#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Animation
{
private:
    int currentFrameWidth, currentFrameHeight;

    SDL_Texture *spriteSheet;
    SDL_Renderer *renderer;
    SDL_Texture *LoadTexture(const char *filename, SDL_Renderer *renderer);

public:
    int numberOfFrames;
    float frameDuration;
    Animation();
    ~Animation();
    float GetFrameDuration();
    int GetNumberOfFrames();
    void SetupAnimation(std::string spriteSheetFile, SDL_Renderer *renderer, int numberOfFrames, float frameDuration);
    void Draw(int frame, int positionX, int positionY);
};
