//
//  LexicographicList.h
//  RealisticRoofs
//
//  Created by Almir Bijedic on 09/02/15.
//  Copyright (c) 2015 Almir Bijedic. All rights reserved.
//

#ifndef __RealisticRoofs__LexicographicList__
#define __RealisticRoofs__LexicographicList__

#include <stdio.h>
#include "CandidatePair.cpp"
#include <vector>

using namespace std;

class LexicographicList {
private:
    vector<CandidatePair> _candidatePairs;
};

#endif /* defined(__RealisticRoofs__LexicographicList__) */
