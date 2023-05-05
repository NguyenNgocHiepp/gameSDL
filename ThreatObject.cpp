#include "ThreatObject.h"
#include <bits/stdc++.h>

using namespace std;

ThreatsObject::ThreatsObject()
{
    width_frame_=0;
    height_frame_=0;
    x_val_=0.0;
    y_val_=0.0;
    x_pos_=0.0;
    y_pos_=0.0;
    on_ground_=0;// 888888888*****************************************
    come_back_time_=0;
    frame_=0;
}
ThreatsObject::~ThreatsObject()
{

}
SDL_Rect ThreatsObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x=rect_.x;
    rect.y=rect_.y;
    rect.w=width_frame_;
    rect.h=height_frame_;
    return rect;
}
bool ThreatsObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret= BaseObject::LoadImg(path,screen);
    if (ret)
    {
        width_frame_=rect_.w/THREAT_FRAME_NUM;
        height_frame_=rect_.h;
    }
    return ret;
}
void ThreatsObject::set_clips()
{
    if (width_frame_>0 && height_frame_>0)
    {
        frame_clip_[0].x=0;
        frame_clip_[0].y=0;
        frame_clip_[0].w=width_frame_;
        frame_clip_[0].h=height_frame_;

        frame_clip_[1].x=width_frame_*1;
        frame_clip_[1].y=0;
        frame_clip_[1].w=width_frame_;
        frame_clip_[1].h=height_frame_;

        frame_clip_[2].x=width_frame_*2;
        frame_clip_[2].y=0;
        frame_clip_[2].w=width_frame_;
        frame_clip_[2].h=height_frame_;

        frame_clip_[3].x=width_frame_*3;
        frame_clip_[3].y=0;
        frame_clip_[3].w=width_frame_;
        frame_clip_[3].h=height_frame_;

        frame_clip_[4].x=width_frame_*4;
        frame_clip_[4].y=0;
        frame_clip_[4].w=width_frame_;
        frame_clip_[4].h=height_frame_;

        frame_clip_[5].x=width_frame_*5;
        frame_clip_[5].y=0;
        frame_clip_[5].w=width_frame_;
        frame_clip_[5].h=height_frame_;

        frame_clip_[6].x=width_frame_*6;
        frame_clip_[6].y=0;
        frame_clip_[6].w=width_frame_;
        frame_clip_[6].h=height_frame_;
    }
}

void ThreatsObject::show(SDL_Renderer* des)
{
    if (come_back_time_==0)
    {
        rect_.x=x_pos_-map_x_;
        rect_.y=y_pos_-map_y_;
        frame_++;
        if (frame_>6) frame_=0;
        SDL_Rect* currentClip = &frame_clip_[frame_];
        SDL_Rect rendQuad = {rect_.x,rect_.y,width_frame_,height_frame_};
        SDL_RenderCopy(des,p_object_,currentClip,&rendQuad);
    }
}

void ThreatsObject::DoPlayer(Map& gMap, float main_x, float main_y)
{
    if (come_back_time_==0)
    {
        float c=sqrt((main_x-x_pos_)*(main_x-x_pos_)+(main_y-y_pos_)*(main_y-y_pos_));
        if (c>DISTANCE)
        {
             float a=(main_y- y_pos_)/(main_x- x_pos_);
             float b=(main_y-a*main_x);
             float m=0;
           if (x_pos_<main_x)
               {
                    float l=0,r=THREATS_SPEED;
                    float yy=0,kc=0;m=0;
                    while (fabs(r-l)>0.0001)
                    {
                        m=(l+r)/2;
                        yy=a*(x_pos_+m)+b;
                        kc=sqrt(m*m+(yy-y_pos_)*(yy-y_pos_));
                        if (kc<THREATS_SPEED) l=m;
                          else if (kc>THREATS_SPEED) r=m; else
                        {
                            break;
                        }
                    }
                    x_pos_+=m;
                    y_pos_=a*(x_pos_)+b;
               } else
               {
                   float l=-THREATS_SPEED;
                    float yy=0,kc=0,r=0;m=0;
                    while (fabs(r-l)>0.0001)
                    {
                        m=(l+r)/2;
                        yy=a*(x_pos_+m)+b;
                        kc=sqrt(m*m+(yy-y_pos_)*(yy-y_pos_));
                        if (kc<THREATS_SPEED) r=m;
                          else if (kc>THREATS_SPEED) l=m; else
                        {
                            break;
                        }
                    }
                    x_pos_+=m;
                    y_pos_=a*(x_pos_)+b;
               }
               save.push(nho(a,b,m));
               if (save.size()>2) save.pop();

        } else
        {
            nho abm=save.front();
            x_pos_+=abm.m;
            y_pos_=abm.a*(x_pos_)+abm.b;
        }

    }
}
