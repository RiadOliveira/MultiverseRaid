#ifndef _ROBOT_DRONE_ATTACK_H_
#define _ROBOT_DRONE_ATTACK_H_

#include "Types.h"
#include "Sprite.h"
#include "PlayerAttack.h"
#include "TileSet.h"
#include "Animation.h"
#include "RobotDrone.h"
#include "Vector.h"

class RobotDroneAttack : public PlayerAttack {
    private:
        TileSet* energyBall = nullptr;
        Animation* animation = nullptr;
        Vector* speed = nullptr;
    public:
        RobotDroneAttack(float damage, RobotDrone* drone, Object* target);
        ~RobotDroneAttack();

        void Update();
        void Draw();
};

inline void RobotDroneAttack::Draw() {
    animation->Draw(x, y, z, 1.0f, rotation);
}

#endif