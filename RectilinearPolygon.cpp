//
//  RectilinearPolygon.cpp
//  RealisticRoofs
//
//  Created by Almir Bijedic on 10/02/15.
//  Copyright (c) 2015 Almir Bijedic. All rights reserved.
//

#include "RectilinearPolygon.h"
#include <iostream>

using namespace std;


void RectilinearPolygon::addVertex(float x, float y, vertexType type, bool end) {
    
    //add the vertex to the vector holding all vertices. We can access them with n
    Vertex* a = new Vertex();
    a->x = x; a->y = y; a->n = this->n; a->type = type;
    this->vertices.push_back(a);
    
    //mark points at which the sweep line will have to stop
    //the elements in the set are sorted and duplicates are ignores, so at the
    //end we have points at which the line sweep will stop for both x and y coordinate
    //(we are doing both a horizontal and vertical sweep)
    this->sweepEventPointsX.insert(x);
    this->sweepEventPointsY.insert(y);
    
    //check if the map already has a vector going for x
    if ( this->verticesMapX.find(x) == this->verticesMapX.end() ) {
        set<Vertex*, CompareVertexX> tmpVector = set<Vertex*, CompareVertexX>();
        tmpVector.insert(a);
        this->verticesMapX.insert( std::pair<float,set<Vertex*, CompareVertexX> >(x, tmpVector) );
    } else {
        this->verticesMapX[x].insert(a);
    }
    
    if ( this->verticesMapY.find(y) == this->verticesMapY.end() ) {
        set<Vertex*, CompareVertexY> tmpVector = set<Vertex*, CompareVertexY>();
        tmpVector.insert(a);
        this->verticesMapY.insert( std::pair<float,set<Vertex*, CompareVertexY> >(y, tmpVector) );
    } else {
        this->verticesMapY[y].insert(a);
    }
    
    
    if (this->n != 0) {
        a->prev = this->vertices[n - 1];
        this->vertices[n - 1]->next = a;
    }
    this->n++;
    if (end) {
        a->next = this->vertices[0];
        this->vertices[0]->prev = a;
    }
}

void RectilinearPolygon::lineSweep1() {
    set<float>::const_iterator it;
    
    //for each vertical line
    for (it = this->sweepEventPointsX.begin(); it != this->sweepEventPointsX.end(); (++it)) {
        set<Vertex*>::const_iterator vertical;
        
        // these two for loops total to O(n) since it is the number of sweep lines by the x coordinate * points on each stop,
        //which actually equals to n
        
        if (this->runningMaxSegments.size() > 0 ) {
            set<int>::const_iterator maxSegmentsIt;
            vector<int> toErase;
            toErase = vector<int>();
            for (maxSegmentsIt = this->runningMaxSegments.begin(); maxSegmentsIt != this->runningMaxSegments.end(); ++maxSegmentsIt) {
                
                for (vertical = this->verticesMapX[*it].begin(); vertical != this->verticesMapX[*it].end(); ++vertical) {
                    Vertex* v2 = *(vertical);
                    Vertex* v1 = *(++vertical);
                    if (this->vertices[*maxSegmentsIt]->y <= v1->y && this->vertices[*maxSegmentsIt]->y >= v2->y) {
                        pair<float, float> max1 = pair<float, float>();
                        max1.second = this->vertices[*maxSegmentsIt]->y;
                        max1.first = *it;
                        this->vertices[*maxSegmentsIt]->maxSegmentEnd1 = max1;
                        
                        toErase.push_back(*maxSegmentsIt);
                    }
                }
            }
            for (int k=0;k<toErase.size();k++){
                this->runningMaxSegments.erase(toErase[k]);
            }
        }

        for (vertical = this->verticesMapX[*it].begin(); vertical != this->verticesMapX[*it].end(); ++vertical) {
            if ((*vertical)->type == SE || (*vertical)->type  == NE) {
                this->runningMaxSegments.insert((*vertical)->n);
            }
        }
    }
}

void RectilinearPolygon::lineSweep2() {
    set<float>::reverse_iterator it;
    
    //for each vertical line
    for (it = this->sweepEventPointsX.rbegin(); it != this->sweepEventPointsX.rend(); (++it)) {
        set<Vertex*>::const_iterator vertical;
        
        // these two for loops total to O(n) since it is the number of sweep lines by the x coordinate * points on each stop,
        //which actually equals to n
        
        if (this->runningMaxSegments.size() > 0 ) {
            set<int>::const_iterator maxSegmentsIt;
            vector<int> toErase;
            toErase = vector<int>();
            for (maxSegmentsIt = this->runningMaxSegments.begin(); maxSegmentsIt != this->runningMaxSegments.end(); ++maxSegmentsIt) {
                
                for (vertical = this->verticesMapX[*it].begin(); vertical != this->verticesMapX[*it].end(); ++vertical) {
                    Vertex* v2 = *(vertical);
                    Vertex* v1 = *(++vertical);
                    if (this->vertices[*maxSegmentsIt]->y <= v1->y && this->vertices[*maxSegmentsIt]->y >= v2->y) {
                        pair<float, float> max1 = pair<float, float>();
                        max1.second = this->vertices[*maxSegmentsIt]->y;
                        max1.first = *it;
                        this->vertices[*maxSegmentsIt]->maxSegmentEnd1 = max1;
                        
                        toErase.push_back(*maxSegmentsIt);
                    }
                }
            }
            for (int k=0;k<toErase.size();k++){this->runningMaxSegments.erase(toErase[k]);}
        }
        
        for (vertical = this->verticesMapX[*it].begin(); vertical != this->verticesMapX[*it].end(); ++vertical) {
            if ((*vertical)->type == SW || (*vertical)->type  == NW) {
                this->runningMaxSegments.insert((*vertical)->n);
            }
        }
    }
}

void RectilinearPolygon::lineSweep3() {
    set<float>::const_iterator it;
    
    //for each horizontal line
    for (it = this->sweepEventPointsY.begin(); it != this->sweepEventPointsY.end(); (++it)) {
        set<Vertex*>::const_iterator horizontal;
        
        // these two for loops total to O(n) since it is the number of sweep lines by the x coordinate * points on each stop,
        //which actually equals to n
        
        if (this->runningMaxSegments.size() > 0 ) {
            set<int>::const_iterator maxSegmentsIt;
            vector<int> toErase;
            toErase = vector<int>();
            for (maxSegmentsIt = this->runningMaxSegments.begin(); maxSegmentsIt != this->runningMaxSegments.end(); ++maxSegmentsIt) {
                
                for (horizontal = this->verticesMapY[*it].begin(); horizontal != this->verticesMapY[*it].end(); ++horizontal) {
                    Vertex* v2 = *(horizontal);
                    Vertex* v1 = *(++horizontal);
                    if (this->vertices[*maxSegmentsIt]->x <= v1->x && this->vertices[*maxSegmentsIt]->x >= v2->x) {
                        pair<float, float> max1 = pair<float, float>();
                        max1.second = *it;
                        max1.first = this->vertices[*maxSegmentsIt]->x;
                        this->vertices[*maxSegmentsIt]->maxSegmentEnd2 = max1;
                        
                        toErase.push_back(*maxSegmentsIt);
                    }
                }
            }
            for (int k = 0;k < toErase.size(); k++) {
                this->runningMaxSegments.erase(toErase[k]);
            }
        }
        
        for (horizontal = this->verticesMapY[*it].begin(); horizontal != this->verticesMapY[*it].end(); ++horizontal) {
            if ((*horizontal)->type == NE || (*horizontal)->type  == NW) {
                this->runningMaxSegments.insert((*horizontal)->n);
                if ((*horizontal)->type == NE) {
                    this->NEVertices.push_back(*horizontal);
                } else {
                    this->NWVertices.push_back(*horizontal);
                }
            }
        }
    }
}

void RectilinearPolygon::lineSweep4() {
    set<float>::reverse_iterator it;
    
    //for each horizontal line
    for (it = this->sweepEventPointsY.rbegin(); it != this->sweepEventPointsY.rend(); (++it)) {
        set<Vertex*>::const_iterator horizontal;
        
        // these two for loops total to O(n) since it is the number of sweep lines by the x coordinate * points on each stop,
        //which actually equals to n
        
        if (this->runningMaxSegments.size() > 0 ) {
            set<int>::const_iterator maxSegmentsIt;
            vector<int> toErase;
            toErase = vector<int>();
            for (maxSegmentsIt = this->runningMaxSegments.begin(); maxSegmentsIt != this->runningMaxSegments.end(); ++maxSegmentsIt) {
                
                for (horizontal = this->verticesMapY[*it].begin(); horizontal != this->verticesMapY[*it].end(); ++horizontal) {
                    Vertex* v2 = *(horizontal);
                    Vertex* v1 = *(++horizontal);
                    if (this->vertices[*maxSegmentsIt]->x <= v1->x && this->vertices[*maxSegmentsIt]->x >= v2->x) {
                        pair<float, float> max1 = pair<float, float>();
                        max1.second = *it;
                        max1.first = this->vertices[*maxSegmentsIt]->x;
                        this->vertices[*maxSegmentsIt]->maxSegmentEnd2 = max1;
                        
                        toErase.push_back(*maxSegmentsIt);
                    }
                }
            }
            for (int k=0;k<toErase.size();k++){this->runningMaxSegments.erase(toErase[k]);}
        }
        
        for (horizontal = this->verticesMapY[*it].begin(); horizontal != this->verticesMapY[*it].end(); ++horizontal) {
            if ((*horizontal)->type == SE || (*horizontal)->type  == SW) {
                this->runningMaxSegments.insert((*horizontal)->n);
                if ((*horizontal)->type == SE) {
                    this->SEVertices.push_back(*horizontal);
                } else {
                    this->SWVertices.push_back(*horizontal);
                }
            }
        }
    }
}

//check if an opposite pair is a candidate pair is done in a constant time thanks to the maximal segments previously computed with a line sweep
bool RectilinearPolygon::areLinesIntersecting(pair<float, float> a0, pair<float, float> a1, pair<float, float> a2, pair<float, float> a3) {
    float A0(a0.first);
    float A1(a1.first);
    float A2(a2.first);
    float A3(a3.first);
    float B0(a0.second);
    float B1(a1.second);
    float B2(a2.second);
    float B3(a3.second);
    if (((A2-A0)*(B1-B0) - (B2-B0)*(A1-A0)) * ((A3-A0)*(B1-B0) - (B3-B0)*(A1-A0)) < 0
        &&
        ((A0-A2)*(B3-B2) - (B0-B2)*(A3-A2)) * ((A1-A2)*(B3-B2) - (B1-B2)*(A3-A2)) < 0)
    {
        return true;
    }
    return false;
}

void RectilinearPolygon::generateCandidatePairs() {
    for (int i = 0; i < this->SEVertices.size(); i++) {
        Vertex* v1 = this->SEVertices[i];
        for (int j = 0; j < this->NWVertices.size(); j++) {
            Vertex* v2 = this->NWVertices[j];
            if (areLinesIntersecting(pair<float, float>(v1->x, v1->y), v1->maxSegmentEnd1, pair<float, float>(v2->x, v2->y), v2->maxSegmentEnd2) && areLinesIntersecting(pair<float, float>(v1->x, v1->y), v1->maxSegmentEnd2, pair<float, float>(v2->x, v2->y), v2->maxSegmentEnd1) ) {
                v1->isCandidate = true;
                v2->isCandidate = true;
                if (v1->n < v2->n) {
                    this->candidatePairs.insert(pair<Vertex*, Vertex*>(v1,v2));
                } else {
                    this->candidatePairs.insert(pair<Vertex*, Vertex*>(v2,v1));
                }
            }
        }
    }
    for (int i = 0; i < this->SWVertices.size(); i++) {
        Vertex* v1 = this->SWVertices[i];
        for (int j = 0; j < this->NEVertices.size(); j++) {
            Vertex* v2 = this->NEVertices[j];
            if (areLinesIntersecting(pair<float, float>(v1->x, v1->y), v1->maxSegmentEnd1, pair<float, float>(v2->x, v2->y), v2->maxSegmentEnd2) && areLinesIntersecting(pair<float, float>(v1->x, v1->y), v1->maxSegmentEnd2, pair<float, float>(v2->x, v2->y), v2->maxSegmentEnd1) ) {
                v1->isCandidate = true;
                v2->isCandidate = true;
                if (v1->n < v2->n) {
                    this->candidatePairs.insert(pair<Vertex*, Vertex*>(v1,v2));
                } else {
                    this->candidatePairs.insert(pair<Vertex*, Vertex*>(v2,v1));
                }
            }
        }
    }
    
    int k = 1;
    for (int i = 0; i < this->vertices.size(); i++) {
        if (this->vertices[i]->isCandidate) {
            this->vertices[i]->n = k++;
        }
    }
    this->candidateVertices = k;
}

void RectilinearPolygon::sortLexicographicalSets() {
    this->lexicographicList[0][this->candidateVertices ] = new vector<pair<Vertex*, Vertex*>>();
    set<std::pair<Vertex*, Vertex*>>::const_iterator candidatePairsIt, candidatePairsIt2;
    for (candidatePairsIt = this->candidatePairs.begin(); candidatePairsIt != this->candidatePairs.end(); ++candidatePairsIt) {
        this->lexicographicList[0][this->candidateVertices]->push_back(*candidatePairsIt);
        this->lexicographicList[candidatePairsIt->first->n][candidatePairsIt->second->n] = new vector<pair<Vertex*, Vertex*>>();
        for (candidatePairsIt2 = this->candidatePairs.begin(); candidatePairsIt2 != this->candidatePairs.end(); ++candidatePairsIt2) {
            if (candidatePairsIt2 == candidatePairsIt) continue;
            
            /*cout << "(" << candidatePairsIt->first->n << ", " << candidatePairsIt->second->n << ")" << endl;
            cout << candidatePairsIt->first->n << " < " << candidatePairsIt2->first->n << " < " << candidatePairsIt2->second->n << " < " << candidatePairsIt->second->n << endl << endl;*/
            if ((candidatePairsIt->first->n < candidatePairsIt2->first->n &&
                candidatePairsIt2->second->n < candidatePairsIt->second->n) ||
                (candidatePairsIt->second->n < candidatePairsIt2->first->n )) {
                
                this->lexicographicList[candidatePairsIt->first->n][candidatePairsIt->second->n]->push_back(*candidatePairsIt2);
            }
        }
    }
}

void RectilinearPolygon::reportCompatibleSet(vector<pair<Vertex*, Vertex*>> compSet) {
    
    cout << "Compatible set #" << this->compatibleSets.size() + 1 << " : { ";
    for (int i = 0; i < compSet.size(); i++) {
        cout << "(" << compSet[i].first->n << ", " << compSet[i].second->n << ")";
        if (i != compSet.size() - 1) {
            cout << ", ";
        }
    }
    cout << " }" << endl << endl;
}

void RectilinearPolygon::nextCompSet(vector<pair<Vertex*, Vertex*> > compSet, vector<int> listLvPassed) {
    vector<int> listLv;
    listLv = listLvPassed;
    for (int x = 0; x < listLv.size() - 1; x++) {
        int a(listLv[x]), b(listLv[x+1]);
        for (int i = 0; i < (this->lexicographicList[a][b])->size(); i++) {
            compSet.push_back((*this->lexicographicList[a][b])[i]);
            reportCompatibleSet(compSet);
            this->compatibleSets.insert(compSet);
            vector<int> updatedListLv = vector<int>();
            updatedListLv.push_back((*this->lexicographicList[a][b])[i].first->n);
            updatedListLv.push_back((*this->lexicographicList[a][b])[i].second->n);
            for (int j = x + 1; j < listLv.size(); j++) {
                if (listLv[j] > listLv[1]) {
                    updatedListLv.push_back(listLv[j]);
                }
            }
            this->nextCompSet(compSet, updatedListLv);
            compSet.pop_back();
        }
    }
}
