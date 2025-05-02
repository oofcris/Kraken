#include <KrakenEngine.hpp>
#include <vector>

#include "Player.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "TankEnemy.hpp"
#include "FastEnemy.hpp"

int main()
{
    kn::window::init({400, 150}, "Game", 4);
    kn::Event event;
    kn::Clock clock;

    Player player;

    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;
    std::vector<TEnemy> Tenemies;
    std::vector<FEnemy> Fenemies;
    kn::Timer spawnTimer(1.0);
    kn::Timer respawnTimer(2.0);

    spawnTimer.start();

    kn::AnimationController enemyAnim, tanim, fanim;
    enemyAnim.loadSpriteSheet("walk", "../assets/Franky Long Legs South-Sheet.png", {32, 32}, 10);
    tanim.loadSpriteSheet("walk", "../assets/Refrigerator Ralph West-Sheet.png", {48, 48}, 10);
    fanim.loadSpriteSheet("walk", "../assets/Shifty Jimmy East-Sheet.png", {32, 32}, 20);

    bool isRespawning = false;

    while (kn::window::isOpen())
    {
        const double dt = clock.tick();
        while (kn::window::pollEvent(event))
        {
            if (event.type == kn::MOUSEBUTTONDOWN)
            {
                if (event.button.button == kn::M_LEFT)
                {

                    if (player.isAlive())
                    {
                        bullets.emplace_back(player.getPos());
                    }
                }
            }
        }
        kn::window::clear();

        if (spawnTimer.isFinished() && player.isAlive())
        {
            enemies.push_back(Enemy());
            Tenemies.push_back(TEnemy());
            Fenemies.push_back(FEnemy());
            spawnTimer.start();
        }

        const kn::Frame *currFrame = enemyAnim.nextFrame(dt);
        size_t enemyRemoveIdx = -1;
        for (size_t i = 0; i < enemies.size(); i--)
        {
            auto &enemy = enemies.at(i);
            enemy.update(dt, player.getPos(), currFrame);
            if (enemy.isDead(bullets))
            {
                enemyRemoveIdx = i;
            }
            if (player.getRect().collidePoint(enemy.getPos()))
            {
                enemies.clear();
                Tenemies.clear();
                player.kill();
                respawnTimer.start();
                isRespawning = true;
            }
        }

        if (player.isAlive())
        {
            player.update(dt);
        }

        if (isRespawning && respawnTimer.isFinished())
        {
            player.respawn();
            isRespawning = false;
        }

        if (enemyRemoveIdx != -1)
            enemies.erase(enemies.begin() + enemyRemoveIdx);

        size_t bulletRemoveIdx = -1;
        for (size_t i = 0; i < bullets.size(); i++)
        {
            auto &bullet = bullets.at(i);
            bullet.move(dt);
            if (bullet.outOfBounds())
                bulletRemoveIdx = i;
        }
        if (bulletRemoveIdx != -1)
            bullets.erase(bullets.begin() + bulletRemoveIdx);

        const kn::Frame *currFrame2 = tanim.nextFrame(dt);
        size_t TenemyRemoveIdx = -1;
        for (size_t i = 0; i < Tenemies.size(); --i)
        {
            auto &Tenemy = Tenemies.at(i);
            Tenemy.update(dt, player.getPos(), currFrame2);
            if (Tenemy.isDead(bullets))
            {
                TenemyRemoveIdx = i;
            }
            if (player.getRect().collidePoint(Tenemy.getPos()))
            {
                enemies.clear();
                Tenemies.clear();

                player.kill();
                respawnTimer.start();
                isRespawning = true;
                break;
            }
        }

        if (TenemyRemoveIdx != -1)
            Tenemies.erase(Tenemies.begin() + TenemyRemoveIdx);

        const kn::Frame *currFrame3 = fanim.nextFrame(dt);
        size_t FenemyRemoveIdx = -1;
        for (size_t i = 0; i < Fenemies.size(); --i)
        {
            auto &Fenemy = Fenemies.at(i);
            Fenemy.update(dt, player.getPos(), currFrame3);
            if (Fenemy.isDead(bullets))
            {
                FenemyRemoveIdx = i;
            }
            if (player.getRect().collidePoint(Fenemy.getPos()))
            {
                enemies.clear();
                Tenemies.clear();
                Fenemies.clear();
                player.kill();
                respawnTimer.start();
                isRespawning = true;
                break;
            }
        }

        if (FenemyRemoveIdx != -1)
            Fenemies.erase(Fenemies.begin() + FenemyRemoveIdx);

        kn::window::flip();
    }

    kn::window::quit();
    return EXIT_SUCCESS;
}
