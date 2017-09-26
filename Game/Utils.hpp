//
//  Utils.hpp
//  Game
//
//  Created by Blind Joe Death on 25.09.17.
//  Copyright © 2017 test. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <stdio.h>

class Utils{
public:
    static enum direction{FRONT, BACK, LEFT, RIGHT};
    template <typename T>
    static int get_sign(T);
};

#endif /* Utils_hpp */
