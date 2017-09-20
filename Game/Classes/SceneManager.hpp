//
//  SceneManager.hpp
//  Game
//
//  Created by Blind Joe Death on 19.09.17.
//  Copyright © 2017 test. All rights reserved.
//

#ifndef SceneManager_hpp
#define SceneManager_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ResourcePath.hpp"
#include "MovableObject.hpp"
#include "Road.hpp"

static class SceneManager{
    private:
    static int scr_width;
    static int scr_height;
    static int car_width;
    static int car_height;
    static int players_count;
    
    public :
    static int road_width;
    static int road_height;
    static int layers_count;
    static sf::RenderWindow * window;
    static sf::Music * music;
    static void create_window();
    static std::vector<MovableObject*> cars;
    static std::vector<Road*> roads;
};

#endif /* SceneManager_hpp */
