//
//  SceneManager.cpp
//  Game
//
//  Created by Blind Joe Death on 19.09.17.
//  Copyright © 2017 test. All rights reserved.
//

#include "SceneManager.hpp"

int SceneManager :: scr_height = 600;
int SceneManager :: scr_width = 800;

sf::RenderWindow SceneManager::window;
sf::Music SceneManager::music;

void SceneManager :: create_window(){
    window.create(sf::VideoMode(scr_width, scr_height), "Game");
    if (!SceneManager::music.openFromFile(resourcePath() + "music.ogg")){
        return EXIT_FAILURE;
    }
}


