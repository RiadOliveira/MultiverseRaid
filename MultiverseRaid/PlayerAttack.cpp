#include "PlayerAttack.h"
#include "MultiverseRaid.h"

PlayerAttack::PlayerAttack() {
    type = PLAYER_ATTACK;
    MoveTo(x, y, Layer::BACK);
}

PlayerAttack::~PlayerAttack() {
}