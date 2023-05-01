#include "MultiverseRaid.h"
#include "WallHit.h"
#include "Random.h"

WallHit::WallHit(float pX, float pY)
{
    float base;
    if (pX < 50)
    {
        base = 0.0f;
        pX = 50;
    }
    else if (pX > game->Width() - 50)
    {
        base = 180.0f;
        pX = game->Width() - 50;
    }
    else if (pY < 50)
    {
        base = 270.0f;
        pY = 50;
    }
    else
    {
        base = 90.0f;
        pY = game->Height() - 50;
    }

    RandF color{ 0, 1 };
    
    Generator explosion;
    explosion.imgFile   = "Resources/Spark.png";
    explosion.angle     = base;
    explosion.spread    = 160.0f;
    explosion.lifetime  = 1.0f;
    explosion.frequency = 0.000f;
    explosion.percentToDim = 0.6f;
    explosion.minSpeed  = 25.0f;
    explosion.maxSpeed  = 250.0f;
    explosion.color.r   = color.Rand();
    explosion.color.g   = color.Rand();
    explosion.color.b   = color.Rand();
    explosion.color.a   = 1.0f;

    sparks = new Particles(explosion);

    sparks->Generate(pX, pY, 25);
    type = WALLHIT;
}

WallHit::~WallHit()
{
    delete sparks;
}

void WallHit::Update()
{
    sparks->Update(gameTime);

    if (sparks->Inactive())
        MultiverseRaid::scene->Delete();
}
