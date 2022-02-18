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
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
//    decLives();
//    return GWSTATUS_PLAYER_DIED;
    
    int val = -1;
    getKey(val);
    peach->setKey(val);
    peach->doSomething();
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
}
