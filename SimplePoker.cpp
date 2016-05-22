#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

const int DEFAULT_SCREEN_WIDTH = 640;
const int DEFAULT_SCREEN_HEIGHT = 480;

typedef struct Color {
    Uint8 r;
    Uint8 g;
    Uint8 b;
} Color;

const Color TABLE_COLOR = { 0x00, 0x80, 0x00 };



int main(int argc, char* argv[]) {

    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;

    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        cerr << "SDL could not initialize!  SDL_Error: " << SDL_GetError() << endl;
    }
    else {
        window = SDL_CreateWindow("Simple Poker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if (NULL == window) {
            cerr << "Window could not be created!  SDL_Error: " << SDL_GetError() << endl;
        }
        else {
            screenSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, TABLE_COLOR.r, TABLE_COLOR.g, TABLE_COLOR.b));
            SDL_UpdateWindowSurface(window);
            SDL_Delay(2000);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
