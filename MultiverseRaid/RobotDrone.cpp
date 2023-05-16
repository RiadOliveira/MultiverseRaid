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
        MoveTo(game->CenterX() - 52.0f, game->CenterY());
    } else MoveTo(player->X(), player->Y());
    BBox(new Circle(dronesAttributes.range));

    drone = new TileSet(
        "Resources/Robot/RobotDrone.png",
        24, 28, 4, 4
    );
    animation = new Animation(drone, 0.2f, true);
    uint sequence[4] = {0, 1, 2, 3};
    animation->Add(0, sequence, 4);

    attackTimer->Start();
    type = PLAYER_PASSIVE;
}

RobotDrone::~RobotDrone() {
    delete drone;
    delete animation;
    delete attackTimer;

    MultiverseRaid::audio->Stop(DRONE_ATTACK);
}

void RobotDrone::MoveToPlayer() {
    Player* player = MultiverseRaid::player;
    float playerX = player->X(), playerY = player->Y();

    float multiplier = shouldGoUp ? -1.0f : 1.0f;
    float yDifference = playerY - y + multiplier * 24.0f;

    if(shouldGoUp && yDifference >= 0.0f) shouldGoUp = false;
    else if(!shouldGoUp && yDifference <= 0.0f) shouldGoUp = true;

    float droneSpeed = abs(yDifference) > 50.0f ? dronesAttributes.speed : 60.0f;
    Translate(0, multiplier * gameTime * droneSpeed);

    uint state = player->TileSetState();
    float expectedDistance = playerX + (state == LEFT ? -52.0f : 52.0f);
    float xDifference = abs(x - expectedDistance);

    float xTranslation =
        (xDifference > 10.0f ? 360.0f : dronesAttributes.speed) * gameTime;

    if(state == LEFT && x > playerX - 52.0f) {
        Translate(-xTranslation, 0);
    } else if(state == RIGHT && x < playerX + 52.0f) {
        Translate(xTranslation, 0);
    }
}

void RobotDrone::OnCollision(Object* obj) {
    uint type = obj->Type();
    if(type != ENEMY) return;

    float playerAttackSpeed = MultiverseRaid::player->Attributes().attackSpeed;
    float cooldown = dronesAttributes.attackSpeed - (1.0f - playerAttackSpeed);
    if(attackTimer->Elapsed() < cooldown) return;

    float angle = Line::Angle(Point(x, y), Point(obj->X(), obj->Y()));
    for(int ind=-10 ; ind<=10 ; ind += 10) {
        RobotDroneAttack* attack = new RobotDroneAttack(
            dronesAttributes.damage, angle + (float) ind, this
        );
        
        MultiverseRaid::scene->Add(attack, STATIC);
        MultiverseRaid::audio->Play(DRONE_ATTACK);
    }

    attackTimer->Reset();
    BBox()->ScaleTo(0.0f);
}

void RobotDrone::Update() {
    MoveToPlayer();
    animation->NextFrame();

    if(attackTimer->Elapsed() >= dronesAttributes.attackSpeed) {
        BBox()->ScaleTo(min(BBox()->Scale() + 0.1f, 1.0f));
    }
}
