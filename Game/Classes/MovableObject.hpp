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

class MovableObject : public GameObject{
    
    private :
    static float x_limit_speed;
    static float y_limit_speed;
    static float x_incr_step;
    static float y_incr_step;
    float x_curr_obj_speed;
    float y_curr_obj_speed;
    
    public :
    static enum direction{FRONT, BACK, RIGHT, LEFT};
    MovableObject(const char *, sf::IntRect, sf::Vector2f, int);
    void move(direction);
    void on_collision(direction);
};

#endif /* MovableObject_hpp */
