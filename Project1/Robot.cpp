//
//  Robot.cpp
//  CS32Project1
//
//  Created by Monil Patel on 1/6/16.
//  Copyright © 2016 Monil Patel. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "Robot.h"
#include "Arena.h"
#include "globals.h"
using namespace std;
Robot::Robot(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** A robot must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "***** Robot created with invalid coordinates (" << r << ","
        << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_health = INITIAL_ROBOT_HEALTH;
}

int Robot::row() const
{
    return m_row;
}

int Robot::col() const
{
    return m_col;
}

void Robot::move()
{
    // Attempt to move in a random direction; if we can't move, don't move
    int dir = randInt(0, 3);  // dir is now UP, DOWN, LEFT, or RIGHT
    m_arena->determineNewPosition(m_row, m_col, dir);
}
// notify the History object that a robot has died at a grid point in the Arena that the History object corresponds to
bool Robot::getAttacked(int dir)  // return true if dies
{
    m_health--;
    if (m_health == 0)
        
        return true;
    if ( ! m_arena->determineNewPosition(m_row, m_col, dir))
    {
        m_health = 0;
        return true;
    }
    return false;
}
