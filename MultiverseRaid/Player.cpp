#include "Player.h" 
#include "MultiverseRaid.h"
#include "WizardAvatar.h"
#include "RobotAvatar.h"
#include "AlienAvatar.h"
#include "RobotEnemy.h"
#include "WizardEnemy.h"
#include "AlienEnemy.h"

void Player::SetAttributes() {
    attributes.hp = 10.0f;
    attributes.damage = 0.0f;
    attributes.speed = 180.0f;
    attributes.attackSpeed = 0.0f;
    attributes.defense = 0.3f;
    attributes.range = 290.0f;
}

Player::Player(): tileSetState(LEFT), level(0), selectedAvatar(WIZARD) {
    avatars = new Avatar*[3];
    avatars[WIZARD] = new WizardAvatar();
    avatars[ROBOT] = new RobotAvatar();
    avatars[ALIEN] = new AlienAvatar();

    Point vertex[16] =
    {
        Point(11, -35), Point(12, -28), Point(20, -26), Point(20, -8),
        Point(24, 12), Point(20, 12), Point(20, 18), Point(20, 35),
        Point(-20, 35), Point(-20, 18), Point(-20, 12), Point(-24, 12),
        Point(-20, -8), Point(-20, -26), Point(-12, -28), Point(-11, -35)

    };
    BBox(new Poly(vertex, 16));

    MoveTo(game->CenterX(), game->CenterY());
    SetAttributes();
    type = PLAYER;

    Scene * scene = MultiverseRaid::scene;
    avatars[selectedAvatar]->HandleSelectAvatar();
    scene->Add(avatars[selectedAvatar], STATIC);
}

Player::~Player() {
    for(int ind=0 ; ind<3 ; ind++) {
        if(ind != selectedAvatar) delete avatars[ind];
    }
    delete[] avatars;
}

void Player::LevelUp() {
    level++;

    attributes.hp = 10.0f + level * 5.0f;
    attributes.damage += 2.0f;
    attributes.speed += 20.0f;
    attributes.attackSpeed -= 0.2f;

    if(attributes.attackSpeed < 1.0f) {
        attributes.attackSpeed = 1.0f;
    }
}

float Player::GetSelectedAvatarDefenseValue() {
    switch(selectedAvatar) {
        case WIZARD: return WizardEnemy::defaultAttributes.defense;
        case ROBOT: return RobotEnemy::defaultAttributes.defense;
        case ALIEN: return AlienEnemy::defaultAttributes.defense;
        default: return WizardEnemy::defaultAttributes.defense;
    }
}

bool Player::HasDisadvantageOnEnemyType(uint enemyType) {
    switch(enemyType) {
        case WIZARD: return selectedAvatar == ROBOT;
        case ROBOT: return selectedAvatar == ALIEN;
        case ALIEN: return selectedAvatar == WIZARD;
        default: return false;
    }
}

float Player::GetDamageReduction(uint damageReceivedType) {
    if(HasDisadvantageOnEnemyType(damageReceivedType)) return 0.0f;
    return GetSelectedAvatarDefenseValue();
}

void Player::ApplyDamage(float damage, uint damageType) {
    float damageReduction = GetDamageReduction(damageType);
    float damageToApply = damage * (1.0f - damageReduction);

    attributes.hp -= damageToApply;
    if(attributes.hp < 0.0f) attributes.hp = 0.0f;
}

void Player::HandleMovement() {
    float parsedSpeed = attributes.speed * gameTime;

    bool upCommandPressed = window->KeyDown(VK_UP) || window->KeyDown('W');
    bool downCommandPressed = window->KeyDown(VK_DOWN) || window->KeyDown('S');
    bool rightCommandPressed = window->KeyDown(VK_RIGHT) || window->KeyDown('D');
    bool leftCommandPressed = window->KeyDown(VK_LEFT) || window->KeyDown('A');

    if(upCommandPressed) Translate(0, -parsedSpeed);
    if(downCommandPressed) Translate(0, parsedSpeed);

    if(rightCommandPressed) {
        Translate(parsedSpeed, 0);
        tileSetState = RIGHT;
    }
    if(leftCommandPressed) {
        Translate(-parsedSpeed, 0);
        tileSetState = LEFT;
    }

    if (x < 50) MoveTo(50, y);
    else if (x > game->Width() - 50) MoveTo(game->Width() - 50, y);

    if (y < 50) MoveTo(x, 50);
    else if (y > game->Height() - 50) MoveTo(x, game->Height() - 50);

    Animation* avatarAnimation = avatars[selectedAvatar]->animation;
    avatarAnimation->Select(tileSetState);

    bool playerMoved = upCommandPressed || downCommandPressed ||
        rightCommandPressed || leftCommandPressed;
    if(playerMoved) avatarAnimation->NextFrame();
    else avatarAnimation->Frame(0);
}

void Player::Update() {
    bool hasToSwitchAvatar = Avatar::ReachedActiveTimeLimit();
    bool chooseAndCanSwitchAvatar = window->KeyDown('Q') && Avatar::CanSwitchAvatar();
    if(hasToSwitchAvatar || chooseAndCanSwitchAvatar) {
        Scene * scene = MultiverseRaid::scene;
        
        Avatar* previousAvatar = avatars[selectedAvatar];
        previousAvatar->HandleUnselectAvatar();
        scene->Remove(previousAvatar, STATIC);

        selectedAvatar = (selectedAvatar + 1) % 3;
        Avatar* currentAvatar = avatars[selectedAvatar];

        currentAvatar->HandleSelectAvatar();
        scene->Add(currentAvatar, STATIC);
        Avatar::ResetTimersData();
    }

    HandleMovement();
}

void Player::Draw() {
    avatars[selectedAvatar]->animation->Draw(x, y, Layer::MIDDLE, 0.25f);
}
