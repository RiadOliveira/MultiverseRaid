#include "WaveGenerator.h"
#include "WizardEnemy.h"
#include "RobotEnemy.h"
#include "AlienEnemy.h"
#include "MultiverseRaid.h"
#include "Random.h"

float WaveGenerator::WAVE_TOTAL_TIME = 32.0f;

WaveGenerator::WaveGenerator(): waveTimer(new Timer()), generationTimer(new Timer()) {
}

WaveGenerator::~WaveGenerator() {
    delete waveTimer;
    delete generationTimer;
}

void WaveGenerator::ResetEnemiesAttributes() {
    WizardEnemy::ResetWaveAttributes();
    RobotEnemy::ResetWaveAttributes();
    AlienEnemy::ResetWaveAttributes();
}

void WaveGenerator::UpdateEnemiesAttributes() {
    WizardEnemy::UpdateWaveAttributes();
    RobotEnemy::UpdateWaveAttributes();
    AlienEnemy::UpdateWaveAttributes();
}

void WaveGenerator::Start(uint w) {
    wave = w;
    finishedCurrentWave = false;
    float waveDivisor = wave <= 3 ? 4 : 8;

    waveSpawningTime = WAVE_TOTAL_TIME / waveDivisor;
    waveEnemiesByTime = (float) pow(2, 2 + wave) / waveDivisor;

    waveTimer->Start();
    generationTimer->Start();

    if(wave == 1) ResetEnemiesAttributes();
    else UpdateEnemiesAttributes();
}

Enemy* WaveGenerator::GenerateRandomEnemy() {
    RandI enemyType{0, 2};

    switch(enemyType.Rand()) {
        case WIZARD: return new WizardEnemy();
        case ROBOT: return new RobotEnemy();
        case ALIEN: return new AlienEnemy();
        default: return new RobotEnemy();
    }
}

Point* WaveGenerator::GenerateRandomPosition() {
    Player* player = MultiverseRaid::player;
    RandI side{0, 1};
    RandF distance{290.0f, 1000.0f};

    return new Point(
        player->X() + (side.Rand() ? 1 : -1) * distance.Rand(),
        player->Y() - (side.Rand() ? 1 : -1) * distance.Rand()
    );
}

void WaveGenerator::UpdateGeneration() {
    if(waveTimer->Elapsed() >= (WAVE_TOTAL_TIME + 2.0f)) {
        bool allEnemiesAreDead = MultiverseRaid::remainingEnemies == 0;
        if(allEnemiesAreDead) finishedCurrentWave = true;

        return;
    }
    if(generationTimer->Elapsed() < waveSpawningTime) return;

    for(int ind=0 ; ind < (int) waveEnemiesByTime ; ind++) {
        Enemy* enemy = GenerateRandomEnemy();
        Point* position = GenerateRandomPosition();

        enemy->MoveTo(position->X(), position->Y());
        MultiverseRaid::scene->Add(enemy, STATIC);

        delete position;
    }

    generationTimer->Reset();
}