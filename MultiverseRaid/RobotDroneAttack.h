#ifndef _ROBOT_DRONE_ATTACK_H_
#define _ROBOT_DRONE_ATTACK_H_

#include "Types.h"
#include "Sprite.h"
#include "Attack.h"
#include "RobotDrone.h"
#include "Vector.h"

class RobotDroneAttack : public Attack {
    private:
        Sprite* sprite = nullptr;
        Point startPoint;
        Vector speed;
    public:
        RobotDroneAttack(
            float damage, float angle,
            RobotDrone* drone
        );
        ~RobotDroneAttack();

        void Update();
        void Draw();
};

inline void RobotDroneAttack::Draw() {
    sprite->Draw(x, y, z, 0.03f, rotation);
}

#endif