#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Hero.h"
#include <fstream>
#include "MapObject.h"
#include <list>
#include "InformationBox.h"
#include <stdlib.h>
#include <time.h>
#include "BattleScreen.h"
enum INVENTORY_ITEMS
{
    NO_ITEM,
    RESTORE_HP,
    DAMAGE_ITEM,
    ATTACK_UP,
    DEFENSE_UP,
    AGILITY_UP
};

class MapScreen
{
public:
    ~MapScreen();
    MapScreen(SDL_Renderer *renderer, Hero *hero, int *playerInventory);
    Hero *hero; // Reference to hero in main.cpp
    int *playerInventory;
    int dungeonMap[10][10]; // 2D Array Representing game map 0 = wall, 1 = walkable
    list<MapObject> mapObjects;
    MapObject doorObject;
    MapObject heroObject;
    BattleScreen battleScreen();
    InformationBox informationBox;
    bool isExitProgram = false;
    bool isEscapeAvailable = false;
    bool isEscaped = false;
    // Textures for Map Tiles
    SDL_Texture *heroTileTexture;
    SDL_Texture *doorTileTexture;
    SDL_Texture *klobTileTexture;
    SDL_Texture *chestTileTexture;
    SDL_Renderer *renderer;
    void DrawToScreen();
    void Update();
    void ItemFound();

private:
    const int tileHeight = 32;
    const int tileWidth = 32;
    void LoadTextures();
    SDL_Texture *LoadTexture(const char *filename, SDL_Renderer *renderer);
    void DrawMapObjects();
    void HandleMapObjectCollision();
    bool HandleIsEscapeAvailable();
    const int NUMBER_OF_ITEM_TYPES = 4;
};
