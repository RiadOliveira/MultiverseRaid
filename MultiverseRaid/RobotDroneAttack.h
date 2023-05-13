#ifndef _ROBOT_DRONE_ATTACK_H_
#define _ROBOT_DRONE_ATTACK_H_

#include "Types.h"
#include "Sprite.h"
#include "PlayerAttack.h"
#include "RobotDrone.h"
#include "Vector.h"

class RobotDroneAttack : public PlayerAttack {
    private:
        Sprite* sprite = nullptr;
        Vector speed;
    public:
        RobotDroneAttack(
            Image* energyBall, float damage,
            RobotDrone* drone, Object* target
        );
        ~RobotDroneAttack();

        void Update();
        void Draw();
};

inline void RobotDroneAttack::Draw() {
    sprite->Draw(x, y, z, 2.5f, rotation);
}

#endif