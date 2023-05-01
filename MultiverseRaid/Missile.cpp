#include "Missile.h"
#include "WallHit.h"
#include "MultiverseRaid.h"

Player* & Missile::player = MultiverseRaid::player;

Missile::Missile() {
    sprite = new Sprite("Resources/Missile.png");

    BBox(new Circle(8));
    
    //speed.RotateTo(player->speed->Angle());
    speed.ScaleTo(15.0f);
    
    MoveTo(player->X() + 22 * cos(speed.Radians()), player->Y() - 22 * sin(speed.Radians()));
    //RotateTo(-player->speed->Angle() + 90.0f);

    type = MISSILE;
}

Missile::~Missile()
{
    delete sprite;
}

void Missile::Update()
{
    Translate(speed.XComponent() * 90.0f * gameTime, -speed.YComponent() * 90.0f * gameTime);

    if (x > game->Width() - 50 || x < 50 || y > game->Height() - 50 || y < 50)
    {
        float distance = Point::Distance(Point(x, y), Point(player->X(), player->Y()));
        float level = (MaxDistance - distance) / MaxDistance * BaseVolume;
        MultiverseRaid::audio->Volume(HITWALL, level);
        MultiverseRaid::audio->Play(HITWALL);

        MultiverseRaid::scene->Add(new WallHit(x,y), STATIC);

        MultiverseRaid::scene->Delete();
    }
}
