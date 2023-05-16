#ifndef _ROBOT_ATTACK_H_
#define _ROBOT_ATTACK_H_

#include "Types.h"
#include "Sprite.h"
#include "Attack.h"
#include "TileSet.h"
#include "Animation.h"

class RobotAttack : public Attack {
    private:
        float angle = 0.0f;

        TileSet* laserBeam = nullptr;
        Animation* animation = nullptr;
    public:
        RobotAttack(Point* playerPoint, float laserAngle);
        ~RobotAttack();

        void Update();
        void Draw();
};

inline void RobotAttack::Draw() {
    animation->Draw(x, y, z, 1.0f, rotation);
}

#endif