#ifndef ACTOR_H_
#define ACTOR_H_
class StudentWorld;
#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor: public GraphObject
{
public:
    Actor(int imageID,int startX, int startY,Direction dir, double size, unsigned int depth,StudentWorld* world);
    virtual ~Actor();
    virtual void doSomething()=0;
    virtual void annoy(int amt)=0;
    virtual int getTheID()=0;
    
    virtual bool moveDirection(Direction d);
    virtual bool isValidLocToMoveTo(int xLoc, int yLoc);
    
    bool isAlive();
    void setAlive(bool res);
    void getCoordinates(int &x, int &y, Direction d, int numSteps);
    
    void incrementCounter();
    int getCounter();
    
    StudentWorld*  getWorld();
    
private:
    bool m_isAlive;
    StudentWorld * m_world;
    int m_counter;
    
};
class Dirt: public Actor
{
public:
    Dirt( int startX, int startY,StudentWorld* world);
    ~Dirt();
    virtual void doSomething();
    virtual void annoy(int amt);
    virtual int getTheID();
    
    
private:
};

class FrackMan: public Actor
{
    
public:
    FrackMan(StudentWorld* world); 
    ~FrackMan();
    virtual void doSomething();
    virtual void annoy(int amt);
    virtual int getTheID();
    
    int getSquirtsLeftInSquirtGun();
    int getPlayerGoldCount();
    int getPlayerSonarChargeCount();
    int getNumberOfBarrelsRemainingToBePickedUp();
    void addToWaterCount(int amt);
    void decrementWater(){unitsOfWater--;};
    void addToGoldCount(int amt);
    void decrementNumberOfBarrels();
    int getHitPoints();
    void getNewSquirt();
    void addNumberOfBarrels(int amt);
    
private:
    int m_lives;
    int m_health;
    int m_hitPoints;
    int numSonarCharges;
    int unitsOfWater;
    int numGoldNuggets;
    int numBarrels;
};

class Protester:public Actor
{
public:
    Protester(int imageID, StudentWorld * world);
    virtual ~Protester();
    virtual void doSomething()=0;
    virtual void annoy(int amt)=0;
    virtual int getTheID()=0;
    bool movePossible(Direction d);
    bool inLineOfSight();
    virtual int numSquaresToMoveIn();
    void calculateWhereToMoveTo(int & x, int & y);
    bool isFacingFrackman();
    bool yell();
private:
    int m_tickCounter;
    int m_yellCounter;
    int m_stunCounter = 0;
    int numMovesBeforeTurn;
    bool leaveField;
    bool isStunned;
};

// Regular Protestor
class RegularProtester: public Protester
{
public:
    RegularProtester(StudentWorld * world);
    virtual ~RegularProtester();
    void addToGoldCount(int amt);
    virtual void doSomething();
    virtual void annoy(int amt);
    virtual int getTheID();
private:
    int m_hitPoints;
    int numSquaresMoveinDir;
    bool isInField;
    int ticksToWaitBetweenMoves;
    int nonRestingTickCounter;
    bool hasYelledinLastFF;
};

// Goodie class common base class for all pick uppable goods
class Goodie: public Actor
{
public:
    Goodie(int imageID,int startX, int startY,Direction dir, double size, unsigned int depth,StudentWorld* world);
    virtual ~Goodie();
private:
};

// Boulder Class
class Boulder: public Goodie
{
public:
    Boulder(int startX, int startY, StudentWorld * world);
    virtual ~Boulder();
    virtual void doSomething();
    virtual void annoy(int amt);
    virtual int getTheID();
    
    //virtual bool canActorsPassThroughMe() const;
    
private:
    int m_stable=0; // if 0 stable, if 1 waiting, 2 falling
    int counter;
};

//Water Class
class WaterPool: public Goodie
{
public:
    WaterPool(int x, int y, StudentWorld * world);
    virtual ~WaterPool();
    virtual void doSomething();
    virtual void annoy(int amt);
    virtual int getTheID();
    
private:
    bool isPickable;
    int tempState;
};

// SonarKit Class
class SonarKit: public Goodie
{
public: SonarKit(int x, int y, StudentWorld * world);
    virtual ~SonarKit();
    virtual void doSomething();
    virtual void annoy(int amt);
    virtual int getTheID();
    
private:
    int tempState;
};

// Gold Nuggets Class
class GoldNugget: public Goodie
{
public: GoldNugget(int startX, int startY,bool frack,bool prost,bool isPerm,int d,StudentWorld* world);
    virtual~GoldNugget();
    virtual void doSomething();
    virtual void annoy(int amt);
    virtual int getTheID();
    
private:
    bool isPickableByFrackMan;
    bool isPickableByProtester;
    int tempState;
    bool isPermanent;
};

// Squirts

class Squirt: public Goodie
{
public: Squirt(int startX, int startY, Direction d,StudentWorld * world);
    virtual void doSomething();
    virtual void annoy(int amt);
    virtual int getTheID();
    
    bool collision(Direction d);
    virtual ~Squirt();
    
private:
    int m_travelDistance;
};

// Barrels Class

class Barrel: public Goodie
{
public:
    Barrel(int startX, int startY,StudentWorld * world);
    virtual ~Barrel();
    virtual void doSomething();
    virtual void annoy(int amt);
    virtual int getTheID();
    
private:
};
#endif // ACTOR_H_
