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
    int getInput (int val);
    
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
          int y, char ch);
    ~Block();
    void doSomething ();
    
private:
    char power = ' ';
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


class PiranhaFireball: public Actor {
public:
    PiranhaFireball(int x,
          int y, int d);
    ~PiranhaFireball();
    void doSomething ();
    
private:
};


class PeachFireball: public Actor {
public:
    PeachFireball(int x,
          int y, int d);
    ~PeachFireball();
    void doSomething ();
    
private:
};


class Shell: public Actor {
public:
    Shell(int x,
          int y, int d);
    ~Shell();
    void doSomething ();
    
private:
};


class Goomba: public Actor {
public:
    Goomba(int x,
          int y);
    ~Goomba();
    void doSomething ();
    
private:
};


class Koopa: public Actor {
public:
    Koopa(int x,
          int y);
    ~Koopa();
    void doSomething ();
    
private:
};

class Piranha: public Actor {
public:
    Piranha(int x,
          int y);
    ~Piranha();
    void doSomething ();
    
private:
};
#endif // ACTOR_H_

