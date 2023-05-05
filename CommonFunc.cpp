#include "CommonFunc.h"
#include <iostream>

bool SDLCommonFunc::CheckFocusWithRect(const int &x, const int &y, const SDL_Rect& rect)
{
    if (rect.x<=x && x<=rect.x+rect.w &&
        rect.y<=y && y<=rect.y+rect.h) return true;
    return false;
}


int SDLCommonFunc::ShowMenu(SDL_Renderer* des,TTF_Font* font,bool kt)
{
    //g_img_menu = loadSurface("img//start_img.png");
    //if (g_img_menu==NULL) return 1;
    if (!kt)
    {
        BaseObject parkourBoy;
        bool ret=parkourBoy.LoadImg("img//parkourboy.png",des);
        parkourBoy.SetRect(400,60);
        parkourBoy.Render(des,NULL);

        BaseObject boy;
        ret=boy.LoadImg("img//boy.png",des);
        boy.SetRect(70,60);
        boy.Render(des,NULL);

        BaseObject boy1;
        ret=boy1.LoadImg("img//boy1.png",des);
        boy1.SetRect(850,60);
        boy1.Render(des,NULL);
    }

    const int kMenuItemNum = 2;
    SDL_Rect pos_arr[kMenuItemNum];
    pos_arr[0].x=565;
    pos_arr[0].y=400;
    pos_arr[0].w=105;
    pos_arr[0].h=35;

    pos_arr[1].x=600;
    pos_arr[1].y=450;
    pos_arr[1].w=40;
    pos_arr[1].h=35;

    TextObject text_menu[kMenuItemNum];

    text_menu[0].SetText("play game");
    text_menu[0].SetColor(TextObject::WHITE_TEXT);

    text_menu[1].SetText("exit");
    text_menu[1].SetColor(TextObject::WHITE_TEXT);
    //text_menu[1].LoadFromRenderText(font,des);

    bool selected[kMenuItemNum] = {0,0};
    SDL_Event m_event;
    int xm=0,ym=0;
    while(true)
    {
        while (SDL_PollEvent(&m_event))
        {
            switch (m_event.type)
            {
            case SDL_QUIT:
                return 1;
            case SDL_MOUSEMOTION:
                {
                    xm=m_event.motion.x;
                    ym=m_event.motion.y;
                    for (int i=0;i<kMenuItemNum;i++)
                    {
                        if (CheckFocusWithRect(xm,ym,pos_arr[i]))
                        {
                            if (selected[i] == 0)
                            {
                               selected[i] =1;
                               text_menu[i].SetColor(TextObject::RED_TEXT);
                            }
                        } else
                        {
                            if (selected[i]==1)
                            {
                                selected[i] =0;
                               text_menu[i].SetColor(TextObject::WHITE_TEXT);
                            }
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                {
                    xm=m_event.motion.x;
                    ym=m_event.motion.y;
                    for (int i=0;i<kMenuItemNum;i++)
                    {
                        if (CheckFocusWithRect(xm,ym,pos_arr[i]))
                        {
                            return i;
                        }
                    }
                }
            default:
                break;
            }
        }

        //SDL_SetRenderDrawColor(des, 0, 0, 0, 255);
        //SDL_RenderClear(des);


        text_menu[0].LoadFromRenderText(font,des);
        text_menu[0].RenderText(des,pos_arr[0].x,pos_arr[0].y);
        text_menu[1].LoadFromRenderText(font,des);
        text_menu[1].RenderText(des,pos_arr[1].x,pos_arr[1].y);

        SDL_RenderPresent(des);
    }
    return 1;

}

bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
  int left_a = object1.x;
  int right_a = object1.x + object1.w;
  int top_a = object1.y;
  int bottom_a = object1.y + object1.h;

  int left_b = object2.x;
  int right_b = object2.x + object2.w;
  int top_b = object2.y;
  int bottom_b = object2.y + object2.h;

  // Case 1: size object 1 < size object 2
  if (left_a > left_b && left_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }

  if (left_a > left_b && left_a < (right_b+10))
  {
    if (bottom_a > (top_b+10) && bottom_a < bottom_b)
    {
      return true;
    }
  }

  if (right_a > left_b && right_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }

  if (right_a > (left_b+10) && right_a < right_b)
  {
    if (bottom_a > (top_b+10) && bottom_a < bottom_b)
    {

      return true;
    }
  }

  // Case 2: size object 1 < size object 2
  if (left_b > left_a && left_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }

  if (left_b > left_a && left_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }

  if (right_b > left_a && right_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }

  if (right_b > left_a && right_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }

   // Case 3: size object 1 = size object 2
  if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
  {
    return true;
  }

  return false;
}
