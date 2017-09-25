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
#include <Utils.hpp>

static class SceneManager{
    private:
    static int car_width;
    static int car_height;
    static int players_count;
    static int y_right_car_pos;
    static std::map<sf::Keyboard::Key, std::function<void()>> key_actions;
    static std::map<sf::Keyboard::Key, bool> is_key_pressed;
    static void set_actions();
    static bool is_car_pos_right(MovableObject * car, Road * road);
    static Utils::direction turn_direction(Utils::direction);
    static void movement(MovableObject*, Road*, Utils::direction);
    
    public :
    static int scr_width;
    static int scr_height;
    static int road_width;
    static int road_height;
    static int layers_count;
    static sf::RenderWindow * window;
    static sf::Music * music;
    static void create_window();
    static void set_key_state(sf::Keyboard::Key, sf::Event::EventType);
    static void execute_actions();
    static std::vector<MovableObject*> cars;
    static std::vector<Road*> roads;
    static void move_cars();
};

#endif /* SceneManager_hpp */
