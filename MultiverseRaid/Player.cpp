#include "Player.h" 
#include "Missile.h"
#include "MultiverseRaid.h"
#include "WizardAvatar.h"
#include "RobotAvatar.h"
#include "AlienAvatar.h"

void Player::ResetAttributes() {
    attributes.hp = 10.0f;
    attributes.damage = 0.0f;
    attributes.speed = 180.0f;
    attributes.attackSpeed = 0.0f;
    attributes.defense = 0.3f;
    attributes.range = 290.0f;
}

Player::Player(): spriteState(LEFT), level(0), selectedAvatar(WIZARD) {
    sprite = new Sprite("Resources/Player.png");

    avatars = new Avatar*[3];
    avatars[WIZARD] = new WizardAvatar();
    avatars[ROBOT] = new RobotAvatar();
    avatars[ALIEN] = new AlienAvatar();

    BBox(new Circle(18.0f));
    MoveTo(game->CenterX(), game->CenterY());
    type = PLAYER;

    Scene * scene = MultiverseRaid::scene;
    avatars[selectedAvatar]->HandleSelectAvatar();
    scene->Add(avatars[selectedAvatar], MOVING);
}

Player::~Player() {
    delete sprite;

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
        spriteState = RIGHT;
    }
    if(leftCommandPressed) {
        Translate(-parsedSpeed, 0);
        spriteState = LEFT;
    }

    if (x < 50) MoveTo(50, y);
    else if (x > game->Width() - 50) MoveTo(game->Width() - 50, y);

    if (y < 50) MoveTo(x, 50);
    else if (y > game->Height() - 50) MoveTo(x, game->Height() - 50);
}

void Player::Update() {
    HandleMovement();

    bool hasToSwitchAvatar = Avatar::ReachedActiveTimeLimit();
    bool chooseAndCanSwitchAvatar = window->KeyDown('Q') && Avatar::CanSwitchAvatar();
    if(hasToSwitchAvatar || chooseAndCanSwitchAvatar) {
        Scene * scene = MultiverseRaid::scene;
        
        Avatar* previousAvatar = avatars[selectedAvatar];
        previousAvatar->HandleUnselectAvatar();
        scene->Remove(previousAvatar, MOVING);

        selectedAvatar = (selectedAvatar + 1) % 3;
        Avatar* currentAvatar = avatars[selectedAvatar];

        currentAvatar->HandleSelectAvatar();
        scene->Add(currentAvatar, MOVING);
        Avatar::ResetTimersData();
    }
}

void Player::Draw() {
    float rotation = spriteState == LEFT ? 0.0f : 180.0f;
    sprite->Draw(x, y, Layer::MIDDLE, 1.0f, rotation);
}
