#include "Avatar.h"

Avatar::Avatar() {
}

Avatar::~Avatar() {
}

void Avatar::Update() {
    PassiveUpdate();
    UltUpdate();
}

void Avatar::Draw() {
    PassiveDraw();
    UltDraw();
}