
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



int main (int argc, char** argv){
    
    SceneManager::create_window();
    while ((*SceneManager::window).isOpen()){
        sf::Event event;
        while ((*SceneManager::window).pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                (*SceneManager::music).stop();
                (*SceneManager::window).close();
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
                (*SceneManager::music).stop();
                (*SceneManager::window).close();
            }
            if (event.type == sf::Event::KeyPressed | event.type == sf::Event::KeyReleased)
            {
                SceneManager::set_key_state(event.key.code, event.type);
            }
        }
        SceneManager::execute_actions();
        (*SceneManager::window).clear();
        for (int j = 1; j <= SceneManager::layers_count; ++j)
            for (int i = 0; i < GameObject::all_objects_count; ++i)
                if (GameObject::all_objects[i] -> get_layer() == j)
                    (*SceneManager::window).draw(*GameObject::all_objects[i]->get_sprite());
        for (int i = 0; i < 2; ++i)
        {
            SceneManager::cars[i] -> move();
            SceneManager::roads[i] -> move();
            Utils::direction dir;
            if (SceneManager::cars[i]->get_collider()->is_collided(dir)){
                SceneManager::cars[i]->colide(dir);
            }
        }
        (*SceneManager::window).display();
    }
    (*SceneManager::music).~Music();
    (*SceneManager::window).~RenderWindow();
    return EXIT_SUCCESS;
}
