#ifndef COMMONFUNC_H_INCLUDED
#define COMMONFUNC_H_INCLUDED

#include <windows.h>
#include <string>
#include <math.h>
#include <SDL.h>
#include <vector>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "BaseObject.h"
#include "TextObject.h"

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
static SDL_Surface* g_img_menu = NULL;
static Mix_Chunk* g_sound=NULL;
static Mix_Chunk* g_death_sound=NULL;

//screen
const int FRAME_PER_SECOND= 25;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0xff;

#define BLANK_TILE 0
#define TILE_SIZE 64
#define MAX_MAP_X 20
#define MAX_MAP_Y 10

typedef struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
    int jump_1;
    int jump_2;
    int jump_3;
};

typedef struct Map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name_;
};
//float chat_nhi_phan(float l. float r, float )

namespace SDLCommonFunc
{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
    int ShowMenu(SDL_Renderer* des, TTF_Font* font,bool kt);
    bool CheckFocusWithRect(const int &x, const int &y, const SDL_Rect& rect);
}

#endif // COMMONFUNC_H_INCLUDED
