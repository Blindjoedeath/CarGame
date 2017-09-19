//
//  GameObject.hpp
//  Game
//
//  Created by Blind Joe Death on 19.09.17.
//  Copyright © 2017 test. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class GameObject{
    
    private :
    int layer;
    sf::Sprite sprite;
    sf::Vector2f position;
    sf::IntRect size;
    
    public :
    GameObject(const char, sf::IntRect, int);
    int get_layer();
    sf::Sprite get_sprite();
    sf::Vector2f get_position();
    sf::IntRect get_size();
    void set_position(sf::Vector2f);
};
#endif /* GameObject_hpp */
