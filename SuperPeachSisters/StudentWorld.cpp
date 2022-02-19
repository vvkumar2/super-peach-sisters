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
                    actors.push_back(new Koopa(width, height)); break;
                case Level::goomba:
                    actors.push_back(new Goomba(width, height)); break;
                case Level::peach:
                    peach = new Peach(width, height);
                case Level::flag:
                    actors.push_back(new Flag(width, height)); break;
                case Level::block:
                    actors.push_back(new Block(width, height, ' ')); break;
                case Level::star_goodie_block:
                    actors.push_back(new Block(width, height, '*')); break;
                case Level::flower_goodie_block:
                    actors.push_back(new Block(width, height, '^')); break;
                case Level::mushroom_goodie_block:
                    actors.push_back(new Block(width, height, '+')); break;
                case Level::piranha:
                    actors.push_back(new Piranha(width, height)); break;
                case Level::pipe:
                    actors.push_back(new Pipe(width, height)); break;
                case Level::mario:
                    actors.push_back(new Mario(width, height)); break;
            }
        }
    }

    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    int val;
    getKey(val);
    
    int x = peach->getX();
    int y = peach->getY();
    
    if (val == KEY_PRESS_LEFT)
    {
        x = peach->getX() - 4;
    }
    else if (val == KEY_PRESS_RIGHT)
    {
        x = peach->getX() + 4;
    }
    
    bool move = checkIfCanMove(x, y);
    
    if (move)
    {
        peach->setKey(val);
        peach->doSomething();
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    while (actors.empty())
    {
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

