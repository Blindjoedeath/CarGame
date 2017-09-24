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
float Road::lim_obstr_filled_part = 0.05;
int Road::wall_indent = 150;
int Road::min_obstr_dist = 10;


int Road::get_dist_from_surf(sf::Vector2f first_pos, sf::Vector2f second_pos,
                               sf::IntRect first_trans, sf::IntRect second_trans){
    return (sqrt(pow(first_pos.x + first_trans.width/2 - second_pos.x + second_trans.width/2, 2) +
                 pow(first_pos.y + first_trans.height/2 - second_pos.y + second_trans.height/2, 2)) -
                (first_trans.width/2 + second_trans.width/2)) ;
}

void Road::gen_obstr(){
    float area = ((float)get_size().width - 2*wall_indent) * (float)get_size().height * lim_obstr_filled_part;
    srand(time(0) + get_position().x);
    while (area > 0)
    {
        sf::Vector2f pos;
        pos.x = get_position().x + wall_indent +
            rand() % (get_size().width - wall_indent*2);
        pos.y = -rand() % get_size().height + SceneManager::scr_height;
        
        sf::IntRect size;
        size.width = min_obstr_size.x + rand() % (max_obstr_size.x - min_obstr_size.x);
        size.height = size.width;
        bool isCorrect = false;
        if (pos.x > get_position().x + wall_indent &&
                pos.x < get_position().x + get_size().width - wall_indent){
            isCorrect = true;
            for (int i = 0; i < obstruction.size(); ++i)
            {
                int dist = get_dist_from_surf(pos, obstruction[i]->get_position(), size, obstruction[i]->get_size());
                std::cout << dist << std::endl;
                if (dist < min_obstr_dist){
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
    gen_obstr();
    for (auto it = obstruction.begin(); it != obstruction.end(); ++it){
        add_child(*it);
    }
}
