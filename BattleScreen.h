#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <list>
#include "Hero.h"
#include "Klog.h"
#include "Sham.h"
#include "CharacterAnimationSet.h"
#include "CharacterType.h"
#include "Character.h"
#include "HitpointsBar.h"
#include "BattleScreenButton.h"
#include "BattleVisualEffects.h"
class BattleScreen
{
private:
    BattleVisualEffects enemyBattleVisualEffect;
    BattleVisualEffects playerBattleVisualEffect;
    BattleScreenButton fightButton;
    BattleScreenButton itemButton;
    bool isBattleFinished;
    bool isExitProgram;
    bool isHeroesTurn;
    Character *enemy;
    CharacterAnimationSet enemyAnimationSet;
    CharacterAnimationSet heroAnimationSet;
    Hero *player;
    HitpointsBar enemyHPBar;
    HitpointsBar heroHPBar;
    int *items;
    int const ENEMYHPXPOSITION = 190;
    int const ENEMYHPYPOSITION = 10;
    int const HEROHPXPOSITION = 90;
    int const HEROHPYPOSITION = 194;
    int const playerNameRectangleX = 90;
    int const playerNameRectangleY = 181;
    int enemyDamage = 0;
    int fontSize;
    int playerDamage = 0;
    SDL_Color playerNameTextColor;
    SDL_Rect bottomUIBar;
    SDL_Rect fightButtonRect;
    SDL_Rect itemButtonRect;
    SDL_Rect playerNameRectangle;
    SDL_Renderer *renderer;
    SDL_Texture *backgroundTexture;
    SDL_Texture *playerNameTexture;
    TTF_Font *font;
    void HandleBattleScreenPlayerOptionSelection(SDL_Event playerInput);
    void UpdateCharacters(Character *enemy, Hero *player);
    void DetermineBattleOrder();

public:
    BattleScreen(SDL_Renderer *renderer, Hero *hero, int *currentInventory, CharacterType enemyType);
    ~BattleScreen();
    SDL_Texture *LoadTexture(const char *filename, SDL_Renderer *renderer);
    void Draw();
    void Update();
    void CreateUIBar();
    void CreatePlayerNameTextTexture();
    bool GetIsExitProgram();
    bool GetIsBattleFinished();
    bool IsAnimationsPlaying();
};
