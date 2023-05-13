#include "RobotDrone.h"
#include "RobotDroneAttack.h"
#include "MultiverseRaid.h"

EntityAttributes RobotDrone::dronesAttributes = {
    0.0f, //hp
    4.0f, //damage
    190.0f, //speed
    2.0f, //attackSpeed
    0.0f, //defense
    145.0f //range
};

RobotDrone::RobotDrone() {
    Player* player = MultiverseRaid::player;
    attackTimer = new Timer();

    if(player == nullptr) {
        MoveTo(game->CenterX() - 48.0f, game->CenterY() - 24.0f);
    } else MoveTo(player->X(), player->Y());
    BBox(new Circle(dronesAttributes.range));

    drone = new TileSet(
        "Resources/Robot/RobotDrone.png",
        24, 28, 4, 4
    );
    animation = new Animation(drone, 0.2f, true);
    uint sequence[4] = {0, 1, 2, 3};
    animation->Add(0, sequence, 4);

    energyBall = new Image("Resources/Robot/RobotDroneAttack.png");
    type = PLAYER_COMPANION;
}

RobotDrone::~RobotDrone() {
    delete drone;
    delete animation;
    delete attackTimer;
    delete energyBall;
}

void RobotDrone::MoveToPlayer() {
    Player* player = MultiverseRaid::player;

    float playerX = player->X(), playerY = player->Y();
    MoveTo(x, playerY - 24.0f);

    SpriteState state = player->SpriteState();
    float expectedDistance = playerX + (state == LEFT ? -48.0f : 48.0f);
    float xDifference = abs(x - expectedDistance);

    float xTranslation =
        (xDifference > 10.0f ? 360.0f : dronesAttributes.speed) * gameTime;

    if(state == LEFT && x > playerX - 48.0f) {
        Translate(-xTranslation, 0);
    } else if(state == RIGHT && x < playerX + 48.0f) {
        Translate(xTranslation, 0);
    }
}

void RobotDrone::OnCollision(Object* obj) {
    uint type = obj->Type();
    if(type != ENEMY) return;

    if(attackTimer->Elapsed() >= dronesAttributes.attackSpeed) {
        RobotDroneAttack* attack = new RobotDroneAttack(
            energyBall, dronesAttributes.damage, this, obj
        );
        MultiverseRaid::scene->Add(attack, MOVING);
        attackTimer->Reset();

        BBox()->ScaleTo(0.0f);
    }
}

void RobotDrone::Update() {
    MoveToPlayer();
    animation->NextFrame();

    if(attackTimer->Elapsed() >= dronesAttributes.attackSpeed) {
        BBox()->ScaleTo(min(BBox()->Scale() + 0.1f, 1.0f));
    }
}
