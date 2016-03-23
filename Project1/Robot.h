//
//  Robot.h
//  CS32Project1
//
//  Created by Monil Patel on 1/6/16.
//  Copyright © 2016 Monil Patel. All rights reserved.
//

#ifndef Robot_h
#define Robot_h
class Arena;

class Robot {
public:
// Constructor
Robot(Arena* ap, int r, int c);

// Accessors
int  row() const;
int  col() const;

// Mutators
void move();
bool getAttacked(int dir);

private:
Arena* m_arena;
int    m_row;
int    m_col;
int    m_health;
int    numOfRobotsKilledAtPos;
};
#endif /* Robot_h */