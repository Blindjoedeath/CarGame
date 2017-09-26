//
//  Collider.cpp
//  Game
//
//  Created by Blind Joe Death on 25.09.17.
//  Copyright © 2017 test. All rights reserved.
//

#include "Collider.hpp"
#include <cmath>
#include <iostream>


std::vector<Collider*> Collider::colliders;
int Collider::collision_dist = 2;

sf::Vector2f Collider::get_position(){
    return pos;
}

sf::IntRect Collider::get_size(){
    return transform;
}

void Collider::set_position(sf::Vector2f position){
    pos.x = position.x;
    pos.y = position.y;
}


bool Collider::check_collision(Collider * col, Utils::direction & d){
    if (col != this)
    {
        if ((get_position().y - (col->get_position().y + col->get_size().height) <= collision_dist) &&
            get_position().y - (col->get_position().y + col->get_size().height) > 0 &&
            get_position().x >= (col ->get_position().x - get_size().width) &&
            get_position().x <= col->get_position().x + col->get_size().width){
            d = Utils::direction::FRONT;
            std::cout <<"BAM";
            return true;
        }
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
