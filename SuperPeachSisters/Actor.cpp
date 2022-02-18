#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor (int imageID, int x, int y, int dir=0, int depth=0, bool d = true, bool blocking = false, int size=1)
:GraphObject(imageID, x, y, dir, depth, size), damageable (d), alive(true) {}
Actor::~Actor() {};


Peach::Peach (int x, int y)
:Actor(IID_PEACH, x, y)
{
    healthPoints = 1;
    jumpPower = firePower = starPower = false;
    time_to_recharge_before_next_fire = 0;
    remaining_jump_distance = 0;
}
Peach::~Peach() {};
void Peach::doSomething()
{
    return;
}


Block::Block (int x, int y)
:Actor(IID_BLOCK, x, y, 0, 2, false, true), released (false), power(' ') {}
Block::~Block() {};
void Block::doSomething ()
{
    return;
}


Pipe::Pipe (int x, int y)
:Actor(IID_PIPE, x, y, 0, 2, false, true) {}
Pipe::~Pipe() {};
void Pipe::doSomething ()
{
    return;
}

Flag::Flag (int x, int y)
:Actor(IID_FLAG, x, y, 0, 1, false) {}
Flag::~Flag() {};
void Flag::doSomething ()
{
    return;
}


Mario::Mario (int x, int y)
:Actor(IID_MARIO, x, y, 0, 1, false) {}
Mario::~Mario() {};
void Mario::doSomething ()
{
    return;
}


Flower::Flower (int x, int y)
:Actor(IID_FLOWER, x, y, 0, 1, false) {}
Flower::~Flower() {};
void Flower::doSomething ()
{
    return;
}

Mushroom::Mushroom (int x, int y)
:Actor(IID_MUSHROOM, x, y, 0, 1, false) {}
Mushroom::~Mushroom() {};
void Mushroom::doSomething ()
{
    return;
}

Star::Star (int x, int y)
:Actor(IID_STAR, x, y, 0, 1, false) {}
Star::~Star() {};
void Star::doSomething ()
{
    return;
}

