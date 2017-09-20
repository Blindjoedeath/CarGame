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
    
    protected :
    int layer;
    sf::Sprite * sprite;
    sf::Texture* texture;
    std::vector<GameObject*> children;
    
    public :
    static int all_objects_count;
    static std::vector<GameObject*> all_objects;
    static float distanse(GameObject *, GameObject *);
    GameObject(const char *, sf::IntRect, sf::Vector2f, int);
    ~GameObject();
    int get_layer();
    sf::Sprite * get_sprite();
    sf::Vector2f get_position();
    sf::IntRect get_size();
    void set_position(sf::Vector2f);
    int child_count;
    GameObject* get_child(int pos);
    void add_child(GameObject* obj);
};
#endif /* GameObject_hpp */
