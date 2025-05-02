#pragma once
#include <KrakenEngine.hpp>

class Player
{
public:
    Player();
    ~Player() = default;

    void update(double dt);

    kn::Vec2 getPos() const;

    kn::Rect getRect() const;

    bool isAlive() const { return alive; }
    void kill() { alive = false; }

    void respawn()
    {
        alive = true;
        pos = kn::window::getSize() / 2;
        rect.center(pos);
    }

private:
    kn::AnimationController anim;
    kn::Rect rect;
    kn::Vec2 pos;
    const double speed = 100;
    bool alive = true;
};
