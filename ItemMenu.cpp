#include "ItemMenu.h"

SDL_Texture *ItemMenu::GenerateTextTexture(TTF_Font *font, SDL_Color color, std::string textToPrint)
{
    // Create Surface
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, textToPrint.c_str(), color);
    ;
    // Convert from Surface to Textre
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    // Delete the surface
    SDL_FreeSurface(textSurface);
    return textTexture;
}

void ItemMenu::Initialize(SDL_Renderer *renderer, int *items, int x, int y)
{
    this->renderer = renderer;
    this->xPosition = x;
    this->yPosition = y;
    this->itemsArray = items;
    int fontSize = 8;
    SDL_Color fontColor = {0, 0, 0, 0};
    TTF_Font *fontTypeFace = TTF_OpenFont("assets/PublicPixel.ttf", fontSize);
    noItem = GenerateTextTexture(fontTypeFace, fontColor, "---");
    damageItem = GenerateTextTexture(fontTypeFace, fontColor, "Taser");
    attackBoostItem = GenerateTextTexture(fontTypeFace, fontColor, "Brawny Hippo Gummy");
    defenseBoostItem = GenerateTextTexture(fontTypeFace, fontColor, "Rygar Guard keychain");
    cancelItem = GenerateTextTexture(fontTypeFace, fontColor, "Cancel");
    TTF_CloseFont(fontTypeFace);
}

void ItemMenu::MoveSelectionUp()
{
    selectedItemIndex--;
    if (selectedItemIndex < 0)
    {
        selectedItemIndex = 0;
    }
}

void ItemMenu::MoveSelectionDown()
{
    selectedItemIndex++;
    if (selectedItemIndex > 10)
    {
        selectedItemIndex = 0;
    }
}

void ItemMenu::Draw()
{
    if (isVisible == false)
    {
        return;
    }
    SDL_Rect itemButton = {xPosition, yPosition, 100, 200};
    for (int i = 0; i < 10; i++)
    {
        // Place each button underneath previous button
        itemButton.y = itemButton.y + (i * itemButton.h);
        if (selectedItemIndex == i)
        {
            SDL_SetRenderDrawColor(renderer, 200, 40, 90, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        SDL_RenderFillRect(renderer, &itemButton);

        SDL_Texture *tempTexture = noItem;
        if (itemsArray[i] == 1)
        {
            tempTexture = healthBoostItem;
        }
        else if (itemsArray[i] == 2)
        {
            tempTexture = damageItem;
        }
        else if (itemsArray[i] == 3)
        {
            tempTexture = attackBoostItem;
        }
        else if (itemsArray[i] == 4)
        {
            tempTexture = defenseBoostItem;
        }
    }
}
ItemMenu::~ItemMenu()
{
    SDL_DestroyTexture(noItem);
    SDL_DestroyTexture(attackBoostItem);
    SDL_DestroyTexture(defenseBoostItem);
    SDL_DestroyTexture(healthBoostItem);
    SDL_DestroyTexture(cancelItem);
}
