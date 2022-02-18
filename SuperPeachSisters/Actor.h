#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp


//GraphObject(int imageID, int startX, int startY, int dir = 0, int depth = 0, double size = 1.0)

class Actor: public GraphObject {
public:
    Actor(int imageID,
          int x,
          int y,
          int dir,
          int depth,
          bool d,
          bool blocking,
          int size);
    bool isAlive() { return alive; }
    virtual void doSomething () { return; }
    ~Actor();
private:
    bool alive;
    bool damageable;
};



class Peach: public Actor {
public:
    Peach(int x,
          int y);
    ~Peach();
    void doSomething ();
    
private:
    int healthPoints;
    bool jumpPower;
    bool firePower;
    bool starPower;
    int time_to_recharge_before_next_fire;
    int remaining_jump_distance;
};


class Block: public Actor {
public:
    Block(int x,
          int y);
    ~Block();
    void doSomething ();
    
private:
    char power;
    bool released;
};


class Pipe: public Actor {
public:
    Pipe(int x,
          int y);
    ~Pipe();
    void doSomething ();
    
private:
};


class Flag: public Actor {
public:
    Flag(int x,
          int y);
    ~Flag();
    void doSomething ();
    
private:
};


class Mario: public Actor {
public:
    Mario(int x,
          int y);
    ~Mario();
    void doSomething ();
    
private:
};

class Flower: public Actor {
public:
    Flower(int x,
          int y);
    ~Flower();
    void doSomething ();
    
private:
};


class Mushroom: public Actor {
public:
    Mushroom(int x,
          int y);
    ~Mushroom();
    void doSomething ();
    
private:
};


class Star: public Actor {
public:
    Star(int x,
          int y);
    ~Star();
    void doSomething ();
    
private:
};

#endif // ACTOR_H_
