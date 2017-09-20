//
//  MovableObject.cpp
//  Game
//
//  Created by Blind Joe Death on 19.09.17.
//  Copyright © 2017 test. All rights reserved.
//

#include "MovableObject.hpp"
#include <cmath>


float MovableObject :: x_limit_speed = 5;
float MovableObject :: x_incr_step = 1;
float MovableObject :: y_limit_speed = 3;
float MovableObject :: y_incr_step = 0.5;

MovableObject::MovableObject (const char * fileName, sf::IntRect size, sf::Vector2f pos, int layout)
: GameObject(fileName, size, pos, layout){
    x_curr_obj_speed = y_curr_obj_speed = 0;
}

void MovableObject::move(direction dir)
{
    switch (dir) {
        case direction::FRONT:{
            if (y_curr_obj_speed + y_incr_step <= y_limit_speed)
                y_curr_obj_speed += y_incr_step;
            sprite.setPosition(get_position().x + y_curr_obj_speed, get_position().y);
        }
            break;
        case direction::BACK:{
            if (abs(y_curr_obj_speed - y_incr_step) <= y_limit_speed)
                y_curr_obj_speed -= y_incr_step;
            sprite.setPosition(get_position().x + y_curr_obj_speed, get_position().y);
        }
            break;
        case direction::LEFT:{
            if (abs(x_curr_obj_speed - x_incr_step) <= x_limit_speed)
                x_curr_obj_speed -= x_incr_step;
            sprite.setPosition(get_position().x + x_curr_obj_speed, get_position().y);
        }
            break;
        case direction::RIGHT:{
            if (x_curr_obj_speed + x_incr_step <= x_limit_speed)
                x_curr_obj_speed += x_incr_step;
            sprite.setPosition(get_position().x + x_curr_obj_speed, get_position().y);
        }
            break;
    }
}

void MovableObject::on_collision(direction dir)
{
    switch (dir) {
        case direction::FRONT:{
            y_curr_obj_speed = -(y_curr_obj_speed * 0.2);
        }
            break;
        case direction::BACK:{
            y_curr_obj_speed = -(y_curr_obj_speed * 0.2);
        }
            break;
        case direction::LEFT:{
            x_curr_obj_speed = -(x_curr_obj_speed * 0.2);
        }
            break;
        case direction::RIGHT:{
            x_curr_obj_speed = -(x_curr_obj_speed * 0.2);
        }
            break;
    }
}
