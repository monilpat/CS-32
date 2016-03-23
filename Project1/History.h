//
//  History.h
//  CS32Project1
//
//  Created by Monil Patel on 1/6/16.
//  Copyright © 2016 Monil Patel. All rights reserved.
//

#ifndef History_h
#define History_h
#include "globals.h"
class Arena;
class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
    
private:
    char m_grid [MAXROWS][MAXCOLS];
    int m_rows,m_cols;
};

#endif /* History_h */
