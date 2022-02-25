#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <sstream>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

int StudentWorld::init()
{
    Level lev(assetPath());
    ostringstream oss;
    if (getLevel() < 10)
    {
        oss << "level0";
    }
    else
        oss << "level";
    oss << getLevel() << ".txt";
    cout << oss.str();
    
    string level_file = oss.str();
    
    Level::LoadResult result = lev.loadLevel(level_file); if (result == Level::load_fail_file_not_found)
    cerr << "Could not find level01.txt data file" << endl; else if (result == Level::load_fail_bad_format)
    cerr << "level01.txt is improperly formatted" << endl; else if (result == Level::load_success)
    cerr << "Successfully loaded level" << endl; Level::GridEntry ge;
    
    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            int width = SPRITE_WIDTH * i;
            int height = SPRITE_HEIGHT * j;
            
            ge = lev.getContentsOf(i, j); // x=5, y=10 switch (ge)
            switch (ge)
            {
                case Level::empty:
                    break;
                case Level::koopa:
                    int a;
                    if (rand() %2 ==1) a = 180; else a = 0;
                    actors.push_back(new Koopa(this, width, height, a)); break;
                case Level::goomba:
                    int b;
                    if (rand() %2 ==1) b = 180; else b = 0;
                    actors.push_back(new Goomba(this, width, height, b)); break;
                case Level::peach:
                    peach = new Peach(this, width, height);
                case Level::flag:
                    actors.push_back(new Flag(this, width, height)); break;
                case Level::star_goodie_block:
                    actors.push_back(new Block(this, width, height, '*')); break;
                case Level::flower_goodie_block:
                    actors.push_back(new Block(this, width, height, '%')); break;
                case Level::mushroom_goodie_block:
                    actors.push_back(new Block(this, width, height, '^')); break;
                case Level::block:
                    actors.push_back(new Block(this, width, height, 'q')); break;
                case Level::piranha:
                    int c;
                    if (rand() %2 ==1) c = 180; else c = 0;
                    actors.push_back(new Piranha(this, width, height, c)); break;
                case Level::pipe:
                    actors.push_back(new Pipe(this, width, height)); break;
                case Level::mario:
                    actors.push_back(new Mario(this, width, height)); break;
            }
        }
    }

    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    peach->doSomething();
    for (vector<Actor*>::iterator i = actors.begin(); i != actors.end(); i++)
    {
        Actor* a = *i;
        if (a != nullptr)
            a->doSomething();
    }
    
    if (!peach->isAlive())
    {
        playSound(SOUND_PLAYER_DIE);
        return GWSTATUS_PLAYER_DIED;
    }
    if (won)
    {
        return GWSTATUS_PLAYER_WON;
    }
    if (finished)
    {
        return GWSTATUS_FINISHED_LEVEL;
    }
    
    for (vector<Actor*>::iterator i = actors.begin(); i != actors.end(); i++)
    {
        Actor* a = *i;
        if (!a->isAlive())
        {
            actors.erase(i);
            i--;
            delete a;
        }
    }
    if (!peach->isAlive())
    {
        delete peach;
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    while (!actors.empty())
    {
        (*actors.begin())->setVisible(false);
        actors.erase(actors.begin());
    }
    delete peach;
}

bool StudentWorld::checkIfCanMove(int x, int y)
{
    for (vector<Actor*>::iterator i = actors.begin(); i != actors.end(); i++)
    {
        Actor* a = *i;
        int xx = a->getX();
        int yy = a->getY();
        
        if (a->isBlocking())
        {
            if ((abs(xx-x) < SPRITE_WIDTH) && (abs(yy-y) < SPRITE_HEIGHT))
            {
                return false;
            }
        }
        
    }
    return true;
}

bool StudentWorld::isOverlapping(int x, int y)
{
    int peachX = peach->getX();
    int peachY = peach->getY();
        
    if ((abs(peachX-x) < SPRITE_WIDTH) && (abs(peachY-y) < SPRITE_HEIGHT))
        return true;
    
    return false;
}
    
Actor* StudentWorld::objAtPosition(int x, int y)
{
    for (vector<Actor*>::iterator i = actors.begin(); i != actors.end(); i++)
    {
        Actor* a = *i;
        int xx = a->getX();
        int yy = a->getY();
        
        if (a->isBlocking())
        {
            if ((abs(xx-x) < SPRITE_WIDTH) && (abs(yy-y) < SPRITE_HEIGHT))
            {
                return a;
            }
        }
    }
    return nullptr;
}

