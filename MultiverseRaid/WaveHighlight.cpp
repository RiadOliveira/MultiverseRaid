#include "WaveHighlight.h"
#include "MultiverseRaid.h"

WaveHighlight::WaveHighlight() {
    font = new Font("Resources/TwCenMT72Bold.png");
    font->Spacing("Resources/TwCenMT72Bold.dat");

    timer.Start();
}

WaveHighlight::~WaveHighlight() {
    delete font;
}

void WaveHighlight::Update() {
    if (timer.Elapsed(3.0f)) MultiverseRaid::scene->Delete();
}

void WaveHighlight::Draw() {
    text.str("");
    text << "ONDA " << MultiverseRaid::gameWave;

    float opacity = min(timer.Elapsed(), 3 - timer.Elapsed());
    font->Draw(
        window->CenterX() - 96, 128,
        text.str(), Color(1, 1, 1, opacity), Layer::FRONT
    );
}
