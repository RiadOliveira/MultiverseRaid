#include "Player.h" 
#include "Missile.h"
#include "MultiverseRaid.h"

void Player::InitializeAttributes() {
    attributes.hp = 10.0f;
    attributes.speed = 180.0f;
    attributes.damage = 8.0f;
    attributes.attackSpeed = 3.0f;
    attributes.defense = 0.3f;
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

    if(window->KeyDown(VK_RIGHT)) {
        Translate(parsedSpeed, 0);
        spriteState = RIGHT;
    }
    if(window->KeyDown(VK_LEFT)) {
        Translate(-parsedSpeed, 0);
        spriteState = LEFT;
    }

    if(window->KeyDown(VK_UP)) Translate(0, -parsedSpeed);
    if(window->KeyDown(VK_DOWN)) Translate(0, parsedSpeed);

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
