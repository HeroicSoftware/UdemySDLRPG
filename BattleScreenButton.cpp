#include "BattleScreenButton.h"
void BattleScreenButton::Initialize(SDL_Renderer *renderer, SDL_Rect buttonRect, std::string textForButton)
{
    this->renderer = renderer;
    this->buttonRect = buttonRect;
    // Setup font to be drawn
    fontSize = 8;
    this->battleScreenButtonColor = {0, 0, 0, 0};
    font = TTF_OpenFont("assets/PublicPixel.ttf", fontSize);
    SDL_Surface *battleScreenButtonTextSurface = TTF_RenderText_Blended(font, textForButton.c_str(), battleScreenButtonColor);
    textTexture = SDL_CreateTextureFromSurface(renderer, battleScreenButtonTextSurface);
    SDL_FreeSurface(battleScreenButtonTextSurface);
    TTF_CloseFont(font);
    textRect.x = buttonRect.x + PIXELFORMATTINGBUFFER;
    textRect.y = buttonRect.y + PIXELFORMATTINGBUFFER;
    SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
    isSelected = false;
}
void BattleScreenButton::Draw()
{
    // Use Different color button if selected
    if (isSelected == true)
    {
        SDL_SetRenderDrawColor(renderer, 217, 43, 90, 255);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }
    // Render Button Background
    SDL_RenderFillRect(renderer, &buttonRect);
    // Render border
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &buttonRect);
    // Render text to screen
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
}
void BattleScreenButton::DrawInactive()
{
    SDL_SetRenderDrawColor(renderer, 217, 43, 90, 255);
    // Render Button Background
    SDL_RenderFillRect(renderer, &buttonRect);
    // Render border
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &buttonRect);
    // Render text to screen
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
}
BattleScreenButton::~BattleScreenButton()
{
    if (textTexture != NULL)
    {
        SDL_DestroyTexture(textTexture);
    }
}
