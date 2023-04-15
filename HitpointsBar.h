#pragma once
#include <SDL.h>
class HitpointsBar
{
private:
    const int DEFAULT_HP = 100;
    const int BORDERWIDTH = 102;
    const int BORDERHEIGHT = 12;
    const int FULLHEALTHBARWIDTH = 100;
    void DrawBlackBoarder();
    void DrawWhiteInnerBox();
    void DrawRedCurrentHP();

public:
    int xPosition, yPosition, currentHitPoints, maxHitPoints;
    SDL_Renderer *renderer;
    void SetCurrentHP(int HP);
    void SetMaxHP(int maxHP);

    HitpointsBar();
    void Initialize(SDL_Renderer *renderer, int x, int y);
    void Draw(); 
};
