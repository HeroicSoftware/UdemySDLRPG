// SDL2 Hello, World!
// This should display a white screen for 2 seconds
// compile with: clang++ main.cpp -o hello_sdl2 -lSDL2
// run with: ./hello_sdl2
#include "Character.h"
#include "Puzzles.h"
#include "Hero.h"
#include "Sham.h"
#include "Klog.h"
#include "MapScreen.h"
#include "MapObject.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <iostream>
#include <string>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define RENDER_LOGIC_WIDTH 320
#define RENDER_LOGIC_HEIGHT 240
int InitializeSDLSubsystems()
{
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        printf("[IMG_Init] - Failed to initialize required PNG support: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }
    if (TTF_Init() != 0)
    {
        printf("[SDL_TTF] - Failed to initialize required TTF support: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "[SDL ERROR] - Could not initialize SDL2 Video: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        fprintf(stderr, "[SDL ERROR] - Could not initialize SDL2 Audio: %s\n", Mix_GetError());
        SDL_Quit();
        return 1;
    }
}
void ClearScreen()
{
    cout << "\033[2J\033[1;1H"; // clear screen
}
SDL_Texture *LoadTexture(const char *filename, SDL_Renderer *renderer)
{
    SDL_Texture *texture;
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
    texture = IMG_LoadTexture(renderer, filename);
    return texture;
}
void DrawSingleTextureOnScreen(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y)
{
    SDL_Rect destination;
    destination.x = x;
    destination.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h);
    SDL_RenderCopy(renderer, texture, NULL, &destination);
}
int main(int argc, char *args[])
{
    cout << "HEROIC:\>DEEP_SPACE_BROADCAST: Juvenile_Mirage" << endl;
    cout << "What is your name hero?" << endl;
    // Variable to hold name of player
    string name;
    cin >> name;
    // Player stats
    int hp = 0, str = 0, def = 0, agi = 0;
    string playerClassType;
    bool characterSetup = false;
    Hero player;
    player.SetName(name);
    while (characterSetup == false)
    {
        cout << "What type of character are you?" << endl;
        cout << "1 - Light Knight Squire" << endl; // Weird 80's cartoon called visionaries
        cout << "2 - Lunar Glamstar " << endl;     // Sailor Moon + Hair Metal
        cout << "3 - Rat Clan Ninja" << endl;      // TMNT
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            hp = 100;
            str = 10;
            def = 2;
            agi = 3;
            playerClassType = "Light Knight Squire";
            player.SetupPlayerAttributes(hp, str, def, agi, name, playerClassType);
        }
        else if (choice == 2)
        {
            hp = 100;
            str = 4;
            def = 10;
            agi = 1;
            playerClassType = "Lunar Glamstar";
            player.SetupPlayerAttributes(hp, str, def, agi, name, playerClassType);
        }
        else if (choice == 3)
        {
            hp = 80;
            str = 3;
            def = 1;
            agi = 10;
            playerClassType = "Rat Clan Ninja";
            player.SetupPlayerAttributes(hp, str, def, agi, name, playerClassType);
        }
        else
        {
            cout << "Invalid choice! Try again...." << endl;
        }
        if (choice >= 1 && choice <= 3)
        {
            characterSetup = true;
        }
    }
    ClearScreen();

    SDL_Window *window = NULL;
    SDL_Surface *screenSurface = NULL;
    // Initialize SDL subsystems needed (SDL_image, SDL_mixer, SDL_ttf)
    InitializeSDLSubsystems();
    char windowTitle[] = "HEROIC:>DEEP-SPACE-BROADCAST: Juvenile_Mirage";
    window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        fprintf(stderr, "[SDL ERROR] - Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        fprintf(stderr, "[SDL ERROR] - Could not create renderer: %s\n", SDL_GetError());
        SDL_Quit();
        system("pause");
        return 1;
    }
    SDL_RenderSetLogicalSize(renderer, RENDER_LOGIC_WIDTH, RENDER_LOGIC_HEIGHT);
    // Load in an image
    SDL_Texture *titleImage = LoadTexture("assets/TitlePrototype.png", renderer);
    if (titleImage == NULL)
    {
        std::cout << "Unable to load Title Image: " << IMG_GetError() << endl;
    }
    int playerInventory[10];
    int item = 0;
    for (item; item < 10; item++)
    {
        playerInventory[item] = 0;
    }
    playerInventory[0] = 1;
    MapScreen mapScreen(renderer, &player, playerInventory);
    bool isMainLoop = true;

    while (isMainLoop)
    {
        SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
        // Clear entire
        SDL_RenderClear(renderer);
        SDL_Rect rectangle{};
        rectangle.w = 25;
        rectangle.h = 25;
        rectangle.x = 15;
        rectangle.y = 15;
        SDL_SetRenderDrawColor(renderer, 34, 76, 22, 255);
        SDL_RenderFillRect(renderer, &rectangle);
        // Draw the test Title Image
        // DrawSingleTextureOnScreen(titleImage, renderer, 0, 0);
        mapScreen.DrawToScreen();
        mapScreen.Update();
        SDL_RenderPresent(renderer);
        // Milliseconds since start of SDL Init
        if (mapScreen.isExitProgram == true)
        {
            isMainLoop = false;
        }
    }
    // SDL Cleanup
    SDL_DestroyTexture(titleImage);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
