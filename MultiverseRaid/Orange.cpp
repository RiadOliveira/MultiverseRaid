#include "MultiverseRaid.h"
#include "Orange.h"
#include "Random.h" 

Orange::Orange(Player * p) : player (p)
{
    sprite = new Sprite("Resources/Orange.png");
    speed  = new Vector(0, 2.0f);
    BBox(new Circle(20.0f));

    speed->RotateTo(Line::Angle(Point(x, y), Point(player->X(), player->Y())));
    RotateTo(-speed->Angle());
    
    RandF pos{ 100, 150 };
    MoveTo(pos.Rand(), pos.Rand());

    multiplier = 70.0f;
    type = ORANGE;

    Generator emitter;
    emitter.imgFile = "Resources/Spark.png";
    emitter.angle = speed->Angle() + 180;
    emitter.spread = 10;
    emitter.lifetime = 0.2f;
    emitter.frequency = 0.010f;
    emitter.percentToDim = 0.7f;
    emitter.minSpeed = 50.0f;
    emitter.maxSpeed = 100.0f;
    emitter.color.r = 1.0f;
    emitter.color.g = 0.5;
    emitter.color.b = 0.0f;
    emitter.color.a = 1.0f;

    tail = new Particles(emitter);
}

Orange::~Orange()
{
    delete sprite;
    delete speed;
    delete tail;
}

void Orange::OnCollision(Object * obj)
{
    if (obj->Type() == MISSILE)
        MultiverseRaid::scene->Delete(this, MOVING);
}

void Orange::Update()
{
    Translate(speed->XComponent() * multiplier * gameTime, -speed->YComponent() * multiplier * gameTime);

    if (x < 100 || y < 100 || x > game->Width() - 100 || y > game->Height() - 100)
    {
        multiplier = 200;
        speed->RotateTo(Line::Angle(Point(x, y), Point(player->X(), player->Y())));
        RotateTo(-speed->Angle());
    }

    tail->Config().angle = speed->Angle();
    tail->Generate(x - 10 * cos(speed->Radians()), y + 10 * sin(speed->Radians()));
    tail->Update(gameTime);
}

void Orange::Draw()
{
    sprite->Draw(x, y, Layer::LOWER, scale, rotation);
    tail->Draw(Layer::LOWER, 1.0f);
}
