//
//  Vertex.cpp
//  RealisticRoofs
//
//  Created by Almir Bijedic on 11/02/15.
//  Copyright (c) 2015 Almir Bijedic. All rights reserved.
//

#include <stdio.h>
#include <utility>

enum vertexType { SE = 0, NE = 1, SW = 2, NW = 3, RE = 4 };


class Vertex {
public:
    Vertex() : isCandidate(false) {};
    float x;
    int n;
    float y;
    char name;
    vertexType type;
    Vertex* next;
    Vertex* prev;
    std::pair<float, float> maxSegmentEnd1;
    std::pair<float, float> maxSegmentEnd2;
    bool isCandidate;
};

struct CompareVertexX {
    bool operator()(const Vertex* lhs, const Vertex* rhs)  {
        return lhs->y < rhs->y;
    }

};

struct CompareVertexY {
    bool operator()(const Vertex* lhs, const Vertex* rhs)  {
        return lhs->x < rhs->x;
    }
};

struct CompareByN {
    bool operator()(const std::pair<Vertex*, Vertex*> lhs, const std::pair<Vertex*, Vertex*> rhs)  {
        if (lhs.first->n == rhs.first->n) {
            return lhs.second->n < rhs.second->n;
        } else {
            return lhs.first->n < rhs.first->n;
        }
    }
};