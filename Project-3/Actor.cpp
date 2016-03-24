#include "Actor.h"
#include "StudentWorld.h"
#include "GameController.h"
#include <algorithm>
#include <queue>

// Squirt Part

Squirt::Squirt(int startX, int startY,Direction d,StudentWorld * world):Goodie(IID_WATER_SPURT,startX,startY,d,1,1,world)
{
    setVisible(true);
    m_travelDistance=4;
}
Squirt::~Squirt()
{}
int Squirt::getTheID()
{
    return IID_WATER_SPURT;
}
void Squirt::annoy(int amt)
{}
void Squirt::doSomething()
{
    StudentWorld* studW=getWorld();
    
    vector<Actor*> temp;
    studW->compareAllRadius(IID_HARD_CORE_PROTESTER, getX(), getY(), 3, temp);
    studW->compareAllRadius(IID_PROTESTER, getX(), getY(), 3, temp);
    if (getCounter()<4)
    {
        incrementCounter();
        for (int i=0; i<temp.size(); i++)
        {
            temp[i]->annoy(2);
            setAlive(false);
        }
        int x=getX(),y=getY();
        getCoordinates(x, y, getDirection(), 1);
    }
    
   else
    {
        setAlive(false);
    }
    int dir=getDirection();
    int x=getX();
    int y=getY();
    switch (dir)
    {
        case up:
            if (isValidLocToMoveTo(x, y) &&!studW->isDirtPresent( x, y) && !studW->isBoulder(x,y))
            {
                moveTo(getX(), getY()+1);
                m_travelDistance++;
            }
            break;
            
        case down:
            if (isValidLocToMoveTo(x, y) &&!studW->isDirtPresent( x, y) && !studW->isBoulder(x,y))
            {
                moveTo(getX(), getY()-1);
                m_travelDistance++;
            }
            break;
            
        case left:
            if (isValidLocToMoveTo(x, y) &&!studW->isDirtPresent( x, y) && !studW->isBoulder(x,y))
            {
                moveTo(getX()-1, getY());
                m_travelDistance++;
            }
            break;
            
        case right:
            if (isValidLocToMoveTo(x, y) &&!studW->isDirtPresent( x, y) && !studW->isBoulder(x,y))
            {
                moveTo(getX()+1, getY());
                m_travelDistance++;
            }
            break;
    }
   }
 //Barrel of Oil

Barrel::Barrel(int startX, int startY, StudentWorld * world):Goodie(IID_BARREL,startX, startY, right,1,2, world)
{
}
Barrel::~Barrel()
{}
int Barrel::getTheID()
{
    return IID_BARREL;
}
void Barrel::doSomething()
{
    if (!isAlive())
    {
        return;
    }
    incrementCounter();
    StudentWorld *studW=getWorld();
    
    if (studW->isRadiusLengthLess(studW->getFrack()->getX(),studW->getFrack()->getY(),getX(),getY(),4))
    {
        setVisible(true);
        if (studW->isRadiusLengthLess(studW->getFrack()->getX(),studW->getFrack()->getY(),getX(),getY(),3))
        {
            setAlive(false);
            GameController::getInstance().playSound(SOUND_FOUND_OIL);
            studW->increaseScore(1000);
            studW->decrementNumberOfBarrels();
        }
        return;
    }
    
}
void Barrel::annoy(int amt)
{}
/*
 Barrels can’t be attacked and will not block Squirts from the FrackMan’s squirt gun
 (they pass right over the Barrels).
 */
// Actor Part

Actor::Actor(int imageID,int startX, int startY,Direction dir, double size, unsigned int depth,StudentWorld * world):GraphObject(imageID,startX,startY,right,size,depth)
{
    setVisible(false);
    m_isAlive=true;
    m_world=world;
    m_counter=0;
}

void Actor::annoy(int amt)
{}
void Actor::getCoordinates(int &x, int& y, GraphObject::Direction d, int numSteps)
{
    if (d==up)
    {
        y+=numSteps;
    }
    else if (d==down)
    {
        y-=numSteps;
    }
    else if (d==left)
    {
        x-=numSteps;
    }
    else if (d==right)
    {
        x+=numSteps;
    }
}
bool Actor::isValidLocToMoveTo(int xLoc, int yLoc)
{
    if (!(xLoc>=0 && xLoc<=60 && yLoc>=0 && yLoc<=60))
    {
        return false;
    }
    return true;
}
bool Actor::isAlive()
{
    return m_isAlive;
}
void Actor::setAlive(bool res)
{
    m_isAlive=res;
}
void Actor::incrementCounter()
{
    m_counter++;
}
int Actor::getCounter()
{
    return m_counter;
}

Actor::~Actor()
{}
bool Actor::moveDirection(GraphObject::Direction d)
{
    if (d==up)
    {
        if(isValidLocToMoveTo(getX(), getY()+1))
        {
            moveTo(getX(), getY()+1);
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (d==down)
    {
        if(isValidLocToMoveTo(getX(), getY()-1))
        {
            moveTo(getX(), getY()-1);
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (d==left)
    {
        if(isValidLocToMoveTo(getX()-1, getY()))
        {
            moveTo(getX()-1, getY());
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (d==right)
    {
        if(isValidLocToMoveTo(getX()+1, getY()))
        {
            moveTo(getX()+1, getY());
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
    
}
StudentWorld* Actor:: getWorld()
{
    return m_world;
}

// Frackman Part
FrackMan::FrackMan(StudentWorld* world):Actor(IID_PLAYER, 30, 60,right,1,0,world)
{
    setVisible(true);
    m_hitPoints=10;
    numSonarCharges=1;
    unitsOfWater=5;
    numGoldNuggets=0;
    numBarrels=0;
}
void FrackMan::addNumberOfBarrels(int amt)
{
    numBarrels+=amt;
}
int FrackMan::getTheID()
{
    return IID_PLAYER;
}
void FrackMan::decrementNumberOfBarrels()
{
    numBarrels--;
}
int FrackMan::getHitPoints()
{
    return m_hitPoints;
}
FrackMan::~FrackMan()
{}
void FrackMan::addToWaterCount(int amt)
{
    unitsOfWater+=amt;
}
void FrackMan::addToGoldCount(int amt)
{
    numGoldNuggets+=amt;
}
int FrackMan::getSquirtsLeftInSquirtGun()
{
    return unitsOfWater;
}
int FrackMan::getPlayerGoldCount()
{
    return numGoldNuggets;
}
int FrackMan::getPlayerSonarChargeCount()
{
    return numSonarCharges;
}
int FrackMan::getNumberOfBarrelsRemainingToBePickedUp()
{
    return numBarrels;
}
void FrackMan::annoy(int amt)
{
    m_hitPoints-=amt;
    if (m_hitPoints<=0)
    {
        setAlive(false);
        getWorld()->playSound(SOUND_PLAYER_GIVE_UP);
    }
}

void FrackMan::doSomething()
{
    if (!isAlive()) // If not currently alive
    {
        return;
    }
    int result=0;
    bool res=false;
    StudentWorld *studW=getWorld();
    vector<Actor*> temp;
    studW->compareAllRadius(IID_BOULDER, getX(), getY(), 3, temp);
    bool canMove=true;
    
    // removes all the dirt in the 4x4 square
    for(int i=0;i<4;i++)
    {
        for (int j=0; j<4; j++)
        {
            studW->removeDirt(getX()+i, getY()+j,res);
        }
    }
    // make a digging sound
    if (res)
    {
        GameController::getInstance().playSound(SOUND_DIG);
    }
    if (temp.size()>0)
    {
        canMove=false;
    }
    if (studW->getKey(result))
    {
        switch (result)
        {
            case KEY_PRESS_ESCAPE:
                setAlive(false);
                break;
            case KEY_PRESS_SPACE:
                if (unitsOfWater>0)
                {
                    int x=getX();
                    int y=getY();
                    getCoordinates(x, y, getDirection(), 4);
                    
                    if (studW->isDirtPresent(x, y) || temp.size()!=0)
                    {
                        GameController::getInstance().playSound(SOUND_PLAYER_SQUIRT);
                        unitsOfWater--;
                    }
                    else
                    {
                        Squirt* s1=new Squirt(x, y, getDirection(), studW);
                        studW->addActortoGame(s1);
                        unitsOfWater--;
                        GameController::getInstance().playSound(SOUND_PLAYER_SQUIRT);
                    }
                }
                break;
            case KEY_PRESS_UP:
                if (getDirection()==up)
                {
                    if(isValidLocToMoveTo(getX(), getY()+1) && canMove)
                    {
                        moveTo(getX(), getY()+1);
                    }
                }
                else
                {
                    setDirection(up);
                }
                break;
            case KEY_PRESS_DOWN:
                if (getDirection()==down)
                {
                    if(isValidLocToMoveTo(getX(), getY()-1) && canMove)
                    {
                        moveTo(getX(), getY()-1);
                    }
                }
                else
                {
                    setDirection(down);
                }
                break;
            case KEY_PRESS_RIGHT:
                if (getDirection()==right)
                {
                    if(isValidLocToMoveTo(getX()+1, getY()) && canMove)
                    {
                        moveTo(getX()+1, getY());
                    }
                }
                else
                {
                    setDirection(right);
                }
                break;
            case KEY_PRESS_LEFT:
                if (getDirection()==left)
                {
                    if(isValidLocToMoveTo(getX()-1, getY()) && canMove)
                    {
                        moveTo(getX()-1, getY());
                    }
                }
                else
                {
                    setDirection(left);
                }
                break;
            case 'Z':
            case 'z':
                if (numSonarCharges>0)
                {
                    numSonarCharges--;
                    vector<Actor*> temp1;
                    studW->compareAllRadius(IID_GOLD, getX(), getY(), 12, temp1);
                    studW->compareAllRadius(IID_BARREL, getX(), getY(), 12, temp1);
                    
                    for (int i=0; i<temp1.size(); i++)
                    {
                        temp1[i]->setVisible(true);
                    }
                }
                break;
            case KEY_PRESS_TAB:
                if (numGoldNuggets>0)
                {
                    GoldNugget * n=new GoldNugget(getX(), getY(), false, true, false, 100, getWorld());
                    n->setVisible(true);
                    studW->addActortoGame(n);
                    numGoldNuggets--;
                }
                break;
        }
    }
}

// Goodie Part

Goodie::Goodie(int imgID, int startX, int startY,Direction dir, double size, unsigned int depth,StudentWorld * world):Actor(imgID,startX,startY,dir,size,depth,world)
{
}
Goodie::~Goodie()
{}
// Dirt Part

Dirt::Dirt(int startX, int startY,StudentWorld* world):Actor(IID_DIRT, startX, startY,right,.25,3,world)
{
    setVisible(true);
}
int Dirt::getTheID()
{
    return IID_DIRT;
}
Dirt::~Dirt(){}
void Dirt::doSomething(){}
void Dirt::annoy(int amt){}
// Boulder Part
Boulder::Boulder(int startX, int startY,StudentWorld* world):Goodie(IID_BOULDER,startX,startY,down,1,1,world)
{
    setVisible(true);
    m_stable=0;
    counter=0;
}
Boulder::~Boulder()
{}
int Boulder::getTheID()
{
    return IID_BOULDER;
}
void Boulder::doSomething()
{
    if (!isAlive())
    {
        return;
    }
    StudentWorld *studW=getWorld();

    bool res;
    for(int i=0;i<4;i++)
    {
        for (int j=0; j<4; j++)
        {
            studW->removeDirt(getX()+i, getY()+j,res);
        }
    }

    if (m_stable==0)
    {
        for (int i =0; i < 4; i++)
        {
            if (studW->isDirtPresent(getX()+i, getY() - 1))
            {
                return;
            }
        }
    }
    m_stable=1;
    if (getCounter()<=30)
    {
        incrementCounter();
        return;
    }
    else
    {
        m_stable=2;
        GameController::getInstance().playSound(SOUND_FALLING_ROCK);
    }
    bool isBoulder=false;
    
    vector<Actor*> temp, temp1;
    studW->compareAllRadius(IID_BOULDER, getX(), getY(), 3, temp);
    studW->compareAllRadius(IID_HARD_CORE_PROTESTER, getX(), getY(), 3, temp1);
    studW->compareAllRadius(IID_PROTESTER, getX(), getY(), 3, temp1);

    if (m_stable==2)
    {
        moveTo(getX(), getY()-1);
        for (int i=0; i<temp.size(); i++)
        {
            isBoulder=true;
        }
        for (int i=0; i<temp1.size(); i++)
        {
            temp1[i]->annoy(100);
        }
        if (studW->isRadiusLengthLess(studW->getFrack()->getX(), studW->getFrack()->getY(), getX(), getY(),3))
        {
            studW->getFrack()->annoy(100);
            studW->decLives();
        }
        if (!isValidLocToMoveTo(getX(), getY()-1) || studW->isDirtPresent(getX(), getY()-1) || isBoulder)
        {
            setAlive(false);
        }
    }
}
void Boulder::annoy(int amt)
{}
GoldNugget::GoldNugget(int startX, int startY,bool frack,bool prost,bool isPerm,int d,StudentWorld* world):Goodie(IID_GOLD,startX,startY,right,1,2,world)
{
    isPickableByFrackMan=frack;
    isPickableByProtester=prost;
    isPermanent=isPerm;
    tempState=d;
}
GoldNugget::~GoldNugget()
{
}
int GoldNugget::getTheID()
{
    return IID_GOLD;
}
void GoldNugget::doSomething()
{
    incrementCounter();
    StudentWorld *studW=getWorld();
    vector<Actor*> temp;
    if (!isAlive()) // If not currently alive
    {
        return;
    }
    if (studW->isRadiusLengthLess(studW->getFrack()->getX(),studW->getFrack()->getY(), getX(), getY(),4))
    {
        setVisible(true);
        if (isPickableByFrackMan && studW->isRadiusLengthLess(studW->getFrack()->getX(), studW->getFrack()->getY(), getX(), getY(),3))
        {
            setAlive(false);
            GameController::getInstance().playSound(SOUND_GOT_GOODIE);
            studW->increaseScore(10);
            studW->getFrack()->addToGoldCount(1);
        }

        return;
    }
    
    
    studW->compareAllRadius(IID_HARD_CORE_PROTESTER, getX(), getY(), 3, temp);
    studW->compareAllRadius(IID_PROTESTER, getX(), getY(), 3, temp);
    if (temp.size()!=0 )
    {
        if(isPickableByProtester)
        {
            setAlive(false);
            GameController::getInstance().playSound(SOUND_PROTESTER_FOUND_GOLD);
            studW->increaseScore(25);
        }
        if (!isPermanent && getCounter()==tempState)
        {
            setAlive(false);
        }
    }
    /*
     Gold Nuggets can’t be attacked and will not block Squirts from the FrackMan’s squirt
     gun (they pass right over the Nuggets).
     */
}
void GoldNugget::annoy(int amt)
{
}

// SonarKit
SonarKit::SonarKit(int x, int y, StudentWorld * world):Goodie(IID_SONAR, x, y,right,1,2,world)
{
    setVisible(true);
}
SonarKit::~SonarKit()
{
}
int SonarKit::getTheID()
{
    return IID_SONAR;
}
void SonarKit::doSomething()
{
    if (!isAlive()) // If not currently alive
    {
        return;
    }
    incrementCounter();
    StudentWorld *studW=getWorld();
    tempState=studW->max(100,300-10*(studW->getLevel()));
    
    if (studW->isRadiusLengthLess(studW->getFrack()->getX(),studW->getFrack()->getY(), getX(), getY(),3))
    {
        setAlive(false);
        GameController::getInstance().playSound(SOUND_GOT_GOODIE);
        studW->increaseScore(75);
    }
    if (tempState==getCounter())
    {
        setAlive(false);
    }
    
    /*
     Sonar Kits can’t be annoyed and will not block Squirts from the FrackMan’s squirt gun.
     */
}
void SonarKit::annoy(int amt)
{
    
}
WaterPool::WaterPool(int x, int y, StudentWorld * world):Goodie(IID_WATER_POOL,x,y,right,1,2,world)
{
    setVisible(true);
}
WaterPool::~WaterPool()
{}
int WaterPool::getTheID()
{
    return IID_WATER_POOL;
}
void WaterPool::doSomething()
{
    if (!isAlive()) // If not currently alive
    {
        return;
    }
    incrementCounter();
    StudentWorld *studW=getWorld();
    tempState=studW->max(100, 300 -10*studW->getLevel());
    if (tempState==getCounter())
    {
        setAlive(false);
        return;
    }

    if (studW->isRadiusLengthLess(studW->getFrack()->getX(),studW->getFrack()->getY(), getX(), getY(),3))
    {
        setAlive(false);
        GameController::getInstance().playSound(SOUND_GOT_GOODIE);
        studW->increaseScore(100);
    }
    //Water Pools can’t be annoyed and will not block Squirts from the FrackMan’s squirt gun.
}
void WaterPool::annoy(int amt)
{}

// Protesters

Protester::Protester(int imageID, StudentWorld * world):Actor(imageID,60,60,left,1,0,world)
{
    m_tickCounter = 0;
    m_stunCounter = 0;
    m_yellCounter = 15;
    numMovesBeforeTurn = rand() % 52 + 8;
    leaveField = false;
    isStunned= false;
    setVisible(true);
}
Protester::~Protester(){};

bool Protester::movePossible(Direction d)
{
    bool canMove = movePossible(d);
    StudentWorld * studW=getWorld();
    
    if (!canMove)
    {
        return false;
    }
    else
    {
        canMove = true;
    }
    switch (d)
    {
        case left:
            for (int i = 0; i < 4; i++)
            {
                if (studW->isDirtPresent(getX() - 1, getY() + i))
                {
                    canMove=false;
                }
            }
            break;
        case right:
            for (int i = 0; i < 4; i++)
            {
                if (studW->isDirtPresent(getX() + 4, getY() + i))
                {
                    canMove=false;
                }
            }
            break;
        case up:
            for (int i = 0; i < 4; i++)
            {
                if (studW->isDirtPresent(getX() + i, getY() + 4))
                {
                    canMove=false;
                }
            }
            break;
        case down:
            for (int i = 0; i < 4; i++)
            {
                if (studW->isDirtPresent(getX() + i, getY() - 1))
                {
                    canMove = false;
                }
            }
            break;
        default:
            canMove = true;
            break;
    }
    
    return canMove;
}
bool Protester::inLineOfSight()
{
    StudentWorld * studW=getWorld();
    
    int xComponent = getX() - studW->getFrack()->getX();
    int yComponent = getY() - studW->getFrack()->getY();
    
    switch (getDirection())
    {
        case left:
            if (xComponent >= 0 && xComponent <= 4)
            {
                if (abs(yComponent)<=3)
                {
                    return true;
                }
            }
            break;
        case right:
            if (xComponent >= -4 && xComponent <= 0)
            {
                if (abs(yComponent)<=3)
                {
                    return true;
                }
            }
            break;
        case up:
            if (abs(xComponent)<=3)
            {
                if (yComponent >= -4 && yComponent <= 0)
                {
                    return true;
                }
            }
            break;
        case down:
            if (abs(xComponent)<=3)
            {
                if (yComponent >= 0 && yComponent <= 4)
                {
                    return true;
                }
            }
            break;
    }
    return false;
}
void Protester::annoy(int amt)
{
    if (leaveField)
    {
        return;
    }
}

bool Protester::yell()
{
    StudentWorld * studW=getWorld();
    if (studW->isRadiusLengthLess(getX(), getY(), studW->getFrack()->getX(), studW->getFrack()->getY(), 4))
    {
        if (inLineOfSight())
        {
            if (m_yellCounter>15)
            {
                m_yellCounter=0;
                studW->playSound(SOUND_PROTESTER_YELL);
                studW->getFrack()->annoy(2);
                return true;
            }
                return false;
        }
    }
    return false;
}
RegularProtester::RegularProtester(StudentWorld* world):Protester(IID_PROTESTER,world)
{
    m_hitPoints=5;
    numSquaresMoveinDir=numSquaresToMoveIn();
    isInField=false; // False or true
    ticksToWaitBetweenMoves = getWorld()->max(0, 3-getWorld()->getLevel()/4);
    nonRestingTickCounter=0;
    hasYelledinLastFF=false;
}
RegularProtester::~RegularProtester() {};

int Protester::numSquaresToMoveIn()
{
    return 1;
    //numSquaresToMoveInCurrentDirection, it will decide to move left before possibly switching its direction. This value must be: 8 <= numSquaresToMoveInCurrentDirection <= 60
}
void RegularProtester::doSomething()
{
    incrementCounter();
    StudentWorld *studW=getWorld();
    if (getCounter()%ticksToWaitBetweenMoves!=0)
    {
        return;
    }
    else
    {
        nonRestingTickCounter++;
        if (!isAlive()) // If not currently alive
        {
            return;
        }

        if (isInField)
        {
            if (getX()==60 && getY()==60)
            {
                setAlive(false);
            }
            else
            {
                int x, y;
                calculateWhereToMoveTo(x, y);
                moveTo(x, y);
                return;
            }
        }
            if (studW->isRadiusLengthLess(getX(), getY(), studW->getFrack()->getX(), studW->getFrack()->getY(), 4&& isFacingFrackman())&& !hasYelledinLastFF)
            {
                studW->playSound(SOUND_PROTESTER_YELL);
                studW->getFrack()->annoy(2);
                hasYelledinLastFF=true;
                return;
            }
            //           AND they are currently facing in the FrackMan’s direction2. If both are true and the Regular Protester hasn’t shouted within its last non-resting 15 ticks3, then the Regular Protester will:
            //           c. Update some state variable in a manner that prevents this Regular Protester from shouting again for at least 15 non-resting ticks.
        
    }
}
bool Protester::isFacingFrackman()
{
    return true;
}

void RegularProtester::annoy(int amt)
{
    
}
int RegularProtester::getTheID()
{
    return IID_PROTESTER;
}
void Protester::calculateWhereToMoveTo(int &x, int &y)
{
//    queue<Coord> coordQueue;
//    coordQueue.push(Coord (sr,sc));
//    maze[sr][sc]='F';
//    
//    while (!coordQueue.empty())
//    {
//        Coord a=coordQueue.front();
//        
//        coordQueue.pop();
//        
//        if (a.c()==ec && a.r()==er)
//        {
//            return true;
//        }
//        if(maze[a.r()-1][a.c()]=='.')
//        {
//            maze[a.r()-1][a.c()]='F';
//            coordQueue.push(Coord(a.r()-1,a.c()));
//        }
//        if(maze[a.r()+1][a.c()]=='.')
//        {
//            maze[a.r()+1][a.c()]='F';
//            coordQueue.push(Coord(a.r()+1,a.c()));
//        }
//        if(maze[a.r()][a.c()-1]=='.')
//        {
//            maze[a.r()][a.c()-1]='F';
//            coordQueue.push(Coord(a.r(),a.c()-1));
//        }
//        if(maze[a.r()][a.c()+1]=='.')
//        {
//            maze[a.r()][a.c()+1]='F';
//            coordQueue.push(Coord(a.r(),a.c()+1));
//        }
//    }
//  return false;
}

    //    Otherwise, the Regular Protester must move one square closer to its exit point (at x=60, y=60). It must determine what direction to move based on a queue-based maze-searching algorithm like the one we learned in class. The Regular Protester may not walk through Dirt or Boulders to reach its exit point (meaning that none of the 16 squares that comprise the 4x4 Regular Protester icon may overlap with a Dirt object and that the Regular Protester must not come within (within means <=) a distance of 3.0 units of any Boulders). Hint: It’s inefficient for every single Regular Protester to try to figure out its own optimal path to the exit, so see if you can figure out a way to compute a single data structure that enables all Protesters to quickly determine their optimal path to their common exit point of 60,60, no matter where they are located in the oil field.

// Regular Protesters