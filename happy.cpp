#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

void init_text(SDL_Renderer *renderer, SDL_Texture **texture_o, SDL_Rect *dstrect_o, SDL_Color *color);

int main()
{
    int i, x, y;

    srand(time(NULL));

    SDL_Event event;
    //The window we'll be rendering to
    SDL_Window *window = NULL;

    SDL_Renderer *renderer = NULL;

    TTF_Init();

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    //Create window
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }

    SDL_Texture *texture;
    SDL_Rect dstrect;
    SDL_Color color = {255, 255, 255};

    init_text(renderer, &texture, &dstrect, &color);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (i = 0; i < 400; ++i)
    {
        x = rand() % SCREEN_WIDTH;
        y = rand() % SCREEN_HEIGHT;
        SDL_RenderDrawPoint(renderer, x, y);
    }
    SDL_RenderPresent(renderer);
    while (1)
    {
        if (SDL_PollEvent(&event) && (event.type == SDL_QUIT || event.type == SDL_KEYDOWN))
            break;
        color={rand()%255, rand()%255, rand()%255};
        init_text(renderer, &texture, &dstrect, &color);
        SDL_RenderCopy(renderer, texture, NULL, &dstrect);
        SDL_RenderPresent(renderer);
        SDL_Delay(200);
    }

    SDL_DestroyTexture(texture);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void init_text(SDL_Renderer *renderer, SDL_Texture **texture_o, SDL_Rect *dstrect_o, SDL_Color *color)
{
    TTF_Font *font = TTF_OpenFont("arial.ttf", 50);
    if (font == NULL)
    {
        printf("Font could not be created! SDL_Error: %s\n", SDL_GetError());
    }
    SDL_Surface *surface = TTF_RenderText_Solid(font, "Happy Christmas!", *color);
    *texture_o = SDL_CreateTextureFromSurface(renderer, surface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(*texture_o, NULL, NULL, &texW, &texH);
    *dstrect_o = {800, 400, texW, texH};
    TTF_CloseFont(font);
    SDL_FreeSurface(surface);
}