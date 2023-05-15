#include "Hud.h"
#include "MultiverseRaid.h"

Hud::Hud() {
    font = new Font("Resources/TwCenMT12.png");
    font->Spacing("Resources/TwCenMT12.dat");
    bold = new Font("Resources/TwCenMT12Bold.png");
    bold->Spacing("Resources/TwCenMT12Bold.dat");
}

Hud::~Hud() {
    delete font;
    delete bold;
}

void Hud::Update() {
}

void Hud::Draw() {
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
}
