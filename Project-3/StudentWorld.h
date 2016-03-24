#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
#include "Actor.h"
#include <cmath>
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir)
    : GameWorld(assetDir)
    {
    }
    virtual int init()
    {
        //B Boulders in each level, where:
        int B = min(GameWorld::getLevel()/ 2 + 2, 6);
        //G Gold Nuggets in each level, where:
        int G = max(5-GameWorld::getLevel() / 2, 2);
        //L Barrels of oil in each level, where:
        int L = min(2 + GameWorld::getLevel(), 20);
        
        m_frackman=new FrackMan(this);
        m_frackman->addNumberOfBarrels(B);
        m_actor.push_back(m_frackman); // Adds it to the list of actors
        
        // Adds dirt at the specified locations
        // Delete something that hasnt been allocated
        for (int i=0; i<VIEW_WIDTH; i++)
        {
            for (int j=0; j<VIEW_HEIGHT; j++)
            {
                if (i>=30 && i<=33)
                {
                    if (j<4) // If not in the middle or not part of the mine shaft
                    {
                        m_dirt[i][j]=new Dirt(i,j,this);
                    }
                    else
                    {
                        m_dirt[i][j]=nullptr;
                    }
                }
                else
                {
                    if(j>=VIEW_HEIGHT-SPRITE_HEIGHT)
                    {
                        m_dirt[i][j]=nullptr;
                    }
                    else
                    {
                        m_dirt[i][j]=new Dirt(i,j,this);
                    }
                }
            }
        }
        
        // Removes dirt at the specified locations
        bool dummy;
        for (int i=30; i<34; i++)
        {
            for (int j=4; j<57; j++)
            {
                removeDirt(i,j,dummy);
            }
        }
        int i=B;
        while (i>0)
        {
            bool isPossibleB=true;

            int x=rand()%61;
            int y=rand()%37+20;
            
            for(int i=0;i<m_actor.size();i++)
            {
                if ((isRadiusLengthLess(x, y, m_actor[i]->getX(), m_actor[i]->getY(),6)))
                {
                    isPossibleB=false;
                    break;
                }
            }
            if(x>26 && x<34)
            {
                isPossibleB=false;
            }
            if(isPossibleB)
            {
                Boulder* b=new Boulder(x,y,this);
                m_actor.push_back(b);
                i--;
            }
            
        }
        int j=G;
        while (j>0)
        {
            bool isPossibleG=true;

            int x=rand()%61;
            int y=rand()%37+20;
            for(int i=0;i<m_actor.size();i++)
            {
                if ((isRadiusLengthLess(x, y, m_actor[i]->getX(), m_actor[i]->getY(),6)))
                {
                    isPossibleG=false;
                    break;
                }
            }
            if(x>26 && x<34)
            {
                isPossibleG=false;
            }
            if(isPossibleG)
            {
                GoldNugget* n=new GoldNugget(x,y,true,false,true,0,this);
                m_actor.push_back(n);
                j--;
            }
            
        }
        int k=L;
        while (k>0)
        {
            bool isPossibleL=true;

            int x=rand()%61;
            int y=rand()%37+20;
            for(int i=0;i<m_actor.size();i++)
            {
                if ((isRadiusLengthLess(x, y, m_actor[i]->getX(), m_actor[i]->getY(),6)))
                {
                    isPossibleL=false;
                    break;
                }
            }
            if(x>26 && x<34)
            {
                isPossibleL=false;
            }

            if(isPossibleL)
            {
                Barrel *c=new Barrel(x, y, this);
                m_actor.push_back(c);
                k--;
            }
        }
        return GWSTATUS_CONTINUE_GAME;
    }
    
    virtual int move()
    {
        
        for(int i=0;i<m_actor.size();i++)
        {
            if (m_actor[i]->isAlive())
            {
                // ask each actor to do something (e.g. move)
                m_actor[i]->doSomething();
                
                                if (theplayerDiedDuringThisTick() == true)
                                {
                                    playSound(SOUND_PLAYER_GIVE_UP);
                                    decLives();
                                    return GWSTATUS_PLAYER_DIED;
                                }
                                 //Remove newly-dead actors after each tick
                
                                if (theplayerCompletedTheCurrentLevel() == true)
                                {
                                    return GWSTATUS_FINISHED_LEVEL;
                                }
            }
        }
                if (theplayerDiedDuringThisTick() == true)
                {
                    playSound(SOUND_PLAYER_GIVE_UP);
                    decLives();
                    return GWSTATUS_PLAYER_DIED;
                }
                if (theplayerCompletedTheCurrentLevel() == true)
                {
                    playSound(SOUND_FINISHED_LEVEL);
                    return GWSTATUS_FINISHED_LEVEL;
                }
     
        // ADD NEW ACTORS
        int G=getLevel()*25+300;
        int num=rand()%G;
        if (num==G)
        {
            int num1=rand()%5;
            if(num1==4)
            {
                WaterPool * w=new WaterPool(0, 60, this);
                m_actor.push_back(w);
            }
            else
            {
                SonarKit* k=new SonarKit(0, 60, this);
                m_actor.push_back(k);
            }
        }
        removeDeadObjects(); // delete dead game objects

        setDisplayText();

        return GWSTATUS_CONTINUE_GAME;
    }

    virtual void cleanUp()
    {
        vector<Actor*>::iterator it;
        it=m_actor.begin();
        
        while (it!=m_actor.end())
        {
            delete *it;
            it=m_actor.erase(it);
        }
        
        for (int i=0; i<VIEW_WIDTH; i++)
        {
            for (int j=0; j<VIEW_HEIGHT; j++)
            {
                delete m_dirt[i][j];
            }
        }
    }
    void compareAllRadius(int ID,int x, int y,int rad, vector<Actor*>& nam)
    {
        for (int i=0; i<m_actor.size(); i++)
        {
            if (m_actor[i]->getTheID()==ID && isRadiusLengthLess(m_actor[i]->getX(), m_actor[i]->getY(),x,y,rad))
            {
                nam.push_back(m_actor[i]);
            }
        }
    }
    void addActortoGame(Actor* n)
    {
        m_actor.push_back(n);
    }
    
    StudentWorld(); // Constructor
    ~StudentWorld(); // Destructor
    
    void removeDirt(int xLoc, int yLoc,bool& removed);
    bool isDirtPresent(int x, int y);
    
    
    int min(int x, int y);
    int max(int x, int y);
    void setDisplayText();
    
    bool isRadiusLengthLess(int x, int y, int x1,int y1, int rad);
    FrackMan*  getFrack();
    
    int getSquirtsLeftInSquirtGun();
    int getPlayerGoldCount();
    int getPlayerSonarChargeCount();
    int getNumberOfBarrelsRemainingToBePickedUp();
    void addToWaterCount(int amt);
    void addToNumberOfBarrels(int amt);
    void addToGoldCount(int amt);
    void decrementNumberOfBarrels();
    bool isBoulder(int x, int y);
private:
    
    vector<Actor*> m_actor; // For all the objects except for the FrackMan and Dirt
    FrackMan* m_frackman; // For the Frackman
    Dirt* m_dirt [VIEW_WIDTH][VIEW_HEIGHT]; // For the dirt objects
    int m_level;
    
    bool theplayerDiedDuringThisTick();
    bool theplayerCompletedTheCurrentLevel();
    void removeDeadObjects();
    
    string organizeDisplayText(int a, int b,int c,int d, int e,int f,int g, int h);
};

#endif // STUDENTWORLD_H_