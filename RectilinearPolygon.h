//
//  RectilinearPolygon.h
//  RealisticRoofs
//
//  Created by Almir Bijedic on 10/02/15.
//  Copyright (c) 2015 Almir Bijedic. All rights reserved.
//

#ifndef __RealisticRoofs__RectilinearPolygon__
#define __RealisticRoofs__RectilinearPolygon__

#include <stdio.h>
#include <complex.h>
#include <vector>
#include <set>
#include "CandidatePair.cpp"
#include "Vertex.cpp"
#include <map>

using namespace std;

//typedef complex<float> point;


class RectilinearPolygon {
private:
    int n;
    vector<Vertex*> vertices;
    
    set<float> sweepEventPointsX;
    set<float> sweepEventPointsY;
    
    map<float, set<Vertex*, CompareVertexX> > verticesMapX;
    map<float, set<Vertex*, CompareVertexY> > verticesMapY;
 
    set<int> runningMaxSegments;
    
    vector<Vertex*> NEVertices;
    vector<Vertex*> SWVertices;
    vector<Vertex*> SEVertices;
    vector<Vertex*> NWVertices;
    
    int candidateVertices;

    set<pair<Vertex*, Vertex*>, CompareByN> candidatePairs;
    
    vector<pair<Vertex*, Vertex*> >* lexicographicList[200][200];
    set<vector<pair<Vertex*, Vertex*>>> compatibleSets;
    bool areLinesIntersecting(pair<float, float> a0, pair<float, float> a1, pair<float, float> a2, pair<float, float> a3);
    void reportCompatibleSet(vector<pair<Vertex*, Vertex*>> compSet);
public:
    RectilinearPolygon() :
        n(0),
        runningMaxSegments(set<int>()),
        NEVertices(vector<Vertex*>()),
        NWVertices(vector<Vertex*>()),
        SEVertices(vector<Vertex*>()),
        SWVertices(vector<Vertex*>()),
        candidatePairs(set<pair<Vertex*, Vertex*>, CompareByN>()),
        compatibleSets(set<vector<pair<Vertex*, Vertex*>>>())
    {
        this->compatibleSets.insert(vector<pair<Vertex*, Vertex*> >());
    };
    void addVertex(float x, float y, vertexType type, bool end = false);
    void lineSweep1();
    void lineSweep2();
    void lineSweep3();
    void lineSweep4();
    void sortLexicographicalSets();
    void generateCandidatePairs();
    void nextCompSet(vector<pair<Vertex*, Vertex*>> compSet, vector<int> listLv);
    int getNumberOfCandidateVertices() { return this->candidateVertices; }
    unsigned long getNumberOfCompatibleSets() { return this->compatibleSets.size(); }
};

#endif /* defined(__RealisticRoofs__RectilinearPolygon__) */
