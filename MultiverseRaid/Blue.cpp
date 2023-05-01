#include "MultiverseRaid.h"
#include "Blue.h"
#include "Random.h" 

Blue::Blue(Player * p) : player(p)
{
    sprite = new Sprite("Resources/Blue.png");
    speed  = new Vector(0, 2.0f);
    BBox(new Circle(20.0f));
    
    // move para uma posição aleatória (canto superior direito)
    RandF posX { game->Width() - 400, game->Width() - 300 };
    RandF posY { 300, 400 };
    MoveTo(posX.Rand(), posY.Rand());
    
    factor = -0.25f;
    type = BLUE;
}

Blue::~Blue()
{
    delete sprite;
    delete speed;
}

void Blue::OnCollision(Object * obj)
{
      if (obj->Type() == MISSILE)
          MultiverseRaid::scene->Delete(this, MOVING);
}

void Blue::Update()
{
    float angle = Line::Angle(Point(x, y), Point(player->X(), player->Y()));
    float magnitude = 2.0f * gameTime;
    Vector target = Vector(angle, magnitude);

    speed->Add(target);
    
    if (speed->Magnitude() > 2.5f)
        speed->ScaleTo(2.5f);

    Translate(speed->XComponent() * 50.0f * gameTime, -speed->YComponent() * 50.0f * gameTime);

    Scale(1.0f + factor * gameTime);

    if (scale < 0.85f)
        factor = 0.25f;
    if (scale > 1.00f)
        factor = -0.25f;

    if (x < 50)
        MoveTo(50, y);
    if (y < 50)
        MoveTo(x, 50);
    if (x > game->Width() - 50)
        MoveTo(game->Width() - 50, y);
    if (y > game->Height() - 50)
        MoveTo(x, game->Height() - 50);
}
