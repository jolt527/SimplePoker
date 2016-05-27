#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
#include "Card.h"
#include "Entity.h"
#include "Animated_card_entity.h"

using namespace std;

const int FAILURE_STATUS = 1;

const int DEFAULT_SCREEN_WIDTH = 640;
const int DEFAULT_SCREEN_HEIGHT = 480;

const int CARD_WIDTH = 100;
const int CARD_HEIGHT = 140;

typedef struct Color {
    Uint8 r;
    Uint8 g;
    Uint8 b;
} Color;

const Color TABLE_COLOR = { 0x00, 0x80, 0x00 };

const char CARDS_IMAGE_FILENAME[] = "assets/simplified-cards.bmp";
const char CARD_BACK_IMAGE_FILENAME[] = "assets/card-back-blue-checkered.bmp";

SDL_Window* window_p = NULL;
SDL_Renderer* renderer_p = NULL;
SDL_Texture* front_texture_p = NULL;
SDL_Texture* back_texture_p = NULL;



// cleanup all the textures, renderers, and windows
void cleanup() {
    SDL_DestroyTexture(back_texture_p);
    SDL_DestroyTexture(front_texture_p);
    SDL_DestroyRenderer(renderer_p);
    SDL_DestroyWindow(window_p);
}



// cleanup meant to happen before exiting with a failure code
void cleanup_and_fail() {
    cleanup();
    exit(FAILURE_STATUS);
}



// loads a texture from a specific file
SDL_Texture* load_texture(const char* file_name_p, SDL_Renderer* renderer_p) {
    SDL_Surface* image_surface_p = SDL_LoadBMP(file_name_p);
    if (NULL == image_surface_p) {
        cerr << "Couldn't load image \"" << file_name_p << "\"!  SDL_Error: " << SDL_GetError() << endl;
        cleanup_and_fail();
    }

    SDL_Texture* texture_p = SDL_CreateTextureFromSurface(renderer_p, image_surface_p);
    if (NULL == texture_p) {
        cerr << "Couldn't create texture from surface!  SDL_Error: " << SDL_GetError() << endl;
        cleanup_and_fail();
    }

    // we don't need that surface anymore since it's been converted to a texture
    SDL_FreeSurface(image_surface_p);

    return texture_p;
}



// the entry point of the game
int main(int argc, char* argv[]) {

    //TODO This nested if-else mess is from tutorials.  It needs to be refactored and cleaned up!
    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        cerr << "SDL could not initialize!  SDL_Error: " << SDL_GetError() << endl;
        cleanup_and_fail();
    }

    window_p = SDL_CreateWindow("Simple Poker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if (NULL == window_p) {
        cerr << "Window could not be created!  SDL_Error: " << SDL_GetError() << endl;
        cleanup_and_fail();
    }

    renderer_p = SDL_CreateRenderer(window_p, -1, 0);
    if (NULL == renderer_p) {
        cerr << "Renderer could not be created!  SDL_Error: " << SDL_GetError() << endl;
        cleanup_and_fail();
    }

    // load the cards image and the card back image
    front_texture_p = load_texture(CARDS_IMAGE_FILENAME, renderer_p);
    back_texture_p = load_texture(CARD_BACK_IMAGE_FILENAME, renderer_p);

    // the card to display
    Card card0(Ten, Spade);
    Card card1(Jack, Club);
    Card card2(Queen, Diamond);
    Card card3(King, Heart);
    Card card4(Ace, Spade);
    Animated_card_entity animated_card_entity0(&card0, 0, back_texture_p, front_texture_p);
    Animated_card_entity animated_card_entity1(&card1, 1, back_texture_p, front_texture_p);
    Animated_card_entity animated_card_entity2(&card2, 2, back_texture_p, front_texture_p);
    Animated_card_entity animated_card_entity3(&card3, 3, back_texture_p, front_texture_p);
    Animated_card_entity animated_card_entity4(&card4, 4, back_texture_p, front_texture_p);

    Entity *entities[] = { &animated_card_entity0, &animated_card_entity1, &animated_card_entity2, &animated_card_entity3, &animated_card_entity4 };
    const int ENTITY_ARRAY_SIZE = 5;

    Uint32 warmup_time = SDL_GetTicks() + 500;

    // game loop goes here
    int i;
    SDL_Event e;
    bool should_quit = false;
    while (!should_quit) {

        Uint32 current_time = SDL_GetTicks();

        // process events
        while (0 != SDL_PollEvent(&e)) {
            if (SDL_QUIT == e.type) {
                should_quit = true;
            }
            else if (SDL_KEYDOWN == e.type && SDLK_ESCAPE == e.key.keysym.sym) {
                should_quit = true;
            }
        }

        // don't animate until the system has warmed up
        if (current_time >= warmup_time) {
            for (i = 0; i < ENTITY_ARRAY_SIZE; i++) {
                entities[i]->update(current_time);
            }
        }

        // render stuff to display

        // clear the display
        SDL_SetRenderDrawColor(renderer_p, TABLE_COLOR.r, TABLE_COLOR.g, TABLE_COLOR.b, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer_p);

        // render the entities
        for (i = 0; i < ENTITY_ARRAY_SIZE; i++) {
            entities[i]->render(renderer_p);
        }

        // display what has been drawn
        SDL_RenderPresent(renderer_p);
    }

    // delay a bit before actually quitting
    SDL_Delay(250);

    // cleanup and quit
    cleanup();
    SDL_Quit();

    return 0;
}
