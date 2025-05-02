#pragma once
#include <KrakenEngine.hpp>

class Bullet
{
public:
    explicit Bullet(const kn::Vec2 &spawnPos);
    ~Bullet() = default;

    void move(double dt);
    bool outOfBounds() const;
    const kn::Vec2 &getPos() const;

    double radius = 5.0;

private:
    kn::Vec2 pos;
    kn::Vec2 direction;
    double speed = 200;
};
