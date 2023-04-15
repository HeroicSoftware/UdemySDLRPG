#include "HitpointsBar.h"
void HitpointsBar::DrawBlackBoarder()
{
    SDL_Rect borderRect = {xPosition, yPosition, BORDERWIDTH, BORDERHEIGHT};
    // Select color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // Draw the border on screen
    SDL_RenderDrawRect(renderer, &borderRect);
}
void HitpointsBar::DrawWhiteInnerBox()
{
    SDL_Rect innerBoxRect = {xPosition, yPosition, BORDERWIDTH, BORDERHEIGHT};
    // Select color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &innerBoxRect);
}
void HitpointsBar::DrawRedCurrentHP()
{
    float currentHPFloat = currentHitPoints;
    int currentHPBarWidth = (currentHPFloat / maxHitPoints) * FULLHEALTHBARWIDTH;
    if (currentHPBarWidth <= 0)
    {
        currentHPBarWidth = 0;
    }
    // Draw the recentagle as a percentage
    SDL_Rect currentHPRect = { xPosition + 1, yPosition + 1, currentHPBarWidth, BORDERHEIGHT -2 };
    SDL_SetRenderDrawColor(renderer, 217, 43, 90, 255);
    SDL_RenderFillRect(renderer, &currentHPRect);
}
void HitpointsBar::SetCurrentHP(int HP)
{
    this->currentHitPoints = HP;
}
void HitpointsBar::SetMaxHP(int maxHP)
{
    this->maxHitPoints = maxHP;
}
HitpointsBar::HitpointsBar()
{
    // Default HP to 100
    currentHitPoints = maxHitPoints = DEFAULT_HP;
}
void HitpointsBar::Initialize(SDL_Renderer *renderer, int x, int y)
{
    this->renderer = renderer;
    this->xPosition = x;
    this->yPosition = y;
}
void HitpointsBar::Draw()
{
    // Draw white InnerBox
    DrawWhiteInnerBox();
    // Draw black border
    DrawBlackBoarder();
    // Draw Red CurrentHP
    DrawRedCurrentHP();
}
