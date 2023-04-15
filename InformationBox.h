#pragma once
#include "InformationBox.h"
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#define RENDER_LOGIC_WIDTH 320
#define RENDER_LOGIC_HEIGHT 240
#define PADDING_WIDTH 4
#define PADDING_HEIGHT 4
class InformationBox
{
public:
    SDL_Renderer *renderer;
    TTF_Font *font;
    std::string displayText;
    SDL_Texture *textTexture = NULL;
    SDL_Rect textRectangle;
    SDL_Rect displayBoxRectangle;
    bool isVisible = true;
    void Setup(SDL_Renderer *renderer);
    void SetText(std::string text);
    void Draw();

    InformationBox();
    ~InformationBox();

private:
    int fontSize;
    SDL_Color displayTextColor;
};
