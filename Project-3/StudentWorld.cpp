#include "StudentWorld.h"
#include <string>
using namespace std;
GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}


string StudentWorld::organizeDisplayText(int a, int b, int c, int d, int e, int f, int g, int h)
{
    string r;
    if(a/10<1)
    {
        r="00000"+to_string(a);
    }
    else if(a/100<1)
    {
        r="0000"+to_string(a);
    }
    else if(a/1000<1)
    {
        r="000"+to_string(a);
    }
    else if(a/10000<1)
    {
        r="00"+to_string(a);
    }
    else if(a/100000<1)
    {
        r="0"+to_string(a);
    }



    
    string result="Scr: "+r+"  Lvl: "+to_string(b)+"  Lives: "+to_string(c)+"  Hlth: "+to_string(d)+"%  Water: "+to_string(e)+"  Gld: "+to_string(f)+"  Sonar: "+to_string(g)+"  Oil Left: "+to_string(h);
    
    return result;
}
FrackMan * StudentWorld::getFrack()
{
    return m_frackman;
}
bool StudentWorld::theplayerDiedDuringThisTick()
{
    if (m_frackman->isAlive())
    {
        return false;
    }
    return true;
}
void StudentWorld::removeDeadObjects()
{
    vector<Actor*>::iterator it=m_actor.begin();
    while (it!=m_actor.end())
    {
        if (!(*it)->isAlive())
        {
            vector<Actor *>::iterator temp=it;
            delete *temp;
            it=m_actor.erase(temp);
        }
        else
        {
            it++;
        }
    }
    }
bool StudentWorld::theplayerCompletedTheCurrentLevel()
{
    if (getNumberOfBarrelsRemainingToBePickedUp()==0) // All oil is gathered
    {
        return true;
    }
    return false;
}

void StudentWorld::setDisplayText()
{
    int score = getScore();
    int level = getLevel();
    int lives = getLives();
    int health = (m_frackman->getHitPoints()/10)*100 ;
    int squirts = m_frackman->getSquirtsLeftInSquirtGun();
    int gold = m_frackman->getPlayerGoldCount();
    int sonar = m_frackman->getPlayerSonarChargeCount();
    int barrelsLeft = m_frackman->getNumberOfBarrelsRemainingToBePickedUp();
    // Next, create a string from your statistics, of the form:
    // “Scr: 0321000 Lvl: 52 Lives: 3 Hlth: 80% Water: 20 Gld: 3 Sonar: 1 Oil Left: 2”
    string s = organizeDisplayText(score, level, lives, health, squirts, gold, sonar, barrelsLeft);
    // Finally, update the display text at the top of the screen with your // newly created stats
    setGameStatText(s); // calls our provided GameWorld::setGameStatText
}
bool StudentWorld::isRadiusLengthLess(int x, int y, int x1, int y1, int rad)
{
    return sqrt(pow(x-x1, 2)+pow(y-y1, 2))<=rad;
}
void StudentWorld::removeDirt(int xLoc, int yLoc,bool& removed)
{
    if(m_dirt[xLoc][yLoc]!=nullptr)
    {
        delete m_dirt[xLoc][yLoc];
        m_dirt[xLoc][yLoc]=nullptr;
        removed=true;
    }
}
bool StudentWorld::isDirtPresent(int x, int y)
{
    if (m_dirt[x][y] == nullptr)
    {
        return false;
    }
    return true;
}
bool StudentWorld::isBoulder(int x, int y)
{
    for (int i=0; i<m_actor.size(); i++)
    {
        if (m_actor[i]->getID()==IID_BOULDER && m_actor[i]->getX()==x && m_actor[i]->getY()==y)
        {
            return true;
        }
    }
    return false;
}
int StudentWorld::min(int x, int y)
{
    if (y<=x)
    {
        return y;
    }
    return x;
}
int StudentWorld::max(int x, int y)
{
    if (y<=x)
    {
        return x;
    }
    return y;
}
int StudentWorld::getNumberOfBarrelsRemainingToBePickedUp()
{
    return m_frackman->getNumberOfBarrelsRemainingToBePickedUp();
}
int StudentWorld::getSquirtsLeftInSquirtGun()
{
    return m_frackman->getSquirtsLeftInSquirtGun();
}
void StudentWorld::decrementNumberOfBarrels()
{
    m_frackman->decrementNumberOfBarrels();
}
void StudentWorld::addToNumberOfBarrels(int amt)
{
    m_frackman->addNumberOfBarrels( amt);
}
StudentWorld::~StudentWorld()
{
    vector<Actor*>::iterator it;
    it=m_actor.begin();
    
    while (it!=m_actor.end())
    {
        it=m_actor.erase(it);
        it++;
    }
    for (int i=0; i<VIEW_WIDTH; i++)
    {
        for (int j=0; j<VIEW_HEIGHT; j++)
        {
            delete m_dirt[i][j];
        }
    }
}