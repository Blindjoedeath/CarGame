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

sf::Vector2i Road::max_obstr_size(100, 100);
sf::Vector2i Road::min_obstr_size(50, 50);
float Road::lim_obstr_filled_part = 0.2;
int Road::wall_indent = 150;


float Road::get_dist_from_surf(sf::Vector2f first_pos, sf::Vector2f second_pos,
                               sf::IntRect first_trans, sf::IntRect second_trans){
    return (sqrt(pow(first_pos.x - second_pos.x, 2) +
                 pow(first_pos.y - second_pos.y, 2)) -
                    (first_trans.width/2 + second_trans.width/2));
}

void Road::gen_obstr(){
    float area = (get_size().width - 2*wall_indent) * get_size().height * lim_obstr_filled_part;
    std::cout << get_size().width << " * " << get_size().height << std::endl;
    while (area > 0)
    {
        sf::Vector2f pos;
        pos.x = get_position().x + wall_indent +
                random() % (get_size().width - wall_indent*2);
        pos.y = random() % get_size().width;
        
        sf::IntRect size;
        size.width = min_obstr_size.x + random() % (max_obstr_size.x - min_obstr_size.x);
        size.height = min_obstr_size.y + random() % (max_obstr_size.y - min_obstr_size.y);
        bool isCorrect = true;
        if (pos.x > get_position().x + wall_indent &&
                pos.x < get_position().x + get_size().width - wall_indent){
            for (int i = 0; i < obstr_count; ++i)
            {
                if (get_dist_from_surf(pos, obstruction[i]->get_position(), size, obstruction[i]->get_size()) < 0){
                    isCorrect = false;
                    break;
                }
            }
        }
        if (isCorrect)
        {
            obstruction.push_back(new GameObject("obstruction.jpg", size, pos, 2));
            area -= size.width * size.height;
        }
        std::cout << "whiling\n";
    }
}

Road::Road(const char * fileName, sf::IntRect size, sf::Vector2f pos, int layout)
: MovableObject(fileName, size, pos, layout){
    obstr_count = 0;
//    gen_obstr();
    for (int i = 0; i < obstr_count; ++i){
        add_child(obstruction[i]);
    }
}
