#ifndef THREATOBJECT_H_INCLUDED
#define THREATOBJECT_H_INCLUDED

#include "CommonFunc.h"
#include "BaseObject.h"
#include <queue>

#define THREATS_SPEED 5
#define THREAT_FRAME_NUM 7
#define DISTANCE 150
class ThreatsObject : public BaseObject
{
public:
    ThreatsObject();
    ~ThreatsObject();

    void set_x_val(const float& xVal) {x_val_=xVal;}
    void set_y_val(const float& yVal) {y_val_=yVal;}
    void set_x_pos(const float& xp) {x_pos_=xp;}
    void set_y_pos(const float& yp) {y_pos_=yp;}

    float get_x_pos() const {return x_pos_;}
    float get_y_pos() const {return y_pos_;}
    void SetMapXY(const int& mp_x, const int& mp_y)
    {
        map_x_=mp_x;
        map_y_=mp_y;
    }
    void set_clips();
    bool LoadImg(std::string path, SDL_Renderer* scree);
    void show(SDL_Renderer* des);
    SDL_Rect GetRectFrame();
    int get_width_frame() const {return width_frame_;}
    int get_height_frame() const {return height_frame_;}
    void DoPlayer(Map& gMap,float a, float b);
    void CheckToMap(Map& gMap);

private:

    int map_x_;
    int map_y_;
    float x_val_;
    float y_val_;
    float x_pos_;
    float y_pos_;
    bool on_ground_;
    int come_back_time_;
    SDL_Rect frame_clip_[THREAT_FRAME_NUM];
    int width_frame_;
    int height_frame_;
    struct nho
    {
        float a,b,m;
        nho(float a_,float b_, float m_)
        {
            a=a_;
            b=b_;
            m=m_;
        }
        nho();
    };
    int frame_;
    std::queue < nho > save;
};


#endif // THREATOBJECT_H_INCLUDED
