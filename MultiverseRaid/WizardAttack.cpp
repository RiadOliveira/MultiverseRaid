#include "WizardAttack.h"
#include "MultiverseRaid.h"
#include "Vector.h"

WizardAttack::WizardAttack(Point* playerPoint, float angle) {
    type = PLAYER_ATTACK;
    damageType = WIZARD;
    SetDamageTickTime(0.7f);
    SetDamagePerTick(6.0f);

    fireBall = new TileSet(
        "Resources/Wizard/FireBallAttack.png",
        16, 16, 4, 4
    );
    animation = new Animation(fireBall, 0.090f, true);
    uint sequence[4] = {0, 1, 2, 3};
    animation->Add(0, sequence, 4);
    
    speed.RotateTo(angle);
    speed.ScaleTo(540.0f);
    
    MoveTo(
        playerPoint->X() + 52 * cos(speed.Radians()),
        playerPoint->Y() - 52 * sin(speed.Radians())
    );
    RotateTo(-angle + 90.0f);
    BBox(new Circle(22.0f));
}

WizardAttack::~WizardAttack() {
    delete fireBall;
    delete animation;
}

void WizardAttack::Update() {
    Translate(speed.XComponent()* gameTime, -speed.YComponent()* gameTime);
    animation->NextFrame();

    if (x > game->Width() - 50 || x < 50 || y > game->Height() - 50 || y < 50) {
        MultiverseRaid::scene->Delete();
    }
}