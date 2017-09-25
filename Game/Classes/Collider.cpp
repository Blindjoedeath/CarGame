//
//  Collider.cpp
//  Game
//
//  Created by Blind Joe Death on 25.09.17.
//  Copyright © 2017 test. All rights reserved.
//

#include "Collider.hpp"
#include <cmath>


std::vector<Collider*> Collider::colliders;
int Collider::collision_dist = 5;

sf::Vector2f Collider::get_position(){
    return pos;
}

sf::IntRect Collider::get_size(){
    return transform;
}


bool Collider::check_collision(Collider * col, Utils::direction & d){
    
    if (fabsf(col->get_position().x - get_position().x) <= collision_dist ||
        fabsf(col->get_position().y - get_position().y) <= collision_dist){
        if (col->get_position().y - get_position().y <= 0)
            return Utils::direction::FRONT;
        if (col -> get_position().y - get_position().y > 0)
            return Utils::direction::BACK;
        if (col->get_position().x - get_position().x > 0)
            return Utils::direction::RIGHT;
        return Utils::direction::LEFT;
    }
    return false;
}


bool Collider:: check_static(Utils::direction & dir){
    for(auto it = colliders.begin(); it < colliders.end(); ++it){
        if ((*it) -> curr_mode == Collider::mode::STATIC){
            if (check_collision((*it), dir))
                return true;
        }
    }
    return false;
}

bool Collider:: check_dynamic(Utils::direction & dir){
    for(auto it = colliders.begin(); it < colliders.end(); ++it){
        if ((*it) -> curr_mode == Collider::mode::DYNAMIC){
            if (check_collision((*it), dir))
                return true;
        }
    }
    return false;
}

bool Collider:: is_collided(Utils::direction & direction){
    if (curr_mode == Collider::mode::STATIC)
        return check_dynamic(direction);
    else return (check_dynamic(direction) || check_static(direction));
}


Collider::Collider(sf::Vector2f position, sf::IntRect size, mode mode){
    pos = position;
    transform = size;
    curr_mode = mode;
    colliders.push_back(this);
}
