#include "BattleScreen.h"
void BattleScreen::HandleBattleScreenPlayerOptionSelection(SDL_Event inputSDLEvent)
{
    // Exit game
    if (inputSDLEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
    {
        this->isExitProgram = true;
    }
    // Check for input on the battle screen - Select up and down
    if (inputSDLEvent.key.keysym.scancode == SDL_SCANCODE_UP)
    {
        if (isHeroesTurn == true)
        {
            fightButton.isSelected = true;
            itemButton.isSelected = false;
        }
    }
    // Check for input on the battle screen - Select up and down
    if (inputSDLEvent.key.keysym.scancode == SDL_SCANCODE_DOWN)
    {
        if (isHeroesTurn == true)
        {
            fightButton.isSelected = false;
            itemButton.isSelected = true;
        }
    }
    // Select Menu Option
    if (inputSDLEvent.key.keysym.scancode == SDL_SCANCODE_SPACE && inputSDLEvent.key.repeat == 0)
    {
        if (isHeroesTurn == true && IsAnimationsPlaying() == false)
        {
            // Player Turn
            if (fightButton.isSelected = true)
            {
                heroAnimationSet.PlayAttack();
                enemyDamage = player->DealDamage();
                enemy->TakeDamage(enemyDamage);
                enemyAnimationSet.PlayHit();
                enemyBattleVisualEffect.PlayHit();
                isHeroesTurn = false;
            }
        }
    }
}
void BattleScreen::UpdateCharacters(Character *enemy, Hero *player)
{
    if (IsAnimationsPlaying() == false)
    {
        // If player or enemy are defeated then end battle
        if (player->GetHitPoints() <= 0 || enemy->GetHitPoints() <= 0)
        {
            if (player->GetHitPoints() <= 0)
            {

                playerBattleVisualEffect.PlayDeath();
            }
            if (enemy->GetHitPoints() <= 0)
            {
                enemyBattleVisualEffect.PlayDeath();
            }
            isBattleFinished = true;
        }
        if (isHeroesTurn == false)
        {
            // Enemy Attack
            enemyAnimationSet.PlayAttack();
            playerDamage = enemy->DealDamage() + 3; // Magic Number
            player->TakeDamage(playerDamage);
            heroAnimationSet.PlayHit();
            playerBattleVisualEffect.PlayHit();
            isHeroesTurn = true;
        }
    }
}
BattleScreen::BattleScreen(SDL_Renderer *renderer, Hero *hero, int *currentInventory, CharacterType enemyType)
{
    this->renderer = renderer;
    this->player = hero;
    this->items = currentInventory;
    if (enemyType != KlogType && enemyType != ShamType)
    {
        enemyType = KlogType;
    }
    // Load background texture
    backgroundTexture = LoadTexture("assets/battlescreenBackground.png", renderer);
    // Create name texture
    // Load font with font size 16
    CreatePlayerNameTextTexture();
    // Create UI Bar
    CreateUIBar();
    // Setup Animations
    heroAnimationSet.Setup(renderer, 7, 50, HeroType);
    enemyAnimationSet.Setup(renderer, 220, 10, enemyType);
    if (enemyType == KlogType)
    {
        enemy = new Klog();
    }
    else if (enemyType == ShamType)
    {
        enemy = new Sham();
    }
    // Setup Health Bars
    enemyHPBar.Initialize(renderer, ENEMYHPXPOSITION, ENEMYHPYPOSITION);
    heroHPBar.Initialize(renderer, HEROHPXPOSITION, HEROHPYPOSITION);
    // Setup BattleButtons
    fightButtonRect = {0, 180, 80, 30};
    fightButton.Initialize(renderer, fightButtonRect, "Fight");
    fightButton.isSelected = true;
    itemButtonRect = {0, 210, 80, 30};
    itemButton.Initialize(renderer, itemButtonRect, "Items");
    // Determine who goes first
    DetermineBattleOrder();
    // Setup Battle Effects
    enemyBattleVisualEffect.Initialize(renderer, enemyAnimationSet.x, enemyAnimationSet.y);
    playerBattleVisualEffect.Initialize(renderer, heroAnimationSet.x, heroAnimationSet.y);
}
BattleScreen::~BattleScreen()
{
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(playerNameTexture);
}
SDL_Texture *BattleScreen::LoadTexture(const char *filename, SDL_Renderer *renderer)
{
    SDL_Texture *texture;
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
    texture = IMG_LoadTexture(renderer, filename);
    return texture;
}
void BattleScreen::Draw()
{
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 21, 209, 249, 255);
    // Draw Background Texture
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    // Draw Enemy
    enemyAnimationSet.Draw();
    // Draw Hero Animation
    heroAnimationSet.Draw();
    // UI Bottom
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &bottomUIBar);
    // UI Border Border
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &bottomUIBar);
    // Draw Name
    SDL_RenderCopy(renderer, playerNameTexture, NULL, &playerNameRectangle);
    // HP Bars
    heroHPBar.Draw();
    enemyHPBar.Draw();
    // Draw the Battle Buttons
    fightButton.Draw();
    itemButton.Draw();
    // Draw Effects
    enemyBattleVisualEffect.Draw();
    playerBattleVisualEffect.Draw();
    // Present to screen
    SDL_RenderPresent(renderer);
}
void BattleScreen::Update()
{
    // Timing
    // DeltaTime ( measurement of time per frame render as a fraction of 1 second)
    float deltaTime = 0;
    Uint32 lastUpdate = SDL_GetTicks();
    while (isBattleFinished == false)
    {
        Uint32 curretTime = SDL_GetTicks() - lastUpdate;
        deltaTime = curretTime / 1000.0f;
        lastUpdate = SDL_GetTicks(); // Update this to get the correct lastUpdate
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
                HandleBattleScreenPlayerOptionSelection(inputSDLEvent);
            }
        }
        if (isExitProgram == true)
        {
            this->isBattleFinished = true;
        }
        // Update Character States
        UpdateCharacters(enemy, player);
        // Update Animations
        heroAnimationSet.Update(deltaTime);
        enemyAnimationSet.Update(deltaTime);
        // Update Healthbars
        heroHPBar.SetCurrentHP(player->GetHitPoints());
        heroHPBar.SetMaxHP(player->GetMaximumHitPoints());
        enemyHPBar.SetCurrentHP(enemy->GetHitPoints());
        enemyHPBar.SetMaxHP(enemy->GetMaximumHitPoints());
        // Update BattleEffectANiations
        enemyBattleVisualEffect.Update(deltaTime);
        playerBattleVisualEffect.Update(deltaTime);
        Draw();
    }
}
void BattleScreen::CreateUIBar()
{
    bottomUIBar = {0, 180, 320, 60};
}
void BattleScreen::CreatePlayerNameTextTexture()
{
    fontSize = 8;
    this->playerNameTextColor = {0, 0, 0, 0};
    font = TTF_OpenFont("assets/PublicPixel.ttf", fontSize);
    SDL_Surface *playerNameTextSurface = TTF_RenderText_Blended(font, player->GetName().c_str(), playerNameTextColor);
    playerNameTexture = SDL_CreateTextureFromSurface(renderer, playerNameTextSurface);
    SDL_FreeSurface(playerNameTextSurface);
    TTF_CloseFont(font);
    playerNameRectangle.x = playerNameRectangleX;
    playerNameRectangle.y = playerNameRectangleY;
    SDL_QueryTexture(playerNameTexture, NULL, NULL, &playerNameRectangle.w, &playerNameRectangle.h);
}
bool BattleScreen::GetIsExitProgram()
{
    return isExitProgram;
}
bool BattleScreen::GetIsBattleFinished()
{
    return isBattleFinished;
}
bool BattleScreen::IsAnimationsPlaying()
{
    bool isAnimationPlaying = (heroAnimationSet.hasAnimationBeenPlayed || enemyAnimationSet.hasAnimationBeenPlayed || enemyBattleVisualEffect.hasBattleVisualEffectPlayed || playerBattleVisualEffect.hasBattleVisualEffectPlayed);
    return isAnimationPlaying;
}
void BattleScreen::DetermineBattleOrder()
{
    if (player->GetAgility() > enemy->GetAgility())
    {
        isHeroesTurn = true;
        printf("%s Swiftly readies for battle\n", player->GetName().c_str());
    }
    else
    {
        printf("The monster ambushes the teenaged adventurer\n");
        isHeroesTurn = false;
    }
}