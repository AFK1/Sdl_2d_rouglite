#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

SDL_Window *win = NULL;
SDL_Renderer *ren = NULL;

bool init() {
    bool ok = true;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Can't init SDL: " << SDL_GetError() << endl;
    }

    win = SDL_CreateWindow("Примитивы", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        cout << "Can't create window: " << SDL_GetError() << endl;
        ok = false;
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (ren == NULL) {
        cout << "Can't create renderer: " << SDL_GetError() << endl;
        ok = false;
    }
    return ok;
}

void quit() {
    SDL_DestroyWindow(win);
    win = NULL;

    SDL_DestroyRenderer(ren);
    ren = NULL;

    SDL_Quit;
}

int main (int arhc, char ** argv) {
    if (!init()) {
        quit();
        system("pause");
        return 1;
    }

    SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);

    SDL_Rect rect1 = {10, 10, 50, 50};
    SDL_RenderFillRect(ren, &rect1);

    SDL_Rect rect2 = {70, 10, 50, 50};
    SDL_RenderDrawRect(ren, &rect2);

    SDL_RenderDrawLine(ren, 10, 70, 640 - 10, 70);

    for (int i = 10; i <= 640-10; i +=4 ) {
        SDL_RenderDrawPoint(ren, i, 90);
    }

    SDL_RenderPresent(ren);

    SDL_Delay(5000);

    quit();
    return 0;
}
