#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor (StudentWorld* w, int imageID, int x, int y, int dir=0, int depth=0, bool d = true, bool b = false, int size=1)
:GraphObject(imageID, x, y, dir, depth, size), damageable (d), alive(true), blocking (b), direction(dir), m_w(w) {}
Actor::~Actor() {};


Peach::Peach (StudentWorld* w, int x, int y)
:Actor(w, IID_PEACH, x, y)
{
    healthPoints = 1;
    jumpPower = firePower = starPower = true;
    rechargeTime = 0;
    starTicks = invincibilityTicks = 0;
    remaining_jump_distance = 0;
}
Peach::~Peach() {};
void Peach::doSomething()
{
    if (!isAlive())
    {
        return;
    }
    int x = getX();
    int y = getY();
    
    if (starTicks > 0) starTicks--;
    if (invincibilityTicks > 0) invincibilityTicks--;
    if (rechargeTime > 0) rechargeTime--;
    
    if (remaining_jump_distance > 0)
    {
        if (GetWorld()->checkIfCanMove(x, y+4))
        {
            moveTo(getX(), getY()+4);
            remaining_jump_distance--;
        }
        else if (GetWorld()->objAtPosition(x, y+8) != nullptr)
        {
            GetWorld()->objAtPosition(x, y+8)->bonk();
            remaining_jump_distance = 0;
        }
    }
    if (remaining_jump_distance == 0)
    {
        if (GetWorld()->checkIfCanMove(x, y-1) && GetWorld()->checkIfCanMove(x, y-2) && GetWorld()->checkIfCanMove(x, y-3) && GetWorld()->checkIfCanMove(x, y-4))
        {
            moveTo(x, y-4);
        }
    }
    
    if (!GetWorld()->getKey(key))
    {
        return;
    }
    if (key == KEY_PRESS_LEFT)
    {
        if (GetWorld()->checkIfCanMove(x-4, y) && GetWorld()->checkIfCanMove(x-1, y))
        {
            setDirection(180);
            moveTo(getX()-4, getY());
        }
        else if (GetWorld()->objAtPosition(x-8, y) != nullptr)
        {
            GetWorld()->objAtPosition(x-8, y)->bonk();
        }
    }
    else if (key == KEY_PRESS_RIGHT)
    {
        if (GetWorld()->checkIfCanMove(x+4, y) && GetWorld()->checkIfCanMove(x+1, y))
        {
            setDirection(0);
            moveTo(getX()+4, getY());
        }
        else if (GetWorld()->objAtPosition(x+8, y) != nullptr)
        {
            GetWorld()->objAtPosition(x+8, y)->bonk();
        }
    }
    else if (key == KEY_PRESS_UP)
    {
        if (!GetWorld()->checkIfCanMove(x, y-1))
        {
            GetWorld()->playSound(SOUND_PLAYER_JUMP);
        }
        if (remaining_jump_distance == 0 && !GetWorld()->checkIfCanMove(x, y-1))
        {
            if (jumpPower)
                remaining_jump_distance = 12;
            else
                remaining_jump_distance = 8;
        }
    }
    else if (key == KEY_PRESS_SPACE)
    {
        if (firePower && rechargeTime == 0)
        {
            GetWorld()->playSound(SOUND_PLAYER_FIRE);
            rechargeTime = 8;
            if (getDirection() == 0)
            {
                GetWorld()->addToVector(new PeachFireball(GetWorld(), getX()+4, getY(), getDirection()));
            }
            else
            {
                GetWorld()->addToVector(new PeachFireball(GetWorld(), getX()-4, getY(), getDirection()));
            }
        }
    }
}

void Peach::bonk()
{
    if (invincibilityTicks > 0 || starTicks > 0)
    {
        return;
    }
    healthPoints--;
    invincibilityTicks = 10;
    if (firePower) firePower = false;
    if (jumpPower) jumpPower = false;
    if (healthPoints > 0)
    {
        GetWorld()->playSound(SOUND_PLAYER_HURT);
    }
    else
    {
        setAlive(false);
    }
}

void Peach::setKey (int val)
{
    key = val;
}


Block::Block (StudentWorld* w, int x, int y, char ch)
:Actor(w, IID_BLOCK, x, y, 0, 2, false, true), released (false), power(ch) {}
Block::~Block() {};
void Block::bonk ()
{
    if (power == 'q')
    {
        
        return;
    }
    if (!released)
    {
        released = true;
        GetWorld()->playSound(SOUND_POWERUP_APPEARS);
        if (power == '*')
        {
            GetWorld()->addToVector(new Star(GetWorld(), getX(), getY()+8));
        }
        else if (power == '%')
        {
            GetWorld()->playSound(SOUND_PLAYER_BONK);
            GetWorld()->addToVector(new Flower(GetWorld(), getX(), getY()+8));
        }
        else if (power == '^')
        {
            GetWorld()->addToVector(new Mushroom(GetWorld(), getX(), getY()+8));
        }
    }
}


Pipe::Pipe (StudentWorld* w, int x, int y)
:Actor(w, IID_PIPE, x, y, 0, 2, false, true) {}
Pipe::~Pipe() {};
void Pipe::doSomething ()
{
    return;
}

Flag::Flag (StudentWorld* w, int x, int y)
:Actor(w, IID_FLAG, x, y, 0, 1, false) {}
Flag::~Flag() {};
void Flag::doSomething ()
{
//    if (GetWorld()->isOverlapping(getX(), getY()))
//    {
//        GetWorld()->increaseScore(1000);
//        setAlive(false);
//        GetWorld()->finishedLevel();
//    }
    return;
}


Mario::Mario (StudentWorld* w, int x, int y)
:Actor(w, IID_MARIO, x, y, 0, 1, false) {}
Mario::~Mario() {};
void Mario::doSomething ()
{
    return;
}


Flower::Flower (StudentWorld* w, int x, int y)
:Actor(w, IID_FLOWER, x, y, 0, 1, false) {}
Flower::~Flower() {};
void Flower::doSomething ()
{
    if (GetWorld()->isOverlapping(getX(), getY()))
    {
        GetWorld()->increaseScore(50);
        GetWorld()->getPeach()->giveFirePower();
        GetWorld()->getPeach()->setHP(2);
        setAlive(false);
        GetWorld()->playSound(SOUND_PLAYER_POWERUP);
    }
    return;
}

Mushroom::Mushroom (StudentWorld* w, int x, int y)
:Actor(w, IID_MUSHROOM, x, y, 0, 1, false) {}
Mushroom::~Mushroom() {};
void Mushroom::doSomething ()
{
    if (GetWorld()->isOverlapping(getX(), getY()))
    {
        GetWorld()->increaseScore(75);
        GetWorld()->getPeach()->giveJumpPower();
        GetWorld()->getPeach()->setHP(2);
        setAlive(false);
        GetWorld()->playSound(SOUND_PLAYER_POWERUP);
    }
    return;
}

Star::Star (StudentWorld* w, int x, int y)
:Actor(w, IID_STAR, x, y, 0, 1, false) {}
Star::~Star() {};
void Star::doSomething ()
{
    if (GetWorld()->isOverlapping(getX(), getY()))
    {
        GetWorld()->increaseScore(100);
        GetWorld()->getPeach()->giveStarPower();
        GetWorld()->getPeach()->setHP(2);
        setAlive(false);
        GetWorld()->playSound(SOUND_PLAYER_POWERUP);
    }
    return;
}

PiranhaFireball::PiranhaFireball (StudentWorld* w, int x, int y, int d)
:Actor(w, IID_PIRANHA_FIRE, x, y, d, 1, false) {}
PiranhaFireball::~PiranhaFireball() {};
void PiranhaFireball::doSomething ()
{
    int x = getX();
    int y = getY();
    if (GetWorld()->isOverlapping(x, y))
    {
        GetWorld()->getPeach()->bonk();
        setAlive(false);
        return;
    }
    if (GetWorld()->checkIfCanMove(getX(), getY()-1) && GetWorld()->checkIfCanMove(getX(), getY()-2))
    {
        moveTo(getX(), getY()-2);
    }
    if (getDir() == 0 && GetWorld()->checkIfCanMove(getX()+1, getY()) && GetWorld()->checkIfCanMove(getX()+2, getY()))
    {
        moveTo(getX()+2, getY());
    }
    else if (getDir() == 180 && GetWorld()->checkIfCanMove(getX()-2, getY()) && GetWorld()->checkIfCanMove(getX()-2, getY()))
    {
        moveTo(getX()-2, getY());
    }
    else
    {
        setAlive(false);
        setVisible(false);
        return;
    }
    return;
}

PeachFireball::PeachFireball (StudentWorld* w, int x, int y, int d)
:Actor(w, IID_PEACH_FIRE, x, y, d, 1, false) {}
PeachFireball::~PeachFireball() {};
void PeachFireball::doSomething ()
{
    if (GetWorld()->objAtPosition(getX(), getY())!= nullptr && (GetWorld()->objAtPosition(getX(), getY())->getDamageable()))
    {
        GetWorld()->objAtPosition(getX(), getY())->damage();
        setAlive(false);
        return;
    }
    
    if (GetWorld()->checkIfCanMove(getX(), getY()-1) && GetWorld()->checkIfCanMove(getX(), getY()-2))
    {
        moveTo(getX(), getY()-2);
    }
    if (getDir() == 0 && GetWorld()->checkIfCanMove(getX()+1, getY()) && GetWorld()->checkIfCanMove(getX()+2, getY()))
    {
        moveTo(getX()+2, getY());
    }
    else if (getDir() == 180 && GetWorld()->checkIfCanMove(getX()-2, getY()) && GetWorld()->checkIfCanMove(getX()-2, getY()))
    {
        moveTo(getX()-2, getY());
    }
    else
    {
        setAlive(false);
        return;
    }
    return;
    
}

Shell::Shell (StudentWorld* w, int x, int y, int d)
:Actor(w, IID_SHELL, x, y, d, 1, false) {}
Shell::~Shell() {};
void Shell::doSomething ()
{
    return;
}

Enemy::Enemy (StudentWorld* w, int imageID, int x, int y, int dir)
:Actor(w, imageID, x, y, dir) {}

Enemy::~Enemy() {};

void Enemy::doSomething ()
{
    if (GetWorld()->isOverlapping(getX(), getY()))
    {
        GetWorld()->getPeach()->bonk();
        setAlive(false);
        return;
    }
    if (!this->isAlive())
    {
        return;
    }

    if ((getDir() == 0 && !GetWorld()->checkIfCanMove(getX()+1, getY())) ||
        (getDir() == 0 && GetWorld()->checkIfCanMove(getX()+1+SPRITE_WIDTH, getY()) && (GetWorld()->checkIfCanMove(getX()+1+SPRITE_WIDTH, getY()-1))))
    {
        setDir(180); setDirection(180);
    }
    else if (getDir() == 0 && GetWorld()->checkIfCanMove(getX()+1, getY()) && !(GetWorld()->checkIfCanMove(getX()+1+SPRITE_WIDTH, getY()-1)))
        moveTo(getX()+1, getY());
    
    if ((getDir() == 180 && !GetWorld()->checkIfCanMove(getX()-1, getY())) ||
        (getDir() == 180 && GetWorld()->checkIfCanMove(getX()-1, getY()) && (GetWorld()->checkIfCanMove(getX()-SPRITE_WIDTH, getY()-1))))
    {
        setDir(0); setDirection(0);
    }
    else if (getDir() == 180 && GetWorld()->checkIfCanMove(getX()-1, getY()) && !(GetWorld()->checkIfCanMove(getX()-SPRITE_WIDTH, getY()-1)))
        moveTo(getX()-1, getY());
}

void Enemy::bonk()
{
    GetWorld()->playSound(SOUND_PLAYER_KICK);
    GetWorld()->increaseScore(100);
    setAlive(false);
}

void Enemy::damage()
{
    GetWorld()->increaseScore(100);
    setAlive(false);
}

Goomba::Goomba (StudentWorld* w, int x, int y, int dir)
:Enemy(w, IID_GOOMBA, x, y, dir) {}

Goomba::~Goomba() {};

Koopa::Koopa (StudentWorld* w, int x, int y, int dir)
:Enemy(w, IID_KOOPA, x, y, dir) {}

Koopa::~Koopa() {};
 

Piranha::Piranha (StudentWorld* w, int x, int y, int dir)
:Actor(w, IID_PIRANHA, x, y, dir) { fr = 0; }
Piranha::~Piranha() {};
void Piranha::doSomething ()
{
    if (GetWorld()->isOverlapping(getX(), getY()))
    {
        GetWorld()->getPeach()->bonk();
        setAlive(false);
        return;
    }
    if (!isAlive())
        return;
    increaseAnimationNumber();
    
    int x = getX(), y = getY();
    if (GetWorld()->isOverlapping(x, y))
    {
        return;
    }
    
    if (abs(getY() - GetWorld()->peachY()) <= 1.5*SPRITE_HEIGHT)
    {
        if (getX() - GetWorld()->peachX() < 0)
        {
            setDir(0);
            setDirection(0);
        }
        else
        {
            setDir(180);
            setDirection(180);
        }
        
        if (fr != 0)
        {
            fr--;
            return;
        }
        else
        {
            if (abs(getX() - GetWorld()->peachX()) < 8*SPRITE_WIDTH)
            {
                
                GetWorld()->addToVector(new PiranhaFireball (GetWorld(), getX(), getY(), getDir()));
                GetWorld()->playSound(SOUND_PIRANHA_FIRE);
                fr = 40;
            }
        }
    }
    return;
}
