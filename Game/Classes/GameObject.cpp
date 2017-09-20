//
//  GameObject.cpp
//  Game
//
//  Created by Blind Joe Death on 19.09.17.
//  Copyright © 2017 test. All rights reserved.
//

#include "GameObject.hpp"
#include "ResourcePath.hpp"
std::vector<GameObject*> GameObject::all_objects;
int GameObject::all_objects_count = 0;

GameObject::GameObject (const char * fileName, sf::IntRect transform, sf::Vector2f position, int layer_num){
    layer = layer_num;
    texture = new sf::Texture();
    sprite = new sf::Sprite();
    (*texture).loadFromFile(resourcePath() + fileName);
    (*sprite).setTexture(*texture);
    (*sprite).setScale((float)transform.width / (float)(*texture).getSize().x,
                    (float)transform.height / (float)(*texture).getSize().y );
    child_count = 0;
    ++all_objects_count;
    all_objects.push_back(this);
}

GameObject::~GameObject(){
    (*sprite).~Sprite();
    (*texture).~Texture();
}

int GameObject::get_layer(){
    return layer;
}

sf::Sprite * GameObject::get_sprite(){
    return sprite;
}

sf::Vector2f GameObject::get_position(){
    return (*sprite).getPosition();
}

sf::IntRect GameObject::get_size(){
    return (*sprite).getTextureRect();
}

void GameObject::set_position(sf::Vector2f pos){
    sf::Vector2f buffer;
    buffer = pos - (*sprite).getPosition();
    (*sprite).setPosition(pos.x, pos.y);
    for (int i = 0; i < child_count; ++i){
        children[i]->set_position(children[i]->get_position() + buffer);
    }
}

GameObject* GameObject::get_child(int pos){
    if (0 <= pos && pos < child_count){
        ++child_count;
        return children[pos];
    }
    return;
}

void GameObject::add_child(GameObject * obj){
    child_count++;
    children.push_back(obj);
}
