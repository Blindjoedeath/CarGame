//
//  SceneManager.cpp
//  Game
//
//  Created by Blind Joe Death on 19.09.17.
//  Copyright © 2017 test. All rights reserved.
//

#include "SceneManager.hpp"
#include <iostream>

int SceneManager::scr_height = 600;
int SceneManager::scr_width = 1000;
int SceneManager::car_width = 60;
int SceneManager::car_height = 100;
int SceneManager::layers_count = 2;
int SceneManager::players_count = 2;

std::vector<Road*> SceneManager::roads;
std::vector<MovableObject*> SceneManager::cars;
sf::RenderWindow* SceneManager::window;
sf::Music* SceneManager::music;

void SceneManager :: create_window(){
    window = new sf::RenderWindow();
    music = new sf::Music();
    (*window).create(sf::VideoMode(scr_width, scr_height), "Game");
    if (!(*music).openFromFile(resourcePath() + "music.ogg")){
        return EXIT_FAILURE;
    }
    (*music).play();
    sf::IntRect rect;
    for (int i = 0; i < players_count; ++i){
        sf::Vector2f pos((scr_width/players_count) * i, -(scr_height * 3)/2);
        sf::IntRect size;
        size.width = scr_width/players_count;
        size.height = scr_height * 3;
        roads.push_back(new Road("road.jpg", size, pos, 1));
        sf::Vector2f car_pos((roads[i] -> get_position()).x / 2, -(roads[i] -> get_size()).height + car_height);
        sf::IntRect car_size;
        car_size.width = car_width;
        car_size.height = car_height;
        cars.push_back(new MovableObject("car.png", car_size, car_pos, 2));
    }
}


