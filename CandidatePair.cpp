//
//  CandidatePair.cpp
//  RealisticRoofs
//
//  Created by Almir Bijedic on 09/02/15.
//  Copyright (c) 2015 Almir Bijedic. All rights reserved.
//

#include <stdio.h>

class CandidatePair {
private:
    bool _isCompatible;
    float _x;
    float _y;
public:
    CandidatePair(float x, float y) : _x(x), _y(y), _isCompatible(false) { }
    float getX() { return this->_x; }
    float getY() { return this->_y; }
    bool isCompatible() { return this->_isCompatible; }
};
