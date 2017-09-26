//
//  MovableObject.cpp
//  Game
//
//  Created by Blind Joe Death on 19.09.17.
//  Copyright © 2017 test. All rights reserved.
//

#include "MovableObject.hpp"
#include <cmath>
#include <iostream>


float MovableObject::x_limit_accel = 0.003;
float MovableObject::y_limit_accel = 0.005;
float MovableObject::x_accel_step = 0.0003;
float MovableObject::y_accel_step = 0.0005;
float MovableObject::x_limit_speed = 0.3;
float MovableObject::y_limit_speed = 0.8;
float MovableObject::x_friction = 0.00025;
float MovableObject::y_friction = 0.00045;
float MovableObject::y_min_for_x = 0.3;
float MovableObject::collision_koeff = 0.6;

void MovableObject::set_x_block(bool b){
    x_move_blocked = b;
}

float MovableObject::get_x_speed(){
    return x_curr_speed;
}

float MovableObject::get_y_speed(){
    return y_curr_speed;
}

float MovableObject::get_x_accel(){
    return x_curr_accel;
}

float MovableObject::get_y_accel(){
    return y_curr_accel;
}

void MovableObject::set_x_speed(float x_speed){
    x_curr_speed = x_speed;
}

void MovableObject::set_y_speed(float y_speed){
    y_curr_speed = y_speed;
}
void MovableObject::set_x_accel(float x_accel){
    x_curr_accel = x_accel;
}
void MovableObject::set_y_accel(float y_accel){
    y_curr_accel = y_accel;
}
MovableObject::MovableObject (const char * fileName, sf::IntRect size, sf::Vector2f pos, int layout)
: GameObject(fileName, size, pos, layout){
    x_curr_speed = y_curr_speed = 0;
    x_curr_accel = y_curr_accel = 0;
}

void MovableObject::move(){
    
    if (x_curr_speed > 0){
        x_curr_accel -= x_friction;
        if (x_curr_speed + x_curr_accel <= 0){
            x_curr_speed = 0;
            x_curr_accel = 0;
        }
    }
    else if (x_curr_speed < 0){
        x_curr_accel += x_friction;
        if (x_curr_speed + x_curr_accel >= 0){
            x_curr_speed = 0;
            x_curr_accel = 0;
        }
    }
    if (y_curr_speed > 0){
        y_curr_accel -= y_friction;
        if (y_curr_speed + y_curr_accel <= 0){
            y_curr_speed = 0;
            y_curr_accel = 0;
        }
    }
    else if (y_curr_speed < 0){
        y_curr_accel += y_friction;
        if (y_curr_speed + y_curr_accel >= 0){
            y_curr_speed = 0;
            y_curr_accel = 0;
        }
    }
    if ((x_curr_speed + x_curr_accel < x_limit_speed && x_curr_speed >= 0)||
        (x_curr_speed + x_curr_accel > -x_limit_speed && x_curr_speed < 0))
        x_curr_speed += x_curr_accel;
    else{
        if (x_curr_speed > 0)
            x_curr_speed = x_limit_speed;
        else if (x_curr_speed < 0)
            x_curr_speed = -x_limit_speed;
    }
    if ((y_curr_speed + y_curr_accel < y_limit_speed && y_curr_speed >= 0)||
        (y_curr_speed + y_curr_accel > -y_limit_speed && y_curr_speed < 0))
        y_curr_speed += y_curr_accel;
    else{
        if (y_curr_speed > 0)
            y_curr_speed = y_limit_speed;
        else if (y_curr_speed < 0)
            y_curr_speed = -y_limit_speed;
    }

    if (((y_curr_speed > 0 && y_curr_speed < y_min_for_x)||
        (y_curr_speed < 0 && y_curr_speed > -y_min_for_x)|| y_curr_speed == 0) && x_move_blocked){
        x_curr_speed = x_curr_accel = 0;
    }
    set_position(sf::Vector2f(get_position().x + x_curr_speed,get_position().y - y_curr_speed));
}

void MovableObject::add_acceleration(Utils::direction dir)
{
    switch (dir) {
        case Utils::direction::FRONT:
            if (y_curr_accel + y_accel_step <= y_limit_accel)
                y_curr_accel += y_accel_step;
            break;
            
        case Utils::direction::BACK:
            if (y_curr_accel - y_accel_step >= -y_limit_accel)
                y_curr_accel -= y_accel_step;
        
            break;
        case Utils::direction::LEFT:
            if (x_curr_accel - x_accel_step >= -x_limit_accel)
                x_curr_accel -= x_accel_step;
            break;
            
        case Utils::direction::RIGHT:
            if (x_curr_accel + x_accel_step <= x_limit_accel)
                x_curr_accel += x_accel_step;
            break;
    }
}

void MovableObject::collide(Utils::direction dir){
    if (dir == Utils::direction::BACK || dir == Utils::direction::FRONT){
        y_curr_accel = -y_curr_accel * collision_koeff;
        y_curr_speed = -y_curr_speed * collision_koeff;
    }
    else{
        x_curr_accel = -x_curr_accel * collision_koeff;
        x_curr_speed = -x_curr_speed * collision_koeff;
    }
}
