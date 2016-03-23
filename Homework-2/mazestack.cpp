//
//  mazestack.cpp
//  CS32Homework2
//
//  Created by Monil Patel on 1/28/16.
//  Copyright © 2016 Monil Patel. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <stack>
using namespace std;
class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    stack<Coord> coordStack;     // declare a stack of Coords
    coordStack.push(Coord(sr,sc));
    maze[sr][sc]='F';
    
    while (!coordStack.empty())
    {
        Coord a=coordStack.top();
        coordStack.pop();
        
        if (a.r()==er && a.c()==ec)
        {
            return true;
        }
        if (maze[a.r()-1][a.c()]=='.')
        {
            coordStack.push(Coord(a.r()-1,a.c()));
            maze[a.r()-1][a.c()]='F';
        }
        if (maze[a.r()][a.c()+1]=='.')
        {
            coordStack.push(Coord(a.r(),a.c()+1));
            maze[a.r()][a.c()+1]='F';
        }
        if (maze[a.r()+1][a.c()]=='.')
        {
            coordStack.push(Coord(a.r()+1,a.c()));
            maze[a.r()+1][a.c()]='F';
        }
        if (maze[a.r()][a.c()-1]=='.')
        {
            coordStack.push(Coord(a.r(),a.c()-1));
            maze[a.r()][a.c()-1]='F';
        }
    }
    return false;
}