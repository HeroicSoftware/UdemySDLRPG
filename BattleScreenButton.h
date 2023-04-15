
#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class BattleScreenButton
{
private:
    int fontSize;
    TTF_Font *font;
    SDL_Color battleScreenButtonColor;
    const int PIXELFORMATTINGBUFFER = 2;

public:
    SDL_Rect buttonRect;
    SDL_Rect textRect;
    SDL_Renderer *renderer;
    SDL_Texture *textTexture;
    bool isSelected;
    void Initialize(SDL_Renderer *renderer, SDL_Rect buttonRect, std::string textForButton);
    void Draw();
    void DrawInactive();
    ~BattleScreenButton();
};
