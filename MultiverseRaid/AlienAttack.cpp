#include "AlienAttack.h"
#include "MultiverseRaid.h"
#include "Vector.h"

AlienAttack::AlienAttack(Object* target) {
    type = PLAYER_ATTACK;
    damageType = ALIEN;
    SetDamageTickTime(0.7f);
    SetDamagePerTick(4.0f);

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
    speed.ScaleTo(270.0f);
    
    int waveDivision = (MultiverseRaid::gameWave - 1) / 3;
    float scaleIncrease = (float) waveDivision * 0.15f;
    ScaleTo(1.0f + min(scaleIncrease, 0.3f));

    float factor = 86.0f * scale;
    MoveTo(
        posX + factor * cos(speed.Radians()),
        posY - factor * sin(speed.Radians())
    );
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
    Vector gravitationalField = Vector(angle, 350.0f);

    float xTranslation = gravitationalField.XComponent() * gameTime;
    float yTranslation = gravitationalField.YComponent() * gameTime;
    obj->Translate(xTranslation, -yTranslation);
}

void AlienAttack::Update() {
    Translate(speed.XComponent() * gameTime, -speed.YComponent() * gameTime);
    animation->NextFrame();

    if (x > game->Width() - 50 || x < 50 || y > game->Height() - 50 || y < 50) {
        MultiverseRaid::scene->Delete();
    }
}