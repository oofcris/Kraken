#include "TankEnemy.hpp"
#include "Bullet.hpp"

TEnemy::TEnemy()
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

    anim.loadSpriteSheet("walk_up", "../assets/Refrigerator Ralph North-Sheet.png", {48, 48}, 10);
    anim.loadSpriteSheet("walk_down", "../assets/Refrigerator Ralph South-Sheet.png", {48, 48}, 10);
    anim.loadSpriteSheet("walk_left", "../assets/Refrigerator Ralph West-Sheet.png", {48, 48}, 10);
    anim.loadSpriteSheet("walk_right", "../assets/Refrigerator Ralph East-Sheet.png", {48, 48}, 10);
}

void TEnemy::update(const double dt, const kn::Vec2 &target, const kn::Frame *frame)
{

    auto dirVec = kn::math::normalize(target - pos);

    pos += dirVec * speed * dt;
    rect.center(pos);

    if (dirVec.getLength() > 0)
    {
        if (dirVec.y < 0)
        {

            anim.loadSpriteSheet("walk_up", "../assets/Refrigerator Ralph North-Sheet.png", {48, 48}, 10);
        }
        else if (dirVec.y > 0)
        {

            anim.loadSpriteSheet("walk_down", "../assets/Refrigerator Ralph South-Sheet.png", {48, 48}, 10);
        }
        else if (dirVec.x < 0)
        {

            anim.loadSpriteSheet("walk_left", "../assets/Refrigerator Ralph West-Sheet.png", {48, 48}, 10);
        }
        else if (dirVec.x > 0)
        {
            anim.loadSpriteSheet("walk_right", "../assets/Refrigerator Ralph East-Sheet.png", {48, 48}, 10);
        }
    }
    const auto *currFrame = anim.nextFrame(dt);
    kn::window::blit(*currFrame->tex, rect, currFrame->rect);
}

bool TEnemy::isDead(std::vector<Bullet> &bullets)
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

kn::Vec2 TEnemy::getPos() const
{
    return pos;
}
