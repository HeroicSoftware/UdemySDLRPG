#include "MapScreen.h"
MapScreen::MapScreen(SDL_Renderer *renderer, Hero *hero, int *playerInventory)
{
    // Seed Random Number Generator
    srand(time(NULL));
    this->renderer = renderer;
    this->hero = hero;
    this->playerInventory = playerInventory;
    // Generate the map - initialize all values to zero
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            dungeonMap[i][j] = 0;
        }
    }
    fstream mapFile("assets/map.txt");
    if (mapFile.is_open())
    {
        for (int column = 0; column < 10; column++)
        {
            for (int row = 0; row < 10; row++)
            {
                char gridSymbol;
                mapFile >> gridSymbol;
                if (gridSymbol == '0')
                {
                    dungeonMap[row][column] = 0;
                }
                else
                {
                    dungeonMap[row][column] = 1;
                    switch (gridSymbol)
                    {
                    case 'h':
                        heroObject.objectType = OBJECT_TYPES::HERO;
                        heroObject.xPosition = row;
                        heroObject.yPosition = column;
                        break;
                    case 'd':
                        doorObject.objectType = OBJECT_TYPES::DOOR;
                        doorObject.xPosition = row;
                        doorObject.yPosition = column;
                        break;
                    case 'c':
                        // Create a new chest object
                        MapObject chest;
                        chest.objectType = OBJECT_TYPES::CHEST;
                        chest.xPosition = row;
                        chest.yPosition = column;
                        // Add it to the list of mapObjects
                        mapObjects.push_back(chest);
                        break;
                    case 's':
                        // Create a new Sham
                        MapObject sham;
                        sham.objectType = OBJECT_TYPES::SHAM;
                        sham.xPosition = row;
                        sham.yPosition = column;
                        mapObjects.push_back(sham);
                        break;
                    case 'k':
                        // Create a new Sham
                        MapObject klog;
                        klog.objectType = OBJECT_TYPES::KLOG;
                        klog.xPosition = row;
                        klog.yPosition = column;
                        mapObjects.push_back(klog);
                    default:
                        dungeonMap[row][column] = 1;
                    }
                }
            }
        }
    }
    mapFile.close();
    // Load Textures
    LoadTextures();
    // Setup InformationBox
    informationBox.Setup(renderer);
    informationBox.SetText("Juvenile_Mirage");
}
MapScreen::~MapScreen()
{
    SDL_DestroyTexture(heroTileTexture);
    SDL_DestroyTexture(klobTileTexture);
    SDL_DestroyTexture(chestTileTexture);
    SDL_DestroyTexture(doorTileTexture);
}
void MapScreen::DrawToScreen()
{
    // Tile representing size of 1 grid square from the map
    SDL_Rect tileRectangle = {0, 0, tileWidth, tileHeight};
    // Draw each grid tile from map array
    // Generate the map
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            // If is walkable set to groundColor
            // Else set to wallColor
            if (dungeonMap[i][j] == 1)
            {
                // Blue walkable
                SDL_SetRenderDrawColor(renderer, 39, 253, 245, 255);
            }
            else
            {
                // Black wall
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            // Move rectangle to grid position with regards to tile
            tileRectangle.x = i * tileRectangle.w;
            tileRectangle.y = j * tileRectangle.h;
            // draw rectangle to screen using current draw colour
            SDL_RenderFillRect(renderer, &tileRectangle);
        }
    }
    // Draw other tiles on top of the Map
    DrawMapObjects();
}
void MapScreen::Update()
{
    // Read User Inputs INcluding Keyboard, Mouse and game pad
    SDL_Event inputSDLEvent;
    // Loop through events
    while (SDL_PollEvent(&inputSDLEvent))
    {
        // Check for ESC key
        if (inputSDLEvent.type == SDL_QUIT)
        {
            this->isExitProgram = true;
        }
        // Hide information box when
        // Check for close window
        if (inputSDLEvent.type == SDL_KEYDOWN)
        {
            if (inputSDLEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                this->isExitProgram = true;
            }
            if (inputSDLEvent.key.keysym.scancode == SDL_SCANCODE_SPACE)
            {
                this->informationBox.isVisible = false;
            }
            // If the information is not visible and player has health
            if (informationBox.isVisible == false && hero->GetHitPoints() > 0)
            {
                // Player movement
                int playerX = heroObject.xPosition;
                int playerY = heroObject.yPosition;
                // Arrow Keys
                if (inputSDLEvent.key.keysym.scancode == SDL_SCANCODE_RIGHT)
                {
                    playerX++;
                }
                if (inputSDLEvent.key.keysym.scancode == SDL_SCANCODE_LEFT)
                {
                    playerX--;
                }
                if (inputSDLEvent.key.keysym.scancode == SDL_SCANCODE_UP)
                {
                    playerY--;
                }
                if (inputSDLEvent.key.keysym.scancode == SDL_SCANCODE_DOWN)
                {
                    playerY++;
                }
                // If playerX and playerY are within the bounds of the grid allow for movement and is walkable
                if ((playerX >= 0 && playerX <= 9) && (playerY >= 0 && playerY <= 9) && (dungeonMap[playerX][playerY] == 1))
                {
                    heroObject.xPosition = playerX;
                    heroObject.yPosition = playerY;
                    // Check if player has moved onto map object
                    HandleMapObjectCollision();
                    // Is Escape possible
                    if ((this->isEscapeAvailable == true) && (isEscaped == false) && (playerX == doorObject.xPosition) && (playerY == doorObject.yPosition))
                    {
                        informationBox.SetText("You escape the Haunted Wento Mall!");
                        informationBox.isVisible = true;
                        isEscaped = true;
                    }
                }
            }
        }
    }
    // Check if all mapObjects are inactive
    if (informationBox.isVisible == false && this->isEscapeAvailable == false)
    {
        this->isEscapeAvailable = HandleIsEscapeAvailable();
        if (isEscapeAvailable == true)
        {
            informationBox.SetText("The curse is lifted!");
            informationBox.isVisible = true;
        }
    }
    if ((informationBox.isVisible == false) && (isEscaped == true || hero->GetHitPoints() <= 0))
    {
        isExitProgram = true;
    }
}
void MapScreen::ItemFound()
{
    // Randomly pick an item a number between 1 and 4
    int itemFound = rand() % NUMBER_OF_ITEM_TYPES + 1;
    bool freeSlotFound = false;
    for (int i = 0; i < 10; i++)
    {
        if (playerInventory[i] == INVENTORY_ITEMS::NO_ITEM)
        {
            freeSlotFound = true;
            playerInventory[i] = itemFound;
            break;
        }
    }
    if (freeSlotFound)
    {
        if (itemFound == INVENTORY_ITEMS::RESTORE_HP)
        {
            // TMNT
            informationBox.SetText("Found a slice of Splinter's NYC Pizza!");
        }
        else if (itemFound == INVENTORY_ITEMS::DAMAGE_ITEM)
        {
            // Gagettron from Ratchet and Clank
            informationBox.SetText("Found a GadgetPhonic Personal Taser!");
        }
        else if (itemFound == INVENTORY_ITEMS::ATTACK_UP)
        {
            // Murray from Sly Cooper
            informationBox.SetText("Found a Brawny Hippo Gummy!");
        }
        else if (itemFound == INVENTORY_ITEMS::DEFENSE_UP)
        {
            // Guilty Gear
            informationBox.SetText("Found a Rygar Guard keychain!");
        }
        else if (itemFound == INVENTORY_ITEMS::AGILITY_UP)
        {
            //  Guilty Gear
            informationBox.SetText("Found a Zanuff NRG Drink!");
        }
    }
    else
    {
        informationBox.SetText("Backpack is full!");
    }
    informationBox.isVisible = true;
}
SDL_Texture *MapScreen::LoadTexture(const char *filename, SDL_Renderer *renderer)
{
    SDL_Texture *texture;
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
    texture = IMG_LoadTexture(renderer, filename);
    return texture;
}
void MapScreen::LoadTextures()
{
    // Load Textures
    this->doorTileTexture = LoadTexture("assets/doorTile.png", renderer);
    this->heroTileTexture = LoadTexture("assets/heroTile.png", renderer);
    this->chestTileTexture = LoadTexture("assets/chestTile.png", renderer);
    this->klobTileTexture = LoadTexture("assets/klobTile.png", renderer);
}
void MapScreen::DrawMapObjects()
{
    // Tile representing size of 1 grid square from the map
    SDL_Rect tileRectangle = {0, 0, tileWidth, tileHeight};
    tileRectangle.x = heroObject.xPosition * tileRectangle.w;
    tileRectangle.y = heroObject.yPosition * tileRectangle.h;
    SDL_RenderCopy(renderer, heroTileTexture, NULL, &tileRectangle);
    tileRectangle.x = doorObject.xPosition * tileRectangle.w;
    tileRectangle.y = doorObject.yPosition * tileRectangle.h;
    SDL_RenderCopy(renderer, doorTileTexture, NULL, &tileRectangle);
    for (MapObject mapObject : mapObjects)
    {
        if (mapObject.isActive)
        {
            tileRectangle.x = mapObject.xPosition * tileRectangle.w;
            tileRectangle.y = mapObject.yPosition * tileRectangle.h;
            if (mapObject.objectType == OBJECT_TYPES::KLOG)
            {
                SDL_RenderCopy(renderer, klobTileTexture, NULL, &tileRectangle);
            }
            else
            {
                SDL_RenderCopy(renderer, chestTileTexture, NULL, &tileRectangle);
            }
        }
    }
    informationBox.Draw();
}
void MapScreen::HandleMapObjectCollision()
{
    for (list<MapObject>::iterator mapObjectIterator = mapObjects.begin(); mapObjectIterator != mapObjects.end(); mapObjectIterator++)
    {
        // Dereference the iterator to get the object
        if (mapObjectIterator->isActive)
        {
            // If the hero is on the square as the object
            if ((heroObject.xPosition == mapObjectIterator->xPosition) && (heroObject.yPosition == mapObjectIterator->yPosition))
            {
                // Move the object from the map
                mapObjectIterator->isActive = false;
                // Check the object's type and handle it.
                if (mapObjectIterator->objectType == OBJECT_TYPES::KLOG)
                {
                    BattleScreen battleScreen(renderer, hero, playerInventory, KlogType);
                    battleScreen.Update();
                    if (battleScreen.GetIsExitProgram() == true)
                    {
                        this->isExitProgram = true;
                    }
                    if (hero->GetHitPoints() <= 0)
                    {
                        informationBox.SetText("You have been slain!");
                        informationBox.isVisible = true;
                    }
                }
                else if (mapObjectIterator->objectType == OBJECT_TYPES::SHAM)
                {
                    BattleScreen battleScreen(renderer, hero, playerInventory, ShamType);
                    battleScreen.Update();
                    if (battleScreen.GetIsExitProgram() == true)
                    {
                        this->isExitProgram = true;
                    }
                    if (hero->GetHitPoints() <= 0)
                    {
                        informationBox.SetText("You have been slain!");
                        informationBox.isVisible = true;
                    }
                }
                else if (mapObjectIterator->objectType == OBJECT_TYPES::CHEST)
                {
                    // Open CHest and get Item
                    ItemFound();
                }
            }
        }
    }
}
bool MapScreen::HandleIsEscapeAvailable()
{
    bool isAllMonstersDefeated = true;
    if (informationBox.isVisible == false && isEscapeAvailable == false)
    {
        for (MapObject mapObject : mapObjects)
        {
            // If the mapObject is a monster
            if ((mapObject.objectType == OBJECT_TYPES::KLOG) || (mapObject.objectType == OBJECT_TYPES::SHAM))
            {
                // If the monster is active
                if (mapObject.isActive)
                {
                    return false;
                }
            }
        }
    }
    return isAllMonstersDefeated;
    ;
}
