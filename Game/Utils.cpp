//
//  Utils.cpp
//  Game
//
//  Created by Blind Joe Death on 25.09.17.
//  Copyright © 2017 test. All rights reserved.
//

#include "Utils.hpp"

template <typename T>
int Utils::get_sign(T t){
    if (t > 0)
        return 1;
    return -1;
}
