//
//  SceneManager.cpp
//  Game
//
//  Created by Blind Joe Death on 19.09.17.
//  Copyright © 2017 test. All rights reserved.
//

#include "SceneManager.hpp"
#include <iostream>
#include <Collider.hpp>
#include <Utils.hpp>

typedef std::map<sf::Keyboard::Key, std::function<void()>> action_map;
typedef std::map<sf::Keyboard::Key, bool>  bool_map;

int SceneManager::scr_height = 600;
int SceneManager::scr_width = 1000;
int SceneManager::car_width = 80;
int SceneManager::car_height = 120;
int SceneManager::layers_count = 2;
int SceneManager::players_count = 2;
int SceneManager::y_right_car_pos = 400;
int SceneManager::indent_width = 50;
int SceneManager::road_lower_bound;
int SceneManager::road_upper_bound;
int SceneManager::car_lower_bound;
int SceneManager::car_upper_bound;
action_map SceneManager::key_actions;
bool_map SceneManager::is_key_pressed;
std::vector<Road*> SceneManager::roads;
std::vector<MovableObject*> SceneManager::cars;
std::vector<Collider*> SceneManager::indents;
sf::RenderWindow* SceneManager::window;
sf::Music* SceneManager::music;



void SceneManager::create_indents(){
    sf::IntRect size;
    size.width = indent_width;
    size.height = scr_height;
    sf::Vector2f pos(roads[0]->get_position().x, 0);
    indents.push_back(new Collider(pos, size , Collider::STATIC));
    pos.x = roads[0]->get_position().x + roads[0]->get_size().width - indent_width;
    indents.push_back(new Collider(pos, size, Collider::STATIC));
    pos.x = roads[1]->get_position().x;
    indents.push_back(new Collider(pos, size, Collider::STATIC));
    pos.x = roads[1]->get_position().x + roads[1]->get_size().width - indent_width;
    indents.push_back(new Collider(pos, size, Collider::STATIC));
}

Utils::direction SceneManager::turn_direction(Utils::direction dir){
    switch(dir){
        case  Utils::direction::BACK:
            return Utils::direction::FRONT;
        case Utils::direction::FRONT:
            return Utils::direction::BACK;
        case  Utils::direction::LEFT:
            return Utils::direction::RIGHT;
        case Utils::direction::RIGHT:
            return Utils::direction::LEFT;
    }
    return;
}

bool SceneManager::is_car_pos_right(MovableObject *car, Road *road){
    if (car->get_position().y - y_right_car_pos < 10)
        return true;
    return false;
}

void SceneManager::movement(int car_num, Utils::direction dir){
    MovableObject * car = cars[car_num];
    Road * road = roads[car_num];
    car->set_x_block(!(road->get_y_speed() > 0.001 || road->get_y_speed() < -0.001));
    if (is_car_pos_right(car, road) && (road -> get_position().y >= road_lower_bound || dir==Utils::FRONT) &&
        (road->get_position().y <= road_upper_bound || dir == Utils::BACK) && dir != Utils::LEFT &&
        dir != Utils::direction::RIGHT){
        if (car->get_y_speed() != 0){
            road->set_y_speed(-car->get_y_speed());
            road->set_y_accel(-car->get_y_accel());
            car->set_y_speed(0);
            car->set_y_accel(0);
        }
        road->add_acceleration(turn_direction(dir));
    }
    else{
        if (car->get_position().y <= car_lower_bound){
            collide(car_num, Utils::direction::FRONT);
        }
        else if (car -> get_position().y >= car_upper_bound){
            collide(car_num, Utils::direction::BACK);
        }
        car->add_acceleration(dir);
    }
}

void SceneManager::collide(int car_num, Utils::direction dir){
    bool collide = true;
    switch(dir){
        case Utils::direction::FRONT:{
            if (is_car_pos_right(cars[car_num], roads[car_num])){
                if(roads[car_num]->get_y_speed() >= 0){
                    collide = false;
                }
            }
            else {
                if (cars[car_num]->get_y_speed() <= 0){
                    collide = false;
                }
            }
        }
            break;
        case Utils::direction::BACK:{
            if (is_car_pos_right(cars[car_num], roads[car_num])){
                if (roads[car_num]->get_y_speed() <= 0){
                    collide = false;
                }
            }
            else {
                if (cars[car_num]->get_y_speed() >= 0){
                    collide = false;
                }
            }
        }
            break;
        case Utils::direction::RIGHT:{
            if(cars[car_num]->get_x_speed() <= 0)
                collide = false;
        }
            break;
        case Utils::direction::LEFT:{
            if (cars[car_num]->get_x_speed() >= 0)
                collide = false;
        }
            break;
    }
    if (collide){
        if (is_car_pos_right(cars[car_num], roads[car_num]) &&
                dir != Utils::direction::LEFT && dir != Utils::direction::RIGHT)
            roads[car_num]->collide(turn_direction(dir));
        else{
            cars[car_num]->collide(dir);
        }
    }
}

void SceneManager::check_collission(){
    
    for (int i = 0; i < 2; ++i){
        Utils::direction dir;
        if (SceneManager::cars[i]->get_collider()->is_collided(dir)){
            collide(i, dir);
        }
    }
}

void SceneManager::execute_actions(){
    for (action_map::iterator it = key_actions.begin(); it!=key_actions.end(); ++it){
        if (is_key_pressed[it->first]){
            it->second();
        }
    }
}

void SceneManager::set_key_state(sf::Keyboard::Key key,sf::Event::EventType event){
    if (event == sf::Event::KeyPressed)
        is_key_pressed[key] = true;
    if (event == sf::Event::KeyReleased)
        is_key_pressed[key] = false;
}

void SceneManager::move_cars(){
    check_collission();
    for (int i = 0; i < 2; ++i){
        cars[i]->move();
        roads[i]->move();
    }
}

void SceneManager::set_actions(){
    key_actions[sf::Keyboard::W] = [](){movement(0, Utils::direction::FRONT);};
    key_actions[sf::Keyboard::S] = [](){movement(0, Utils::direction::BACK);};
    key_actions[sf::Keyboard::A] = [](){movement(0, Utils::direction::LEFT);};
    key_actions[sf::Keyboard::D] = [](){movement(0, Utils::direction::RIGHT);};
    key_actions[sf::Keyboard::Up] = [](){movement(1, Utils::direction::FRONT);};
    key_actions[sf::Keyboard::Down] = [](){movement(1, Utils::direction::BACK);};
    key_actions[sf::Keyboard::Left] = [](){movement(1, Utils::direction::LEFT);};
    key_actions[sf::Keyboard::Right] = [](){movement(1, Utils::direction::RIGHT);};
    for (action_map::iterator it = key_actions.begin(); it!=key_actions.end(); ++it){
        is_key_pressed[it->first] = false;
    }

}
void SceneManager :: create_window(){
    window = new sf::RenderWindow();
    music = new sf::Music();
    (*window).create(sf::VideoMode(scr_width, scr_height), "Game");
    if (!(*music).openFromFile(resourcePath() + "music.ogg")){
        return EXIT_FAILURE;
    }
//    (*music).play();
    sf::IntRect rect;
    for (int i = 0; i < players_count; ++i){
        sf::IntRect size;
        size.width = scr_width/players_count;
        size.height = scr_height * 10;
        sf::Vector2f pos((scr_width/players_count) * i, -(size.height) + scr_height);
        roads.push_back(new Road("road.jpg", size, pos, 1));
        sf::Vector2f car_pos((roads[i]->get_position()).x + roads[i]->get_size().width / 2, scr_height - car_height);
        sf::IntRect car_size;
        car_size.width = car_width;
        car_size.height = car_height;
        cars.push_back(new MovableObject("car.png", car_size, car_pos, 2));
        cars[i]->add_collider(new Collider(cars[i]->get_position(), cars[i]->get_size(), Collider::mode::DYNAMIC));
        roads[i]->set_position
            (sf::Vector2f(roads[i]->get_position().x, roads[i]->get_position().y + cars[i]->get_size().height));
    }
    road_upper_bound = -cars[0]->get_size().height;
    road_lower_bound = roads[0]->get_position().y;
    car_upper_bound = scr_height - cars[0]->get_size().height;
    car_lower_bound = 0;
    set_actions();
    create_indents();
}

