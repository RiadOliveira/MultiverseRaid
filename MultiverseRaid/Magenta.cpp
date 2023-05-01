#include "MultiverseRaid.h"
#include "Magenta.h"
#include "Random.h" 

Magenta::Magenta(Player * p) : player (p)
{
    sprite = new Sprite("Resources/Magenta.png");
    speed  = new Vector(0, 2.0f);
    BBox(new Circle(18.0f));
    
    RandF posX{ 300, 400 };
    RandF posY{ game->Height() - 400, game->Height() - 300 };
    MoveTo(posX.Rand(), posY.Rand());

    type = MAGENTA;
}

Magenta::~Magenta()
{
    delete sprite;
    delete speed;
}

void Magenta::OnCollision(Object * obj)
{
    if (obj->Type() == MISSILE)
        MultiverseRaid::scene->Delete(this, MOVING);
}

void Magenta::Update()
{
    speed->RotateTo(Line::Angle(Point(x, y), Point(player->X(), player->Y())));
    Rotate(200 * gameTime);

    Translate(speed->XComponent() * 50.0f * gameTime, -speed->YComponent() * 50.0f * gameTime);
}
