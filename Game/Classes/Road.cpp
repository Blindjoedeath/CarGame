//
//  Road.cpp
//  Game
//
//  Created by Blind Joe Death on 20.09.17.
//  Copyright © 2017 test. All rights reserved.
//

#include "Road.hpp"
#include <cmath>
#include <iostream>
#include <SceneManager.hpp>
#include <time.h>

sf::Vector2i Road::max_obstr_size(100, 100);
sf::Vector2i Road::min_obstr_size(50, 50);
float Road::lim_obstr_filled_part = 0.04;
int Road::min_obstr_dist = 200;

GameObject* Road::add_obstruction(GameObject * obj){
    obstruction.push_back(obj);
    return obj;
}


int Road::get_dist_from_surf(sf::Vector2f  first_pos, sf::Vector2f  second_pos,
                               sf::IntRect  first_trans, sf::IntRect  second_trans){
    return (sqrt(pow((first_pos.x + first_trans.width/2) - (second_pos.x + second_trans.width/2), 2) +
                 pow((first_pos.y + first_trans.height/2) - (second_pos.y + second_trans.height/2), 2)) -
                (first_trans.width/2 + second_trans.width/2)) ;
}

void Road::gen_obstr(){
    for (int i = 0; i < obstruction.size(); ++i){
        for (auto j = children.begin(); j < children.end(); ++j){
            if (*j == obstruction[i]){
                children.erase(j);
                delete obstruction[i];
                std:: cout << "children count = "<< children.size() << std::endl;
                break;
            }
        }
    }
    obstruction.clear();
    int wall_indent = SceneManager::indent_width + SceneManager::car_width + 10;
    float area = ((float)get_size().width - 2*SceneManager::indent_width) * (float)get_size().height * lim_obstr_filled_part;
    while (area > 0)
    {
        sf::IntRect size;
        size.width = min_obstr_size.x + rand() % (max_obstr_size.x - min_obstr_size.x);
        size.height = size.width;
        sf::Vector2f pos;
        pos.x = get_position().x + SceneManager::indent_width +
            rand() % (get_size().width - SceneManager::indent_width*2);
        pos.y = -rand() % (get_size().height - 2 * SceneManager::scr_height);
    
        bool isCorrect = false;
        if (pos.x >= get_position().x + SceneManager::indent_width &&
                pos.x <= get_position().x + get_size().width - SceneManager::indent_width - size.width){
            isCorrect = true;
            for (int i = 0; i < obstruction.size(); ++i)
            {
                int dist = get_dist_from_surf(pos, obstruction[i]->get_position(), size, obstruction[i]->get_size());
                if (dist < min_obstr_dist){
                    isCorrect = false;
                    break;
                }
            }
        }
        if (isCorrect)
        {
            Collider * coll = add_obstruction(new GameObject("obstruction.jpg", size, pos, 2))
                ->add_collider(new Collider(pos, size, Collider::mode::STATIC));
            area -= size.width * size.height;
        }
    }
    for (auto it = obstruction.begin(); it != obstruction.end(); ++it){
        add_child(*it);
    }
}

Road::Road(const char * fileName, sf::IntRect size, sf::Vector2f pos, int layout)
: MovableObject(fileName, size, pos, layout){
    gen_obstr();
    srand(time(NULL));
}
