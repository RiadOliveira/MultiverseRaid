#include "AlienCosmicOrb.h"
#include "MultiverseRaid.h"
#include "Vector.h"

AlienCosmicOrb::AlienCosmicOrb(
    Image* cosmicOrb, float damage,
    float playerAngle
) {
    damageType = ALIEN;
    damageTickTime = 2.0f;
    damagePerTick = damage;
    sprite = new Sprite(cosmicOrb);

    Player* player = MultiverseRaid::player;
    float posX, posY;

    if(player == nullptr) {
        posX = game->CenterX();
        posY = game->CenterY();
    } else {
        posX = player->X();
        posY = player->Y();
    }
    
    speed.RotateTo(playerAngle + 90.0f);
    speed.ScaleTo(200.0f);
    
    MoveTo(posX, posY);
    BBox(new Circle(21.0f));
}

AlienCosmicOrb::~AlienCosmicOrb() {
    delete sprite;
}

void AlienCosmicOrb::Update() {
    Rotate(300 * gameTime);
    speed.Add(Vector(speed.Angle() + 90.0f, 200.0f));
    Translate(speed.XComponent() * gameTime, -speed.YComponent() * gameTime);

    Player* player = MultiverseRaid::player;
    Point playerPoint = Point(player->X(), player->Y());
    Point orbPoint = Point(x, y);

    float distance = Point::Distance(playerPoint, orbPoint);
    float distanceFromMaxPoint = distance - 120.0f;
    
    float angle = Line::Angle(orbPoint, playerPoint);
    Vector vector = Vector(angle, distanceFromMaxPoint);
    Translate(vector.XComponent(), -vector.YComponent());
}