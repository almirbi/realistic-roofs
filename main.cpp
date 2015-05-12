//
//  main.cpp
//  RealisticRoofs
//
//  Created by Almir Bijedic on 02/02/15.
//  Copyright (c) 2015 Almir Bijedic. All rights reserved.
//

#include <iostream>
#include "RectilinearPolygon.h"

int main(int argc, const char * argv[]) {
    RectilinearPolygon p = RectilinearPolygon();
    int running(1);
    do {
    cout << "Welcome to the realistic roofs enumeration algorithm." << endl;
    
    cout << "Do you wish to run an out of the box test case or do you want to insert a polygon by yourself?" << endl << endl;
    cout << "Type 1 for test case 1" << endl;
    cout << "Type 2 for test case 2" << endl;
    cout << "Type 3 for test case 3" << endl;
    cout << "Type 4 to starting inserting your own vertices of the rectilinear polygon." << endl << endl << endl;
    
    int menu;
    
    cin >> menu;
    
    switch (menu) {
        case 1: {
                    p.addVertex(0, 100, RE);
                    p.addVertex(100, 100, RE);
                    float x(100), y(99.5);
                    for ( int i = 1; i <= 10; i++) {
                        p.addVertex(x, y, SW);
                        cout << "added " << x << " " << y << endl;
                        x++;
                        p.addVertex(x, y, RE);
                        cout << "added " << x << " " << y << endl;
                        y -= 0.5;
                    }
                    p.addVertex(x, 0, RE);
                    p.addVertex(10, 0, RE);
                    x = 10; y = 0.5;
                    for ( int i = 1; i <= 9; i++) {
                        p.addVertex(x, y, NE);
                        cout << "added " << x << " " << y << endl;
                        x--;
                        p.addVertex(x, y, RE);
                        cout << "added " << x << " " << y << endl;
                        y += 0.5;
                    }
                    p.addVertex(1, 5, NE);
                    p.addVertex(0, 5, RE, true);
                }
            break;
        case 2:
            p.addVertex(0, 4, RE);
            p.addVertex(8, 4, RE);
            p.addVertex(8, 3, SW);
            p.addVertex(9, 3, RE);
            p.addVertex(9, 2, SW);
            p.addVertex(10, 2, RE);
            p.addVertex(10, 0, RE);
            p.addVertex(2, 0, RE);
            p.addVertex(2, 0.5, NE);
            p.addVertex(1, 0.5, RE);
            p.addVertex(1, 1, NE);
            p.addVertex(0, 1, RE, true);
            break;
        case 3:
            p.addVertex(0, 2, RE);
            p.addVertex(1, 2, SE);
            
            p.addVertex(1, 3, RE);
            p.addVertex(2, 3, RE);
            
            p.addVertex(2, 2.5, SW);
            p.addVertex(3, 2.5, RE);
            p.addVertex(3,2.4, RE);
            
            p.addVertex(2.8,2.4, NW);
            p.addVertex(2.8,2.1, SW);
            p.addVertex(3,2.1, RE);
            
            p.addVertex(3, 0.5, RE);
            p.addVertex(2, 0.5, NW);
            p.addVertex(2, 0, RE);
            
            p.addVertex(1.3, 0, RE);
            p.addVertex(1.3, 1, NE);
            p.addVertex(0, 1, RE, true);
            break;
        case 4: {
                    float input(0);
                    bool isLast(false);
                    int type;
                    while (!isLast) {
                        cout << "Input x: " << endl;
                        cin >> input;
                        float tmpX = input;
                        cout << "Input y: " << endl;
                        cin >> input;
                        float tmpY = input;
                        cout << "Which type is this vertex?\n 0 - SE\n 1 - SW\n 2 - NE\n 3 - NW\n 4 for a convex vertex: " << endl;
                        int typeInt;
                        cin >> typeInt;
                        vertexType type;
                        switch (typeInt) {
                            case 0:
                                type = SE;
                                break;
                            case 1:
                                type = SW;
                                break;
                            case 2:
                                type = NE;
                                break;
                            case 3:
                                type = NW;
                                break;
                            case 4:
                                type = RE;
                                break;
                        }
                        cout << "Is this the last vertex? 1 - yes, 0 - no" << endl;
                        cin >> input;
                        
                        if (1 == input) isLast = true; else isLast = false;
                        p.addVertex(tmpX, tmpY, type, isLast);
                    }
                    break;
                }
        default:
            cout << "Please choose a number from 1 to 4" << endl;
            return 0;
    }
    //O (n log(n) )
    p.lineSweep1();
    //O (n log(n) )
    p.lineSweep2();
    //O (n log(n) )
    p.lineSweep3();
    //O (n log(n) )
    p.lineSweep4();
    p.generateCandidatePairs();
    p.sortLexicographicalSets();
    vector<pair<Vertex*, Vertex*> > initial = vector<pair<Vertex*, Vertex*> >();
    vector<int> listLv = vector<int>();
    listLv.push_back(0);
    listLv.push_back(p.getNumberOfCandidateVertices());
    cout << "Compatible set #1" <<  " : { ";
    cout << " }" << endl << endl;
    p.nextCompSet(initial, listLv);
    cout << "Total number of compatible sets: " << p.getNumberOfCompatibleSets() << endl;
        
        cout << "Do you want another run? 1 for yes, 0 for no" << endl; cin >> running;
        p = RectilinearPolygon();
    } while (running == 1);
    cout << "Thanks! Bye." << endl << endl;
    return 0;
}
