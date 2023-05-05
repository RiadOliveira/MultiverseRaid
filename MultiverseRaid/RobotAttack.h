#ifndef _ROBOT_ATTACK_H_
#define _ROBOT_ATTACK_H_

#include "Types.h"
#include "Sprite.h"
#include "PlayerAttack.h"
#include "TileSet.h"
#include "Animation.h"

class RobotAttack : public PlayerAttack {
    private:
        TileSet* laserBeam = nullptr;
        Animation* animation = nullptr;
    public:
        RobotAttack(float damage, Object* target);
        ~RobotAttack();

        void Update();
        void Draw();
};

inline void RobotAttack::Draw() {
    animation->Draw(x, y, z, 1.0f, rotation);
}

#endif