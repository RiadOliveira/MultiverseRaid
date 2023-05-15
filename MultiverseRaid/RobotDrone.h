#ifndef _ROBOT_DRONE_H_
#define _ROBOT_DRONE_H_

#include "Object.h"
#include "Types.h"
#include "Sprite.h"
#include "TileSet.h"
#include "Animation.h"
#include "Timer.h"
#include "EntityAttributes.h"

class RobotDrone : public Object {
    private:
        static EntityAttributes dronesAttributes;

        bool shouldGoUp = true;
        TileSet* drone = nullptr;
        Animation* animation = nullptr;
        Timer* attackTimer = nullptr;

        void MoveToPlayer();
    public:
        RobotDrone();
        ~RobotDrone();

        void OnCollision(Object* obj);
        void Update();
        void Draw();
};

inline void RobotDrone::Draw() {
    animation->Draw(x, y, z, 1.1f, rotation);
}

#endif