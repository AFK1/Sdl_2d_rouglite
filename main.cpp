#include <SDL2/SDL.h>
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

int SCREEN_WIDTH = 625;
int SCREEN_HEIGHT = 625;
const int sz_map = 25;
int maprooms[sz_map][sz_map] = { { 0 } };
const int asdsad_need = 4;
const int clr[5][3] = {
    {0,0,0},
    {30,50,255},
    {255,30,50},
    {50,255,30},
    {100,50,30},
};
const int room_cd = 4;

SDL_Window *win = NULL;
SDL_Renderer *ren = NULL;

SDL_Rect rect = { 0, 0, 25, 25 };

bool init() {
    bool ok = true;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Can't init SDL: " << SDL_GetError() << endl;
    }

    win = SDL_CreateWindow("room", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

//==========================RoomGenerator=======================//

int square(int tp) {
    int sq = 0;
    for (int i = 0; i <= 25; i++) {
        for (int j = 0; j <= 25; j++) {
            if (maprooms[i][j] == tp) {
                sq++;
            }
        }
    }
    return sq;
}

void grow(int dir, int tp, int cd) {
    //printf("|%d %d %d|", dir, tp, cd);
    int fgff[sz_map*2][2];                         //peremenuy
    int asdsad = 0;
    if (dir == 1) {
        for (int n = 1; n < cd; n++) {
            for (int i = 0; i <= 25; i++) {
                for (int j = 1; j <= 24; j++) {
                    if (maprooms[i][j] == tp && maprooms[i][j - 1] == 0) {
                        fgff[asdsad][0] = i; fgff[asdsad][1] = j-1;
                        asdsad++;
                        //maprooms[i][j - 1] = tp;
                    }
                }
            }
        }
    }
    else {
        if (dir == 2) {
            for (int n = 1; n < cd; n++) {
                for (int i = 23; i >= 0; i--) {
                    for (int j = 0; j <= 25; j++) {
                        if (maprooms[i][j] == tp && maprooms[i + 1][j] == 0) {
                            fgff[asdsad][0] = i+1; fgff[asdsad][1] = j;
                            asdsad++;
                            //maprooms[i + 1][j] = tp;
                        }
                    }
                }
            }
        }
        else {
            if (dir == 3) {
                for (int n = 1; n < cd; n++) {
                    for (int i = 0; i <= 25; i++) {
                        for (int j = 23; j >= 0; j--) {
                            if (maprooms[i][j] == tp && maprooms[i][j + 1] == 0) {
                                fgff[asdsad][0] = i; fgff[asdsad][1] = j+1;
                                asdsad++;
                                //maprooms[i][j + 1] = tp;
                            }
                        }
                    }
                }
            }
            else {
                if (dir == 4) {
                    for (int n = 1; n < cd; n++) {
                        for (int i = 1; i <= 24; i++) {
                            for (int j = 0; j <= 25; j++) {
                                if (maprooms[i][j] == tp && maprooms[i - 1][j] == 0) {
                                    fgff[asdsad][0] = i-1; fgff[asdsad][1] = j;
                                    asdsad++;
                                    //maprooms[i - 1][j] = tp;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    printf("|>%d|", asdsad);
    int yu = (square(tp));
    if (asdsad >= asdsad_need || yu <= asdsad_need* asdsad_need) {
        for (int i = 0; i < asdsad-1; i++) {
            printf("|%d  %d %d<|", fgff[i][0], fgff[i][1], i);
            maprooms[fgff[i][0]][fgff[i][1]] = tp;
        }
    }
}

void create_rm() {
    for (int i = 1; i <= room_cd; i++) {
        int xq = rand() % 25; int yq = rand() % 25;
        while (maprooms[xq][yq] != 0) {
            xq = rand() % 25; yq = rand() % 25;
        }
        maprooms[xq][yq] = i;
        for (int j = 0; j < 4; j++) {
            grow(j, i, 3);
        }
    }
}

int main (int arhc, char ** argv) {
    srand(time(0));
    if (!init()) {
        quit();
        system("pause");
        return 1;
    }
    SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(ren);
    create_rm();
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 25; j++) {
            SDL_SetRenderDrawColor(ren, clr[maprooms[i][j]][0], clr[maprooms[i][j]][1], clr[maprooms[i][j]][2], 0xFF);
            rect.x = i * 25; rect.y = j * 25;
            SDL_RenderFillRect(ren, &rect);
            printf("%d", maprooms[j][i]);
        }
        printf("\n");
    }
    SDL_RenderPresent(ren);
    //SDL_Delay(3000);
    int stp = 0;

    while (square(4) < 80) {
        grow(rand() % 4 + 1, 4, rand() % 2 + 2);
        SDL_Delay(20);
        SDL_RenderPresent(ren);
    }
    while (!stp) {
        stp = 1;
        grow(rand() % 4 + 1, rand() % 3 + 1, rand() % 3 + 3);
        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 25; j++) {
                SDL_SetRenderDrawColor(ren, clr[maprooms[i][j]][0], clr[maprooms[i][j]][1], clr[maprooms[i][j]][2], 0xFF);
                if (maprooms[i][j] == 0) { stp = 0; }
                rect.x = i * 25;rect.y = j * 25;
                SDL_RenderFillRect(ren, &rect);
            }
        }
        SDL_Delay(20);
        SDL_RenderPresent(ren);
    }
    SDL_Delay(2000);
    quit();
    return 0;
}
