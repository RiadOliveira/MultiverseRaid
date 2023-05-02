#include "Delay.h"
#include "MultiverseRaid.h"
#include "Hud.h"

Delay::Delay()
{
    logo = new Sprite("Resources/Logo.png");
    timer.Start();
    notPlayed = true;
}

Delay::~Delay()
{
    delete logo;
}

void Delay::Update()
{
    if (notPlayed && timer.Elapsed(2.0f))
    {
        MultiverseRaid::audio->Play(START);
        notPlayed = false;
    }

    if (timer.Elapsed(2.0f))
    {
        MultiverseRaid::audio->Play(THEME, true);
        MultiverseRaid::viewHUD = true;
        MultiverseRaid::scene->Delete();
    }
}

void Delay::Draw()
{
    logo->Draw(game->viewport.left + window->CenterX() , game->viewport.top + window->CenterY(), Layer::FRONT);
}
