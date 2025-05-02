#include "Bullet.hpp"

Bullet::Bullet(const kn::Vec2 &spawnPos)
    : pos(spawnPos)
{
    const auto target = kn::mouse::getPos();
    direction = kn::math::normalize(target - pos);
}

void Bullet::move(const double dt)
{
    pos += direction * speed * dt;
    kn::draw::circle(pos, 2, kn::color::RED);
}

bool Bullet::outOfBounds() const
{
    const auto winSize = kn::window::getSize();
    return (pos.x < 0 || pos.x > winSize.x ||
            pos.y < 0 || pos.y > winSize.y);
}

const kn::Vec2 &Bullet::getPos() const
{
    return pos;
}