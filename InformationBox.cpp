#include "InformationBox.h"
void InformationBox::Setup(SDL_Renderer *renderer)
{
    this->renderer = renderer;
}
void InformationBox::SetText(std::string text)
{
    // Destory previous text texture before creating new one
    if (this->textTexture != NULL)
    {
        SDL_DestroyTexture(this->textTexture);
    }
    // If text is new and not empty
    if (displayText != text && text != "")
    {
        // Set the displayText
        this->displayText = text;
        // build the text color
        this->displayTextColor = {0, 0, 0, 0};
        // build surface
        SDL_Surface *displayTextSurface = TTF_RenderText_Blended(font, displayText.c_str(), displayTextColor);
        // Convert Surface to Texture
        this->textTexture = SDL_CreateTextureFromSurface(renderer, displayTextSurface);
        // Delete the surface
        SDL_FreeSurface(displayTextSurface);
        // Get the width and height of the textTexture
        SDL_QueryTexture(textTexture, NULL, NULL, &textRectangle.w, &textRectangle.h);
        // Center the window of text in the screen
        textRectangle.x = (RENDER_LOGIC_WIDTH / 2) - (textRectangle.w / 2);
        textRectangle.y = (RENDER_LOGIC_HEIGHT / 2) - (textRectangle.h / 2);
        // Padding the text
        displayBoxRectangle.x = textRectangle.x - PADDING_WIDTH;
        displayBoxRectangle.y = textRectangle.y - PADDING_HEIGHT;
        displayBoxRectangle.w = textRectangle.w + (PADDING_HEIGHT + PADDING_WIDTH);
        displayBoxRectangle.h = textRectangle.h + (PADDING_HEIGHT + PADDING_WIDTH);
    }
}
void InformationBox::Draw()
{
    if (isVisible && textTexture != NULL && displayText != "")
    {

        // Draw box - Pink-ish
        SDL_SetRenderDrawColor(renderer, 200, 115, 154, 255);
        SDL_RenderFillRect(renderer, &displayBoxRectangle);
        // Draw a border
        SDL_SetRenderDrawColor(renderer, 140, 80, 108, 255);
        SDL_RenderDrawRect(renderer, &displayBoxRectangle);
        // Draw the text
        SDL_RenderCopy(renderer, textTexture, NULL, &textRectangle);
    }
}
InformationBox::InformationBox()
{
    // Load font with font size 16
    fontSize = 8;
    font = TTF_OpenFont("assets/PublicPixel.ttf", fontSize);
}
InformationBox::~InformationBox()
{
    // Clean up
    if (textTexture != NULL)
    {
        SDL_DestroyTexture(textTexture);
    }
    TTF_CloseFont(font);
}
