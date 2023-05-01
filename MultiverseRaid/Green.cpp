#include "Green.h"
#include "MultiverseRaid.h"
#include "Random.h" 

Green::Green(Player * p): player(p)
{
    sprite = new Sprite("Resources/Green.png");
    speed  = new Vector(0, 2.0f);
    BBox(new Circle(20.0f));

    RandI dist{ 300, 400 };
    distance = dist.Rand();

    RandF posX{ game->Width() - 50, game->Width() };
    RandF posY{ game->Height() - 50, game->Height() };
    MoveTo(posX.Rand(), posY.Rand());

    type = GREEN;
}

Green::~Green()
{
    delete sprite;
    delete speed;
}

void Green::OnCollision(Object * obj)
{
    if (obj->Type() == MISSILE)
        MultiverseRaid::scene->Delete(this, MOVING);
}

void Green::Update()
{
    float angle = Line::Angle(Point(x, y), Point(player->X(), player->Y()));
    float magnitude = 10.0f * gameTime;
    Vector target = Vector(angle, magnitude);
    
    if (Point::Distance(Point(x, y), Point(player->X(), player->Y())) < distance)
    {
        target.Rotate(180.0f);
        target.ScaleTo(20.0f * gameTime);
    }

    speed->Add(target);
    
    if (speed->Magnitude() > 3)
        speed->ScaleTo(3.0f);

    Translate(speed->XComponent() * 50.0f * gameTime, -speed->YComponent() * 50.0f * gameTime);
    Rotate(50 * gameTime);

    if (x < 50)
        MoveTo(50, y);
    if (y < 50)
        MoveTo(x, 50);
    if (x > game->Width() - 50)
        MoveTo(game->Width() - 50, y);
    if (y > game->Height() - 50)
        MoveTo(x, game->Height() - 50);
}
