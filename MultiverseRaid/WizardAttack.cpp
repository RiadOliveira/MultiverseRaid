#include "WizardAttack.h"
#include "MultiverseRaid.h"
#include "Vector.h"

WizardAttack::WizardAttack(float damage, Object* target) {
    damageType = WIZARD;
    damageTickTime = 1.0f;
    damagePerTick = damage;

    Player* player = MultiverseRaid::player;
    float posX = player->X();
    float posY = player->Y();

    float tileWidth = 16.0f, halfTileWidth = tileWidth/2;
    float tileHeight = 16.0f, halfTileHeight = tileHeight/2;
    float distanceFromPlayer = 18.0f + halfTileWidth;

    fireBall = new TileSet(
        "Resources/Wizard/WizardAttack.png",
        (uint) tileWidth, (uint) tileHeight, 4, 4
    );
    animation = new Animation(fireBall, 0.090f, true);
    uint sequence[4] = {0, 1, 2, 3};
    animation->Add(0, sequence, 4);

    float angle = Line::Angle(
        Point(posX, posY),
        Point(target->X(), target->Y())
    );
    
    speed.RotateTo(angle);
    speed.ScaleTo(6.0f);
    
    MoveTo(posX + 22 * cos(speed.Radians()), posY - 22 * sin(speed.Radians()));
    RotateTo(-angle + 90.0f);

    BBox(new Circle(23.0f));
}

WizardAttack::~WizardAttack() {
    delete fireBall;
    delete animation;
}

void WizardAttack::Update() {
    Translate(
        speed.XComponent() * 90.0f * gameTime,
        -speed.YComponent() * 90.0f * gameTime
    );
    animation->NextFrame();

    if (x > game->Width() - 50 || x < 50 || y > game->Height() - 50 || y < 50) {
        MultiverseRaid::scene->Delete();
    }
}