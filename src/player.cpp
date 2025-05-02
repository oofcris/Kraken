#include "Player.hpp"

Player::Player() : pos(kn::window::getSize() / 2)
{
    rect.size({16, 16});
    
    anim.loadSpriteSheet("walk_down", "../assets/Thomas Walking South-Sheet.png", {32, 32}, 10);
    anim.loadSpriteSheet("walk_up", "../assets/Thomas Walking North-Sheet.png", {32, 32}, 10);
    anim.loadSpriteSheet("walk_left", "../assets/Thomas Walking West-Sheet.png", {32, 32}, 10);
    anim.loadSpriteSheet("walk_right", "../assets/Thomas Walking East-Sheet.png", {32, 32}, 10);
}

void Player::update(const double dt)
{
    const auto *keys = kn::key::getPressed();
    kn::Vec2 dirVec = {
        keys[kn::S_d] - keys[kn::S_a],
        keys[kn::S_s] - keys[kn::S_w]};

    if (dirVec.getLength() > 1)
        dirVec.normalize();

    pos += dirVec * speed * dt;
    rect.center(pos);

    if (dirVec.getLength() > 0)
    {
        if (dirVec.y < 0)
        {

            anim.loadSpriteSheet("walk_up", "../assets/Thomas Walking North-Sheet.png", {32, 32}, 10);
        }
        else if (dirVec.y > 0)
        {

            anim.loadSpriteSheet("walk_down", "../assets/Thomas Walking South-Sheet.png", {32, 32}, 10);
        }
        else if (dirVec.x < 0)
        {
            anim.loadSpriteSheet("walk_left", "../assets/Thomas Walking West-Sheet.png", {32, 32}, 10);
        }
        else if (dirVec.x > 0)
        {

            anim.loadSpriteSheet("walk_right", "../assets/Thomas Walking East-Sheet.png", {32, 32}, 10);
        }
    }
    else
    {

        anim.loadSpriteSheet("idle", "../assets/Thomas Idle-Sheet.png", {32, 32}, 1);
    }

    const auto *currFrame = anim.nextFrame(dt);
    kn::window::blit(*currFrame->tex, rect, currFrame->rect);
}

kn::Vec2 Player::getPos() const
{
    return pos;
}

kn::Rect Player::getRect() const
{
    return rect;
}
