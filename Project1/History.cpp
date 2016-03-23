//
//  History.cpp
//  CS32Project1
//
//  Created by Monil Patel on 1/6/16.
//  Copyright © 2016 Monil Patel. All rights reserved.
//
#include <stdio.h>
#include "History.h"
#include "globals.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
{
    m_rows=nRows;
    m_cols=nCols;
    
    // Creates the initial grid
    for (int a=0; a<m_rows; a++)
    {
        for (int b=0; b<m_cols; b++)
        {
            m_grid[a][b]='.';
        }
    }
}

bool History::record(int r, int c)
{
    if (r <= 0  ||  c <= 0  ||  r > m_rows  ||  c > m_cols)
    {
        return false;
    }
    char& gridChar=m_grid[r-1][c-1]; // From other Arena.cpp
    if (gridChar=='.')
    {
        gridChar='A';
    }
    else if (gridChar=='Z')
    {
    }
    else
    {
        gridChar++;
    }
    return true;
}
void History::display() const
{
    clearScreen();
    for (int r=0; r<m_rows; r++)
    {
        for (int c=0; c<m_cols; c++)
        {
            cout <<m_grid[r][c];
        }
        cout<<endl;
    }
    cout<<endl;
}