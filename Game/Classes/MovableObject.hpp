//
//  MovableObject.hpp
//  Game
//
//  Created by Blind Joe Death on 19.09.17.
//  Copyright © 2017 test. All rights reserved.
//

#ifndef MovableObject_hpp
#define MovableObject_hpp

#include <stdio.h>
#include "GameObject.hpp"
#include <Utils.hpp>

class MovableObject : public GameObject{
    private :
    static float x_limit_accel;
    static float y_limit_accel;
    static float x_accel_step;
    static float y_accel_step;
    static float x_limit_speed;
    static float y_limit_speed;
    static float x_friction;
    static float y_friction;
    static float y_min_for_x;
    static float collision_koeff;
    float x_curr_accel;
    float y_curr_accel;
    float x_curr_speed;
    float y_curr_speed;
    bool x_move_blocked;
    int upp_bound;
    int low_bound;
    int get_sign(float f);
    
    public :
    MovableObject(const char *, sf::IntRect, sf::Vector2f, int);
    void move();
    void add_acceleration(Utils::direction);
    void set_x_block(bool);
    void set_x_speed(float);
    void set_y_speed(float);
    void set_x_accel(float);
    void set_y_accel(float);
    float get_x_speed();
    float get_y_speed();
    float get_x_accel();
    float get_y_accel();
    void collide(Utils::direction);
};

#endif /* MovableObject_hpp */
