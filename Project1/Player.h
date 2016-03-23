//
//  Player.h
//  CS32Project1
//
//  Created by Monil Patel on 1/6/16.
//  Copyright © 2016 Monil Patel. All rights reserved.
//

#ifndef Player_h
#define Player_h
class Arena;

class Player {
public:
// Constructor
Player(Arena *ap, int r, int c);

// Accessors
int  row() const;
int  col() const;
int  age() const;
bool isDead() const;

// Mutators
void   stand();
void   moveOrAttack(int dir);
void   setDead();

private:
Arena* m_arena;
int    m_row;
int    m_col;
int    m_age;
bool   m_dead;
};

#endif /* Player_h */
