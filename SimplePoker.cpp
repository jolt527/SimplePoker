#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

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



int main(int argc, char* argv[]) {

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* texture = NULL;

    //TODO This nested if-else mess is from tutorials.  It needs to be refactored and cleaned up!
    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        cerr << "SDL could not initialize!  SDL_Error: " << SDL_GetError() << endl;
    }
    else {
        window = SDL_CreateWindow("Simple Poker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if (NULL == window) {
            cerr << "Window could not be created!  SDL_Error: " << SDL_GetError() << endl;
        }
        else {
            renderer = SDL_CreateRenderer(window, -1, 0);
            if (NULL == renderer) {
                cerr << "Renderer could not be created!  SDL_Error: " << SDL_GetError() << endl;
            }
            else {
                // load the cards image
                SDL_Surface* cards_image_surface = SDL_LoadBMP(CARDS_IMAGE_FILENAME);
                if (NULL == cards_image_surface) {
                    cerr << "Couldn't load image \"" << CARDS_IMAGE_FILENAME << "\"!  SDL_Error: " << SDL_GetError() << endl;
                }
                else
                {
                    texture = SDL_CreateTextureFromSurface(renderer, cards_image_surface);
                    if (NULL == texture) {
                        cerr << "Couldn't create texture from surface!  SDL_Error: " << SDL_GetError() << endl;
                    }
                    else {
                        // we don't need that surface anymore since it's been converted to a texture
                        SDL_FreeSurface(cards_image_surface);

                        // clear the display
                        SDL_SetRenderDrawColor(renderer, TABLE_COLOR.r, TABLE_COLOR.g, TABLE_COLOR.b, SDL_ALPHA_OPAQUE);
                        SDL_RenderClear(renderer);

                        // draw stuff here!

                        // location of the ace of spades in the image
                        int card_image_x = CARD_WIDTH * 12;
                        int card_image_y = CARD_HEIGHT * 0;

                        SDL_Rect src_rect;
                        src_rect.x = card_image_x;
                        src_rect.y = card_image_y;
                        src_rect.w = CARD_WIDTH;
                        src_rect.h = CARD_HEIGHT;

                        // destination is the center of the screen
                        SDL_Rect dst_rect;
                        dst_rect.x = (DEFAULT_SCREEN_WIDTH - CARD_WIDTH) / 2;
                        dst_rect.y = (DEFAULT_SCREEN_HEIGHT - CARD_HEIGHT) / 2;;
                        dst_rect.w = CARD_WIDTH;
                        dst_rect.h = CARD_HEIGHT;

                        // rotate the card a bit, for funsies
                        double rotation_degrees = 30;

                        // draw the card as previously defined
                        SDL_RenderCopyEx(renderer, texture, &src_rect, &dst_rect, rotation_degrees, NULL, SDL_FLIP_NONE);

                        // display what has been drawn and delay a bit before quitting
                        SDL_RenderPresent(renderer);
                        SDL_Delay(2000);
                    }
                }
            }
        }
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
