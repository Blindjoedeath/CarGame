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
#include <Utils.hpp>

class Collider{
public:
    enum mode{DYNAMIC, STATIC};
    
private:
    mode curr_mode;
    sf::Vector2f pos;
    sf::IntRect transform;
    static std::vector<Collider *> colliders;
    static int collision_dist;
    bool check_collision(Collider *, Utils::direction & dir);
    bool check_static(Utils::direction &);
    bool check_dynamic(Utils::direction &);
public:
    Collider(sf::Vector2f , sf::IntRect , mode);
    bool is_collided(Utils::direction &);
    sf::Vector2f get_position();
    sf::IntRect get_size();
    void set_position(sf::Vector2f);
};

#endif /* Collider_hpp */
