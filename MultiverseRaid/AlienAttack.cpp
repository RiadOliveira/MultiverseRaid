#include "AlienAttack.h"
#include "MultiverseRaid.h"
#include "Vector.h"

AlienAttack::AlienAttack(float damage, Object* target) {
    damageType = ALIEN;
    damageTickTime = 1.0f;
    damagePerTick = damage;

    Player* player = MultiverseRaid::player;
    float posX = player->X();
    float posY = player->Y();

    float tileWidth = 144.0f, halfTileWidth = tileWidth/2;
    float tileHeight = 144.0f, halfTileHeight = tileHeight/2;
    float distanceFromPlayer = 18.0f + halfTileWidth;

    blackHole = new TileSet(
        "Resources/Alien/AlienAttack.png",
        (uint) tileWidth, (uint) tileHeight, 4, 4
    );
    animation = new Animation(blackHole, 0.090f, true);
    uint sequence[4] = {0, 1, 2, 3};
    animation->Add(0, sequence, 4);

    float angle = Line::Angle(
        Point(posX, posY),
        Point(target->X(), target->Y())
    );
    
    speed.RotateTo(angle);
    speed.ScaleTo(3.0f);
    
    MoveTo(posX + 22 * cos(speed.Radians()), posY - 22 * sin(speed.Radians()));
    RotateTo(-angle + 90.0f);

    BBox(new Circle(58.0f));
}

AlienAttack::~AlienAttack() {
    delete blackHole;
    delete animation;
}

void AlienAttack::OnCollision(Object* obj) {
    if(obj->Type() != ENEMY) return;

    float angle = Line::Angle(Point(obj->X(), obj->Y()), Point(x, y));
    Vector gravitationalField = Vector(angle, 400.0f);

    float xTranslation = gravitationalField.XComponent() * gameTime;
    float yTranslation = gravitationalField.YComponent() * gameTime;

    obj->Translate(xTranslation, -yTranslation);
}

void AlienAttack::Update() {
    Translate(
        speed.XComponent() * 90.0f * gameTime,
        -speed.YComponent() * 90.0f * gameTime
    );
    animation->NextFrame();

    if (x > game->Width() - 50 || x < 50 || y > game->Height() - 50 || y < 50) {
        MultiverseRaid::scene->Delete();
    }
}