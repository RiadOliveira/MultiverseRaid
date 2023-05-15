#include "Delay.h"
#include "MultiverseRaid.h"
#include "WaveHighlight.h"
#include "Hud.h"

Delay::Delay() {
    logo = new Sprite("Resources/Logo.png");
    timer.Start();
}

Delay::~Delay() {
    delete logo;
}

void Delay::Update() {
    if (timer.Elapsed(3.0f)) {
        MultiverseRaid::viewHUD = true;
        MultiverseRaid::scene->Add(new WaveHighlight(), STATIC);
        MultiverseRaid::scene->Delete();
    }
}

void Delay::Draw() {
    logo->Draw(
        game->viewport.left + window->CenterX(),
        game->viewport.top + window->CenterY(), Layer::FRONT,
        scale, rotation, Color(1, 1, 1, 3.0f - timer.Elapsed())
    );
}
