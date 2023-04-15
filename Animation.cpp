#include "Animation.h"

SDL_Texture *Animation::LoadTexture(const char *filename, SDL_Renderer *renderer)
{
    SDL_Texture *texture;
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
    texture = IMG_LoadTexture(renderer, filename);
    return texture;
}

Animation::Animation()
{
}

Animation::~Animation()
{
    if (spriteSheet != NULL)
    {
        SDL_DestroyTexture(spriteSheet);
    }
}

float Animation::GetFrameDuration()
{
    return this->frameDuration;
}

int Animation::GetNumberOfFrames()
{
    return this->numberOfFrames;
}

void Animation::SetupAnimation(std::string spriteSheetFile, SDL_Renderer *renderer, int numberOfFrames, float frameDuration)
{
    this->renderer = renderer;
    this->spriteSheet = LoadTexture(spriteSheetFile.c_str(), this->renderer);
    int width = 0;
    int height = 0;
    SDL_QueryTexture(spriteSheet, NULL, NULL, &width, &height);
    // Calculate Frame Width and Height
    currentFrameHeight = height;
    currentFrameWidth = width / numberOfFrames;
    this->numberOfFrames = numberOfFrames;
    this->frameDuration = frameDuration;
}
void Animation::Draw(int frame, int positionX, int positionY)
{
    // clip of the sprite
    SDL_Rect currentFrameClip;
    currentFrameClip.x = frame * currentFrameWidth;
    currentFrameClip.y = 0;
    currentFrameClip.w = currentFrameWidth;
    currentFrameClip.h = currentFrameHeight;
    // Where to draw the sprite
    SDL_Rect currentFrameDestinationRect = {positionX, positionY, currentFrameWidth, currentFrameHeight};
    // Draw the sprite
    SDL_RenderCopy(renderer, spriteSheet, &currentFrameClip, &currentFrameDestinationRect);
}
