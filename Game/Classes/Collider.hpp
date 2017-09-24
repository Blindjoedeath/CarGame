//
//  Collider.hpp
//  Game
//
//  Created by Blind Joe Death on 25.09.17.
//  Copyright © 2017 test. All rights reserved.
//

#ifndef Collider_hpp
#define Collider_hpp

#include <stdio.h>
#include "SFML/Graphics.hpp"
#include <MovableObject.hpp>

class Collider{
public:
    enum mode{DYNAMIC, STATIC};
    
private:
    mode curr_mode;
    sf::Vector2f pos;
    sf::IntRect transform;
    static std::vector<Collider *> colliders;
    static int collision_dist;
    bool check_collision(Collider *, MovableObject::direction &);
    bool check_static(MovableObject::direction &);
    bool check_dynamic(MovableObject::direction &);
public:
    Collider(sf::Vector2f, sf::IntRect, mode);
    bool is_collided(MovableObject::direction &);
    sf::Vector2f get_position();
    sf::IntRect get_size();
};

#endif /* Collider_hpp */
