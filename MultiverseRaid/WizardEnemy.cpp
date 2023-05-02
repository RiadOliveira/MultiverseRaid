#include "WizardEnemy.h"
#include "MultiverseRaid.h"
#include "Random.h"

EntityAttributes WizardEnemy::wizardsAttributes = {
    5.0f, //hp
    180.0f, //speed
    8.0f, //damage
    3.5f, //attackSpeed
    0.25f, //defense
    300.0f //range
};

WizardEnemy::WizardEnemy(): hp(wizardsAttributes.hp) {
    sprite = new Sprite("Resources/WizardEnemy.png");
    speed  = new Vector(0, 1.0f);
    BBox(new Circle(20.0f));

    RandF posX{ game->Width() - 50, game->Width() };
    RandF posY{ game->Height() - 50, game->Height() };
    MoveTo(posX.Rand(), posY.Rand());

    type = WIZARD_ENEMY;
}

WizardEnemy::~WizardEnemy() {
    delete sprite;
    delete speed;
}

void WizardEnemy::UpdateWaveAttributes() {
    wizardsAttributes.hp += 2.0f;
    wizardsAttributes.speed += 18.0f;
    wizardsAttributes.damage += 2.5f;
    wizardsAttributes.attackSpeed -= 0.2f;

    if(wizardsAttributes.attackSpeed < 2.0f) {
        wizardsAttributes.attackSpeed = 2.0f;
    }
}

void WizardEnemy::OnCollision(Object * obj) {
    if (obj->Type() == MISSILE)
        MultiverseRaid::scene->Delete(this, MOVING);
}

void WizardEnemy::Update() {
    Player * player = MultiverseRaid::player;

    float angle = Line::Angle(Point(x, y), Point(player->X(), player->Y()));
    float magnitude = 20.0f * gameTime;
    Vector target = Vector(angle, magnitude);
    
    float distanceToPlayer = Point::Distance(Point(x, y), Point(player->X(), player->Y()));
    bool hasToEscape = distanceToPlayer < wizardsAttributes.range - 20.0f;
    bool hasToGetCloser = distanceToPlayer > wizardsAttributes.range;

    if(!hasToEscape && !hasToGetCloser) target.Rotate(90.0f);
    else if(hasToEscape) target.Rotate(180.0f);

    speed->Add(target);
    if (speed->Magnitude() > 1.0f) speed->ScaleTo(1.0f);

    float parsedSpeed = wizardsAttributes.speed * gameTime;
    Translate(speed->XComponent() * parsedSpeed, -speed->YComponent() * parsedSpeed);

    if (x < 50) MoveTo(50, y);
    else if (x > game->Width() - 50) MoveTo(game->Width() - 50, y);

    if (y < 50) MoveTo(x, 50);
    else if (y > game->Height() - 50) MoveTo(x, game->Height() - 50);
}
