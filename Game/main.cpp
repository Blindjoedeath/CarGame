//
// Disclaimer:
// ----------
// This code will work only if you selected window, graphics and audio.
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "SceneManager.hpp"
#include <iostream>
#include <cmath>
int main (int argc, char** argv){
    
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
        SceneManager::draw();
        SceneManager::window->display();
    }
    (*SceneManager::music).~Music();
    (*SceneManager::window).~RenderWindow();
    
    return EXIT_SUCCESS;
}
