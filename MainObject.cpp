#include "MainObject.h"


MainObject::MainObject()
{
    frame_=0;
    x_pos_=0;
    y_pos_=0;
    x_val_=0;
    y_val_=0;
    width_frame_=0;
    height_frame_=0;
    status_=WALK_RIGHT;
    input_type_.down_=0;
    input_type_.up_=0;
    input_type_.left_=0;
    input_type_.right_=0;
    input_type_.jump_=0;
    input_type_.jump_1=0;
    input_type_.jump_2=0;
    input_type_.jump_3=0;
    on_ground_=false;
}
void MainObject::isekai()
{
    frame_=0;
    x_pos_=0;
    y_pos_=0;
    x_val_=0;
    y_val_=0;
    status_=WALK_RIGHT;
    input_type_.down_=0;
    input_type_.up_=0;
    input_type_.left_=0;
    input_type_.right_=0;
    input_type_.jump_=0;
    input_type_.jump_1=0;
    input_type_.jump_2=0;
    input_type_.jump_3=0;
    on_ground_=false;
}
MainObject::~MainObject()
{

}

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret=BaseObject::LoadImg(path,screen);
    if (ret==true)
    {
        width_frame_=rect_.w;
        height_frame_=rect_.h;
    }
    return ret;
}
SDL_Rect MainObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x=rect_.x;
    rect.y=rect_.y;
    rect.w=width_frame_;
    rect.h=height_frame_;
    return rect;
}

void MainObject::set_clips()
{
    if (width_frame_>0 && height_frame_>0)
    {
        frame_clip_[0].x=0;
        frame_clip_[0].y=0;
        frame_clip_[0].w=width_frame_;
        frame_clip_[0].h=height_frame_;
    }
}
void MainObject::Show(SDL_Renderer* des)
{
    std::string s="img/";
    if (on_ground_==true)
    {
        if (status_==WALK_LEFT)
        {
            if (input_type_.left_==0)
            {
                s+="dung/dung_left_";
                s+=char(frame_+48);
                s+=".png";
                LoadImg(s,des);
                frame_++;
                if (frame_ >=9) frame_=0;
            } else
            {
                s+="chay/chay_left_";
                s+=char(frame_+48);
                s+=".png";
                LoadImg(s,des);
                frame_++;
                if (frame_ >=8) frame_=0;
            }
        } else
        {
            if (input_type_.right_==0)
            {
                s+="dung/dung_right_";
                s+=char(frame_+48);
                s+=".png";
                LoadImg(s,des);
                frame_++;
                if (frame_ >=9) frame_=0;
            } else
            {
                s+="chay/chay_right_";
                s+=char(frame_+48);
                s+=".png";
                LoadImg(s,des);
                frame_++;
                if (frame_ >=8) frame_=0;
            }
        }
    } else if (on_ground_ == false)
    {
        if (input_type_.jump_1)
        {
            s+="nhay_1/";
            int khoang_cach=(PLAYER_JUMP_VAL*2)/5;
            if (status_ == WALK_RIGHT) s+="nhay_1_right_"; else
            s+="nhay_1_left_";
            {
                if (y_val_<(-PLAYER_JUMP_VAL + khoang_cach-8)) LoadImg(s+"0.png",des); else
                if (y_val_<(-PLAYER_JUMP_VAL + 2*khoang_cach-13)) LoadImg(s+"1.png",des); else
                if (y_val_<(-PLAYER_JUMP_VAL + 3*khoang_cach)) LoadImg(s+"2.png",des); else
                if (y_val_<(-PLAYER_JUMP_VAL + 4*khoang_cach+8)) LoadImg(s+"3.png",des); else
                if (y_val_<=(-PLAYER_JUMP_VAL + 5*khoang_cach)) LoadImg(s+"4.png",des);
            }
        } else if (input_type_.jump_2)
        {
            s+="nhay_2/";
            int khoang_cach=(PLAYER_JUMP_VAL*2)/6;
            if (status_ == WALK_RIGHT)
            {
                s+="nhay_2_right_";
                if (y_val_<(-PLAYER_JUMP_VAL + khoang_cach-4)) LoadImg(s+"0.png",des); else
                if (y_val_<(-PLAYER_JUMP_VAL + 2*khoang_cach-3)) LoadImg(s+"1.png",des); else
                if (y_val_<(-PLAYER_JUMP_VAL + 3*khoang_cach)) LoadImg(s+"2.png",des); else
                if (y_val_<(-PLAYER_JUMP_VAL + 4*khoang_cach)) LoadImg(s+"3.png",des); else
                if (y_val_<(-PLAYER_JUMP_VAL + 5*khoang_cach)) LoadImg(s+"4.png",des); else
                if (y_val_<=(-PLAYER_JUMP_VAL + 6*khoang_cach)) LoadImg(s+"5.png",des);
            } else
            {
                s+="nhay_2_left_";
                if (y_val_<(-PLAYER_JUMP_VAL + khoang_cach-4)) LoadImg(s+"0.png",des); else
                if (y_val_<(-PLAYER_JUMP_VAL + 2*khoang_cach-3)) LoadImg(s+"1.png",des); else
                if (y_val_<(-PLAYER_JUMP_VAL + 3*khoang_cach)) {x_pos_-= 2;LoadImg(s+"2.png",des);} else
                if (y_val_<(-PLAYER_JUMP_VAL + 4*khoang_cach)) {x_pos_+= 2.6;LoadImg(s+"3.png",des);} else
                if (y_val_<(-PLAYER_JUMP_VAL + 5*khoang_cach))  LoadImg(s+"4.png",des); else
                if (y_val_<=(-PLAYER_JUMP_VAL + 6*khoang_cach)) LoadImg(s+"5.png",des);
            }
        } else if (input_type_.jump_3)
        {
            s+="nhay_3/";
            int khoang_cach=(PLAYER_JUMP_VAL*2)/6;
            if (status_ == WALK_RIGHT) s+="nhay_3_right_"; else
            s+="nhay_3_left_";
            {
                if (y_val_<(-PLAYER_JUMP_VAL + khoang_cach)) LoadImg(s+"0.png",des); else
                if (y_val_<(-PLAYER_JUMP_VAL + 2*khoang_cach)) LoadImg(s+"1.png",des); else
                if (y_val_<(-PLAYER_JUMP_VAL + 3*khoang_cach)) LoadImg(s+"2.png",des); else
                if (y_val_<(-PLAYER_JUMP_VAL + 4*khoang_cach)) LoadImg(s+"3.png",des); else
                if (y_val_<(-PLAYER_JUMP_VAL + 5*khoang_cach))  LoadImg(s+"4.png",des); else
                if (y_val_<=(-PLAYER_JUMP_VAL + 6*khoang_cach)) LoadImg(s+"5.png",des);
            }
        }
    }

    //print picture
    set_clips();
    rect_.x=x_pos_;
    rect_.y=y_pos_;

    SDL_Rect* current_clip= &frame_clip_[0];

    SDL_Rect renderQuad={rect_.x, rect_.y, width_frame_, height_frame_};

    SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
}

void MainObject::HandelInputAction(SDL_Event events, SDL_Renderer* screen)
{
    if (events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                status_=WALK_RIGHT;
                input_type_.right_=1;
                input_type_.left_=0;
            }
            break;
        case SDLK_LEFT:
            {
                status_=WALK_LEFT;
                input_type_.left_=1;
                input_type_.right_=0;
            }
            break;
        case SDLK_UP:
            {
                if (input_type_.jump_2==1) break;
                if (input_type_.jump_3==1) break;
                input_type_.jump_=1;
                input_type_.jump_1=1;
                input_type_.jump_2=0;
                input_type_.jump_3=0;
            }
            break;
        case SDLK_2:
            {
                if (input_type_.jump_1==1) break;
                if (input_type_.jump_3==1) break;
                input_type_.jump_=1;
                input_type_.jump_1=0;
                input_type_.jump_2=1;
                input_type_.jump_3=0;
            }
            break;
        case SDLK_3:
            {
                if (input_type_.jump_1==1) break;
                if (input_type_.jump_2==1) break;
                input_type_.jump_=1;
                input_type_.jump_1=0;
                input_type_.jump_2=0;
                input_type_.jump_3=1;
            }
            break;
        }
    } else if (events.type==SDL_KEYUP)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                input_type_.right_=0;
            }
            break;
        case SDLK_LEFT:
            {
                input_type_.left_=0;
            }
            break;
        }


    }

   /* if (events.type == SDL_MOUSEBUTTONDOWN)
    {
        if (events.button.button==SDL_BUTTON_RIGHT)
        {
            input_type_.jump_=1;
        }
    }*/
}

void MainObject::DoPlayer(Map& map_data)
{
    x_val_=0;
    y_val_+=GRAVITY_SPEED;

    //if (y_val_>=MAX_FALL_SPEED) y_val_=MAX_FALL_SPEED;

    if (input_type_.left_==1)
    {
        x_val_-=PLAYER_SPEED;
    } else
    if (input_type_.right_==1)
    {
        x_val_+=PLAYER_SPEED;
    }
    if (input_type_.jump_==1)
    {
        if (on_ground_== true)
        {
            y_val_= - PLAYER_JUMP_VAL;
            on_ground_=false;
        }

        input_type_.jump_=0;
    }

    CheckToMap(map_data);
}

void MainObject::CheckToMap(Map& map_data)
{
    int x1=0;
    int x2=0;
    int y1=0;
    int y2=0;
    //check horizontal
    int height_min=height_frame_<TILE_SIZE ? height_frame_ : TILE_SIZE;

    x1=(x_pos_+ x_val_)/TILE_SIZE;
    x2=(x_pos_+ x_val_+width_frame_ - 1)/TILE_SIZE;

    y1=(y_pos_)/TILE_SIZE;
    y2=(y_pos_ + height_min-1)/TILE_SIZE;

    if (x1>=0 && x2<MAX_MAP_X && y1>=0 && y2<MAX_MAP_Y)
    {
        if (x_val_>0) //moving to right
        {
            if (map_data.tile[y1][x2]!= BLANK_TILE || map_data.tile[y2][x2]!= BLANK_TILE)
            {
                x_pos_=x2*TILE_SIZE;
                x_pos_-=width_frame_+1;
                x_val_=0;
            }
        } else if (x_val_<0)
        {
            if (map_data.tile[y1][x1]!= BLANK_TILE || map_data.tile[y2][x1]!= BLANK_TILE)
            {
                x_pos_=(x1+1)*TILE_SIZE;
                x_val_=0;
            }
        }

    }


    int width_min=width_frame_<TILE_SIZE ? width_frame_ : TILE_SIZE;

    x1=(x_pos_+15)/TILE_SIZE;
    x2=(x_pos_+ width_min-15)/TILE_SIZE;

    y1=(y_pos_+y_val_)/TILE_SIZE;
    y2=(y_pos_ + y_val_+ height_frame_-1)/TILE_SIZE;

    if (x1>=0 && x2<MAX_MAP_X && y1>=0 && y2<MAX_MAP_Y)
    {
        if (y_val_>0) //moving down
        {
            if (map_data.tile[y2][x1]!= BLANK_TILE || map_data.tile[y2][x2]!= BLANK_TILE)
            {
                y_pos_=y2*TILE_SIZE;
                y_pos_-=(height_frame_);/////////////////////////////////////////////////////////////////////
                y_val_=0;
                on_ground_=true;
                input_type_.jump_1=0;
                input_type_.jump_2=0;
                input_type_.jump_3=0;
            } else on_ground_=false;
        } else if (y_val_<0)
        {
            if (map_data.tile[y1][x1]!= BLANK_TILE || map_data.tile[y1][x2]!= BLANK_TILE)
            {
                y_pos_=(y1+1)*TILE_SIZE;
                y_val_=0;
            }
        }
    }

    x_pos_+=x_val_;
    y_pos_+=y_val_;

    if (x_pos_<0) x_pos_=0; else
    if (x_pos_+width_frame_>map_data.max_x_)
      x_pos_=map_data.max_x_-width_frame_-1;
}
void MainObject::UpdateImagePlayer(SDL_Renderer* des)
{

}



