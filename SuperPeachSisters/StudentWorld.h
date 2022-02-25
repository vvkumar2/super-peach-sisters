#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <vector>
using namespace std;

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    bool checkIfCanMove(int x, int y);
    Actor* objAtPosition(int x, int y);
    Peach* getPeach() { return peach; }
    bool isOverlapping(int x, int y);
    int peachX () { return peach->getX(); }
    int peachY () { return peach->getY(); }
    void addToVector (Actor* a) { actors.push_back(a); }
    void finishedLevel() { finished = true; }
    void wonGame() { won = true; }
private:
    vector <Actor*> actors;
    Peach* peach;
    bool finished = false;
    bool won = false;
};

#endif // STUDENTWORLD_H_
