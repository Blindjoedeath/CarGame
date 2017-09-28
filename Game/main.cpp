
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "SceneManager.hpp"
#include <iostream>
#include <cmath>


int main (int argc, char** argv){
    /*
    sf::RenderWindow rv(sf::VideoMode(100 , 100), "Game");
    sf::Font font;
    font.loadFromFile(resourcePath() + "font.ttf");
    sf::Text text;
    text.setString("Hello");
    text.setCharacterSize(24);
    text.setStyle(sf::Text::Bold);
    text.setColor(sf::Color::Green);
    text.setPosition(50, 50);
    while (rv.isOpen()){
        sf::Event event;
        while (rv.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                rv.close();
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
                rv.close();
            }
        }
        rv.clear();
        rv.draw(text);
        rv.display();
    }
     */
    
    SceneManager::create_window();
    while (SceneManager::window->isOpen()){
        sf::Event event;
        while (SceneManager::window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                SceneManager::music->stop();
                SceneManager::window->close();
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
                SceneManager::music->stop();
                SceneManager::window->close();
            }
            if (event.type == sf::Event::KeyPressed | event.type == sf::Event::KeyReleased)
            {
                SceneManager::set_key_state(event.key.code, event.type);
            }
        }
        SceneManager::execute_actions();
        SceneManager::window->clear();
        for (int j = 1; j <= SceneManager::layers_count; ++j)
            for (int i = 0; i < GameObject::all_objects.size(); ++i)
                if (GameObject::all_objects[i] -> get_layer() == j)
                    SceneManager::window->draw(*GameObject::all_objects[i]->get_sprite());
        for (int i =0; i < SceneManager::texts.size(); ++i){
            SceneManager::window->draw(*SceneManager::texts[i]);
        }
        SceneManager::move_cars();
        SceneManager::window->display();
    }
    (*SceneManager::music).~Music();
    (*SceneManager::window).~RenderWindow();
    
    return EXIT_SUCCESS;
}
