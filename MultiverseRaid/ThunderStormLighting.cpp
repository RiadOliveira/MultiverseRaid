#include "ThunderStormLighting.h"
#include "MultiverseRaid.h"
#include "Vector.h"

ThunderStormLighting::ThunderStormLighting(Point* target) {
    damageType = WIZARD;
    damageTickTime = 1.0f;
    damagePerTick = 8.0f;

    lighting = new TileSet(
        "Resources/Wizard/LightingAttack.png",
        (uint) 137, (uint) 363, 4, 4
    );
    animation = new Animation(lighting, 0.10f, false);
    uint sequence[5] = {0, 1, 2, 3, 4};
    animation->Add(0, sequence, 5);

    MoveTo(target->X(), target->Y());
    BBox(new Circle(40.0f));
}

ThunderStormLighting::~ThunderStormLighting() {
    delete lighting;
    delete animation;
}

void ThunderStormLighting::Update() {
    if(animation->Inactive()) MultiverseRaid::scene->Delete();
    else animation->NextFrame();
}