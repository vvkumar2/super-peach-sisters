#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp


//GraphObject(int imageID, int startX, int startY, int dir = 0, int depth = 0, double size = 1.0)

class StudentWorld;

class Actor: public GraphObject {
public:
    Actor(StudentWorld* w,
          int imageID,
          int x,
          int y,
          int dir,
          int depth,
          bool d,
          bool b,
          int size);
    
    virtual void doSomething () { return; }
    virtual void bonk () { return; };
    virtual void damage () {}
    
    void setAlive(bool a) { alive = a; }
    bool isAlive() { return alive; }
    bool isBlocking() { return blocking; }
    int getDir() { return direction; }
    void setDir(int a) { direction = a; }
    bool getDamageable() { return damageable; }
    StudentWorld* GetWorld() { return m_w; }
    
    ~Actor();
private:
    bool alive;
    bool damageable;
    bool blocking;
    int direction;
    StudentWorld* m_w;
};



class Peach: public Actor {
public:
    Peach(StudentWorld* w,
          int x,
          int y);
    ~Peach();
    void doSomething ();
    void bonk ();
    void setKey(int val);
    void giveFirePower () { firePower = true; }
    void giveStarPower () { starPower = true; }
    void giveJumpPower () { jumpPower = true; }
    void setHP (int x) { healthPoints = x; }
    
private:
    int healthPoints;
    bool jumpPower;
    bool firePower;
    bool starPower;
    int rechargeTime;
    int starTicks;
    int invincibilityTicks;
    int remaining_jump_distance;
    int key = -1;
};


class Block: public Actor {
public:
    Block(StudentWorld* w,
          int x,
          int y,
          char ch);
    ~Block();
    void bonk ();
private:
    char power = 'q';
    bool released;
};


class Pipe: public Actor {
public:
    Pipe(StudentWorld* w,
         int x,
          int y);
    ~Pipe();
    void doSomething ();
private:
};


class Flag: public Actor {
public:
    Flag(StudentWorld* w,
         int x,
          int y);
    ~Flag();
    void doSomething ();
private:
};


class Mario: public Actor {
public:
    Mario(StudentWorld* w,
          int x,
          int y);
    ~Mario();
    void doSomething ();
    void bonk () {};
private:
};

class Flower: public Actor {
public:
    Flower(StudentWorld* w,
           int x,
          int y);
    ~Flower();
    void doSomething ();
    void bonk () {};
private:
};


class Mushroom: public Actor {
public:
    Mushroom(StudentWorld* w,
             int x,
          int y);
    ~Mushroom();
    void doSomething ();
    void bonk () {};
private:
};


class Star: public Actor {
public:
    Star(StudentWorld* w,
         int x,
          int y);
    ~Star();
    void doSomething ();
    void bonk () {};
private:
};


class PiranhaFireball: public Actor {
public:
    PiranhaFireball(StudentWorld* w,
                    int x,
          int y, int d);
    ~PiranhaFireball();
    void doSomething ();
    void bonk () {};
private:
};


class PeachFireball: public Actor {
public:
    PeachFireball(StudentWorld* w,
                  int x,
          int y, int d);
    ~PeachFireball();
    void doSomething ();
    void bonk () {};
private:
};


class Shell: public Actor {
public:
    Shell(StudentWorld* w,
          int x,
          int y, int d);
    ~Shell();
    void doSomething ();
    void bonk () {};
private:
};

class Enemy: public Actor {
public:
    Enemy(StudentWorld* w,
           int imageID,
           int x,
           int y,
           int dir);
    ~Enemy();
    virtual void doSomething ();
    virtual void bonk ();
    virtual void damage ();
private:
};

class Goomba: public Enemy {
public:
    Goomba(StudentWorld* w,
           int x,
           int y,
           int dir);
    ~Goomba();
private:
};


class Koopa: public Enemy {
public:
    Koopa(StudentWorld* w,
          int x,
          int y,
          int dir);
    ~Koopa();
private:
};

class Piranha: public Actor {
public:
    Piranha(StudentWorld* w,
            int x,
            int y,
            int dir);
    ~Piranha();
    void doSomething ();
    void bonk () {};
private:
    int fr;
};
#endif // ACTOR_H_

