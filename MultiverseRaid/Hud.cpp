#include "Hud.h"
#include "MultiverseRaid.h"

Hud::Hud() {
    font = new Font("Resources/Tahoma14.png");
    font->Spacing("Resources/Tahoma14.dat");
    bold = new Font("Resources/Tahoma14b.png");
    bold->Spacing("Resources/Tahoma14b.dat");

    infoBox = new Sprite("Resources/InfoBox.png");
    keyMap = new Sprite("Resources/Keymap.png");
}

Hud::~Hud() {
    delete font;
    delete bold;
    delete infoBox;
    delete keyMap;
}

void Hud::Update() {

}

void Hud::Draw() {
    infoBox->Draw(game->viewport.left + 140, game->viewport.top + 100, Layer::FRONT);
    keyMap->Draw(game->viewport.left + window->CenterX(), game->viewport.top + window->Height() - 16.0f, Layer::FRONT);

    Color textColor{ 0.7f, 0.7f, 0.7f, 1.0f };

    text.str("");
    text << "Multiverse Raid";
    bold->Draw(40, 62, text.str(), textColor);

    text.str("");
    text << "Janela: " << window->Width() << " x " << window->Height();
    font->Draw(40, 92, text.str(), textColor);

    text.str("");
    text << "Mundo: " << game->Width() << " x " << game->Height();
    font->Draw(40, 112, text.str(), textColor);

    text.str("");
    text << "Viewport: (" << uint(game->viewport.left) << "," << uint(game->viewport.top) << ") a (" << uint(game->viewport.right) << "," << uint(game->viewport.bottom) << ")";
    font->Draw(40, 132, text.str(), textColor);

    text.str("");
    text << "Vida: " << MultiverseRaid::player->Hp();
    font->Draw(40, 152, text.str(), textColor);

    text.str("");
    text << "Onda: " << MultiverseRaid::gameWave;
    font->Draw(40, 172, text.str(), textColor);

    text.str("");
    text << "Inimigos: " << MultiverseRaid::remainingEnemies;
    font->Draw(40, 192, text.str(), textColor);

    text.str("");
    text << "Movimento";
    bold->Draw(window->CenterX() - 84.0f, window->Height() - 7.0f, text.str(), textColor);

    text.str("");
    text << "Atirar";
    bold->Draw(window->CenterX() + 115.0f, window->Height() - 7.0f, text.str(), textColor);
}
