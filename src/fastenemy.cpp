#include "FastEnemy.hpp"
#include "Bullet.hpp"

FEnemy::FEnemy()
{
    rect.size({16, 16});

    int borderSide = rand() % 4;
    auto winSize = kn::window::getSize();
    switch (borderSide)
    {
    case 0:
        pos.x = rand() % static_cast<int>(winSize.x);
        pos.y = 0;
        break;
    case 1:
        pos.x = winSize.x;
        pos.y = rand() % static_cast<int>(winSize.y);
        break;
    case 2:
        pos.x = rand() % static_cast<int>(winSize.x);
        pos.y = winSize.y;
        break;
    case 3:
        pos.x = 0;
        pos.y = rand() % static_cast<int>(winSize.y);
        break;
    }

    anim.loadSpriteSheet("walk_up", "../assets/Shifty Jimmy North-Sheett.png", {32, 32}, 20);
    anim.loadSpriteSheet("walk_down", "../assets/Shifty Jimmy South-Sheet.png", {32, 32}, 20);
    anim.loadSpriteSheet("walk_left", "../assets/Shifty Jimmy West-Sheet.png", {32, 32}, 20);
    anim.loadSpriteSheet("walk_right", "../assets/Shifty Jimmy East-Sheet.png", {32, 32}, 20);
}

void FEnemy::update(const double dt, const kn::Vec2 &target, const kn::Frame *frame)
{

    auto dirVec = kn::math::normalize(target - pos);

    pos += dirVec * speed * dt;
    rect.center(pos);

    if (dirVec.getLength() > 0)
    {
        if (dirVec.y < 0)
        {

            anim.loadSpriteSheet("walk_up", "../assets/Shifty Jimmy North-Sheet.png", {32, 32}, 20);
        }
        else if (dirVec.y > 0)
        {

            anim.loadSpriteSheet("walk_down", "../assets/Shifty Jimmy South-Sheet.png", {32, 32}, 20);
        }
        else if (dirVec.x < 0)
        {

            anim.loadSpriteSheet("walk_left", "../assets/Shifty Jimmy West-Sheet.png", {32, 32}, 20);
        }
        else if (dirVec.x > 0)
        {
            anim.loadSpriteSheet("walk_right", "../assets/Shifty Jimmy East-Sheet.png", {32, 32}, 20);
        }
    }
    const auto *currFrame = anim.nextFrame(dt);
    kn::window::blit(*currFrame->tex, rect, currFrame->rect);
}

bool FEnemy::isDead(std::vector<Bullet> &bullets)
{
    for (size_t i = 0; i < bullets.size(); i++)
    {
        auto &bullet = bullets.at(i);
        if ((bullet.getPos() - pos).getLength() < (bullet.radius + radius))
        {
            bullets.erase(bullets.begin() + i);
            health--;
            return health == 0;
        }
    }
    return false;
}

kn::Vec2 FEnemy::getPos() const
{
    return pos;
}
