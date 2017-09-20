//
//  Road.hpp
//  Game
//
//  Created by Blind Joe Death on 20.09.17.
//  Copyright © 2017 test. All rights reserved.
//

#ifndef Road_hpp
#define Road_hpp

#include <stdio.h>
#include "MovableObject.hpp"

class Road : public MovableObject{
    
    private :
    int obstr_count;
    std :: vector<GameObject*> obstruction;
    float get_dist_from_surf(sf::Vector2f, sf::Vector2f, sf::IntRect, sf::IntRect);
    void gen_obstr();
    static int lim_obstr_width;
    static int lim_obstr_height;
    static float lim_obstr_filled_part;
    static int wall_indent;
    
    public :
    Road(const char *, sf::IntRect, sf::Vector2f, int);
    bool check_collision(MovableObject *);
};

#endif /* Road_hpp */
