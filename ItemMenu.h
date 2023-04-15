#pragma once
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
class ItemMenu
{
private:
    SDL_Texture *GenerateTextTexture(TTF_Font *font, SDL_Color color, std::string textToPrint);
    int xPosition;
    int yPosition;
    int selectedItemIndex;
    int *itemsArray;
    bool isVisible = false;

public:
    SDL_Renderer *renderer;
    SDL_Texture *noItem, *damageItem, *attackBoostItem, *defenseBoostItem, *healthBoostItem, *cancelItem;
    void Initialize(SDL_Renderer *renderer, int *items, int x, int y);
    void MoveSelectionUp();
    void MoveSelectionDown();
    void Draw();
    ~ItemMenu();
};
