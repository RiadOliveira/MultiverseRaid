#include "MultiverseRaid.h"
#include "AlienEnemy.h"
#include "Random.h"

EntityAttributes AlienEnemy::aliensAttributes = {
    6.0f, //hp
    220.0f, //speed
    7.0f, //damage
    3.5f, //attackSpeed
    0.30f //defense
};

AlienEnemy::AlienEnemy(Player * p) : player (p), hp(aliensAttributes.hp) {
    sprite = new Sprite("Resources/AlienEnemy.png");
    speed  = new Vector(0, 2.0f);
    BBox(new Circle(20.0f));

    speed->RotateTo(Line::Angle(Point(x, y), Point(player->X(), player->Y())));
    RotateTo(-speed->Angle());
    
    RandF pos{ 100, 150 };
    MoveTo(pos.Rand(), pos.Rand());

    type = ALIEN_ENEMY;
}

AlienEnemy::~AlienEnemy() {
    delete sprite;
    delete speed;
}

void AlienEnemy::UpdateWaveAttributes() {
    aliensAttributes.hp += 3.0f;
    aliensAttributes.speed += 20.0f;
    aliensAttributes.damage += 2.0f;
    aliensAttributes.attackSpeed -= 0.2f;

    if(aliensAttributes.attackSpeed < 1.5f) {
        aliensAttributes.attackSpeed = 1.5f;
    }
}

void AlienEnemy::OnCollision(Object * obj)
{
    if (obj->Type() == MISSILE)
        MultiverseRaid::scene->Delete(this, MOVING);
}

void AlienEnemy::Update() {
    float parsedSpeed = aliensAttributes.speed * gameTime;
    Translate(speed->XComponent() * parsedSpeed, -speed->YComponent() * parsedSpeed);

    if (x < 100 || y < 100 || x > game->Width() - 100 || y > game->Height() - 100) {
        speed->RotateTo(Line::Angle(Point(x, y), Point(player->X(), player->Y())));
        RotateTo(-speed->Angle());
    }
}

void AlienEnemy::Draw() {
    sprite->Draw(x, y, Layer::LOWER, scale, rotation);
}
