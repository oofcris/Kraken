#pragma once
#include <KrakenEngine.hpp>
#include <vector>

class Bullet;

class TEnemy
{
public:
    TEnemy();
    ~TEnemy() = default;

    void update(double dt, const kn::Vec2 &target, const kn::Frame *frame);

    bool isDead(std::vector<Bullet> &bullets);

    kn::Vec2 getPos() const;

    double radius = 10.0;

private:
    kn::AnimationController anim;
    kn::Vec2 pos;
    kn::Rect rect;
    double speed = 2;
    int health = 3;
};
