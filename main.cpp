#include "CommonFunc.h"
#include "BaseObject.h"
#include "game_map.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatObject.h"
#include <bits/stdc++.h>
#include "TextObject.h"

using namespace std;

BaseObject g_background;
BaseObject g_youdied;
TTF_Font *font_time=NULL;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret<0) return false;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
    g_window = SDL_CreateWindow("My game",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH,SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if (g_window == NULL)
    {
        success=false;
    }
    else
    {
        g_screen= SDL_CreateRenderer(g_window,-1,SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL) success=false;
        else
        {
            SDL_SetRenderDrawColor(g_screen,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags)) success=false;
        }
        if (TTF_Init()==-1) success=false;
        font_time=TTF_OpenFont("font//Anton-Regular.ttf",25);
    }
    if (Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096)==-1)  return false;
    return success;
}
bool LoadBackground()
{
    bool ret=g_background.LoadImg("img//background.png",g_screen);
    if (ret == false) return false;
    return true;
}
void close()
{

    Mix_FreeChunk(g_sound);
    Mix_FreeChunk(g_death_sound);
    g_background.Free();
    g_youdied.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen=NULL;
    SDL_DestroyWindow(g_window);
    g_window=NULL;
    IMG_Quit();
    SDL_Quit();
    Mix_Quit();
}
/*std::vector<ThreatsObject*> MakeThreadList()
{
    std::vector<ThreatsObject*> list_threats;
    ThreatsObject* threats_objs = new ThreatsObject[5];
    for (int i=0; i<1; i++)
    {
        ThreatsObject* p_threat=(threats_objs + i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("img/Bat/Flying (46x30).png",g_screen);
            p_threat->set_clips();
            p_threat->set_x_pos((rand()%SCREEN_WIDTH)+120);
            p_threat->set_y_pos(0);

            list_threats.push_back(p_threat);
        }
    }
    return list_threats;
}*/
std::vector<ThreatsObject*> threats_list;
void IncreaseThreat()
{
    ThreatsObject* p_threatt = new ThreatsObject;
    if (p_threatt != NULL)
    {
        p_threatt->LoadImg("img/Bat/Flying (46x30).png",g_screen);
        p_threatt->set_clips();
        p_threatt->set_x_pos((rand()%SCREEN_WIDTH)+120);
        p_threatt->set_y_pos(0);
        threats_list.push_back(p_threatt);
    }
}
int main( int argc, char* args[] )
{

    srand(time(NULL));
    ImpTimer fps_timer;

    if (InitData() == false) return -1;
    if (LoadBackground()== false) return -1;
    g_background.Render(g_screen,NULL);

    GameMap game_map;
    game_map.LoadMap("map/map01.dat");
    game_map.LoadTiles(g_screen);

    MainObject p_player;
    p_player.LoadImg("img/chay/chay_right_0.png",g_screen);
    p_player.set_clips();

    IncreaseThreat();

    //Time text
    TextObject time_game;
    time_game.SetColor(TextObject::WHITE_TEXT);


    bool is_quit=false;

    int ret_menu = SDLCommonFunc::ShowMenu(g_screen,font_time,0);
    if (ret_menu==1)
    {
        close();
        return 0;
    }
    Uint32 time_pause=SDL_GetTicks();

    g_sound=Mix_LoadWAV("sound.wav");
    g_death_sound=Mix_LoadWAV("DeathSound.wav");
    bool CheckMusic=0;


    while (!is_quit)
    {
        if (CheckMusic==0)
        {
            Mix_PlayChannel(-1,g_sound,0);
            CheckMusic=1;
        }
        fps_timer.start();
        while (SDL_PollEvent(&g_event)!= 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit=true;
            }
            p_player.HandelInputAction(g_event, g_screen);
        }

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen,NULL);
        game_map.DrawMap(g_screen);
        Map map_data = game_map.getMap();

        float main_x=p_player.get_x_pos();
        float main_y=p_player.get_y_pos();

        for (int i=0; i<threats_list.size(); i++)
        {
            ThreatsObject* p_threat = threats_list.at(i);
            if (p_threat!=NULL)
            {
                p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
                p_threat->DoPlayer(map_data,main_x,main_y);
                p_threat->show(g_screen);

                SDL_Rect rect_player = p_player.GetRectFrame();
                SDL_Rect rect_threat = p_threat->GetRectFrame();
                bool bCol2 = SDLCommonFunc::CheckCollision(rect_player,rect_threat);
                if (bCol2==1)
                {
                        Mix_FreeChunk(g_sound);
                        //Mix_HaltMusic();
                        Mix_PlayChannel(-1,g_death_sound,0);
                        SDL_SetRenderDrawColor(g_screen, 0,0,0,255);
                        SDL_RenderClear(g_screen);
                        bool ret=g_youdied.LoadImg("img//died.png",g_screen);
                        g_youdied.SetRect(360,0);
                        g_youdied.Render(g_screen,NULL);
                        time_game.RenderText(g_screen,SCREEN_WIDTH-120,25);


                        int ret_menu = SDLCommonFunc::ShowMenu(g_screen,font_time,1);
                        if (ret_menu==1)
                        {
                            close();
                            return 0;
                        }
                        p_player.isekai();
                        CheckMusic=0;
                        if (CheckMusic==0)
                        {
                            g_sound=Mix_LoadWAV("sound.wav");
                            Mix_PlayChannel(-1,g_sound,0);
                            CheckMusic=1;
                        }
                        time_pause=SDL_GetTicks();
                        threats_list.clear();
                        IncreaseThreat();
                        break;
                }
            }
        }

        //check trung nhau
        SDL_Rect rect_1;
        SDL_Rect rect_2;
        for (int i=0; i<threats_list.size()-1; i++)
            for (int j=i+1; j<threats_list.size(); j++)
            {
                rect_1=threats_list[i]->GetRectFrame();
                rect_2=threats_list[j]->GetRectFrame();
                if (rect_1.x==rect_2.x && rect_1.y==rect_2.y)
                {
                    ThreatsObject* p_threatt = threats_list.at(i);
                    p_threatt->Free();
                }
            }


        p_player.DoPlayer(map_data);
        p_player.Show(g_screen);

        //game time
        std::string str_time = "Time: ";
        Uint32 time_val = (SDL_GetTicks()-time_pause) / 1000;
        std::string str_val = std::to_string(time_val);
        str_time+=str_val;
        time_game.SetText(str_time);
        time_game.LoadFromRenderText(font_time,g_screen);
        time_game.RenderText(g_screen,SCREEN_WIDTH-120,25);

        //increase thread
        int d=time_val/10+1;
        if (threats_list.size()<d) IncreaseThreat();

        SDL_RenderPresent(g_screen);

        int real_imp_time=fps_timer.get_ticks();
        int time_one_frame=1000/FRAME_PER_SECOND;

        if (real_imp_time<time_one_frame)
        {
            int delay_time=time_one_frame-real_imp_time;
            SDL_Delay(delay_time);
        }

    }
    close();
    return 0;
}
