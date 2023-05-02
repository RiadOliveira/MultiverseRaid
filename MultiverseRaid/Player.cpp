#include "Player.h" 
#include "Missile.h"
#include "MultiverseRaid.h"

void Player::InitializeAttributes() {
    attributes.hp = 10.0f;
    attributes.speed = 180.0f;
    attributes.damage = 8.0f;
    attributes.attackSpeed = 3.0f;
    attributes.defense = 0.3f;
    attributes.range = 290.0f;
}

Player::Player(): spriteState(LEFT), level(0) {
    sprite = new Sprite("Resources/Player.png");

    BBox(new Circle(18.0f));
    MoveTo(game->CenterX(), game->CenterY());
    InitializeAttributes();
    type = PLAYER;
}

Player::~Player() {
    delete sprite;
}

void Player::LevelUp() {
    level++;

    attributes.hp = 10.0f + level * 5.0f;
    attributes.speed += 20.0f;
    attributes.damage += 2.0f;
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
}

void Player::Draw() {
    float rotation = spriteState == LEFT ? 0.0f : 180.0f;
    sprite->Draw(x, y, Layer::MIDDLE, 1.0f, rotation);
}
