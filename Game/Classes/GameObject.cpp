//
//  GameObject.cpp
//  Game
//
//  Created by Blind Joe Death on 19.09.17.
//  Copyright © 2017 test. All rights reserved.
//

#include "GameObject.hpp"
#include "ResourcePath.hpp"

GameObject::GameObject (const char fileName, sf::IntRect transform, int layer_num){
    layer = layer_num;
    sf::Texture texture;
    texture.loadFromFile(resourcePath() + fileName);
    sprite.setTexture(texture);
    sprite.setTextureRect(transform);
}

int GameObject::get_layer(){
    return layer;
}

sf::Sprite GameObject::get_sprite(){
    return sprite;
}

sf::Vector2f GameObject::get_position(){
    return position;
}

sf::IntRect GameObject::get_size(){
    return size;
}

void GameObject::set_position(sf::Vector2f pos){
    position = pos;
}
