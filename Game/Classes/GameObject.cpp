//
//  GameObject.cpp
//  Game
//
//  Created by Blind Joe Death on 19.09.17.
//  Copyright © 2017 test. All rights reserved.
//

#include "GameObject.hpp"
#include "ResourcePath.hpp"
#include <iostream>

std::vector<GameObject*> GameObject::all_objects;

GameObject::GameObject (const char * fileName, sf::IntRect transform, sf::Vector2f position, int layer_num){
    layer = layer_num;
    texture = new sf::Texture();
    sprite = new sf::Sprite();
    (*texture).loadFromFile(resourcePath() + fileName);
    (*sprite).setTexture(*texture);
    (*sprite).setScale((float)transform.width / (float)(*texture).getSize().x,
                    (float)transform.height / (float)(*texture).getSize().y );
    (*sprite).setPosition(position);
    size = transform;
    child_count = 0;
    all_objects.push_back(this);
    curr_coll = NULL;
}

GameObject::~GameObject(){
    (*sprite).~Sprite();
    (*texture).~Texture();
    if (curr_coll != 0)
        delete curr_coll;
    for (auto it = all_objects.begin(); it < all_objects.end(); ++it){
        if (*it == this)
            all_objects.erase(it);
    }
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
    return size;
}

void GameObject::set_position(sf::Vector2f pos){
    sf::Vector2f differ;
    differ = pos - (*sprite).getPosition();
    (*sprite).setPosition(pos);
    if (curr_coll != NULL){
        curr_coll -> set_position(curr_coll->get_position() + differ);
    }
    for (int i = 0; i < children.size(); ++i){
        children[i]->set_position(children[i]->get_position() + differ);
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

Collider* GameObject::add_collider(Collider * coll){
    curr_coll = coll;
    return coll;
}

Collider* GameObject::get_collider(){
    return curr_coll;
}
