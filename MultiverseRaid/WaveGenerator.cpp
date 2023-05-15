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
    float waveDivisor = (((float) wave) <= 3.0f) ? 4.0f : 8.0f;

    waveSpawningTime = WAVE_TOTAL_TIME / waveDivisor;
    waveEnemiesByTime = 2.0f * wave;

    waveTimer->Start();
    generationTimer->Start();

    if(wave == 1) ResetEnemiesAttributes();
    else UpdateEnemiesAttributes();
}

Enemy* WaveGenerator::GenerateRandomEnemy(int generatedWaveType) {
    if(generatedWaveType >= 9) return new WizardEnemy();
    if(generatedWaveType >= 8) return new AlienEnemy();
    if(generatedWaveType >= 6) return new RobotEnemy();

    RandI enemyType{0, 9};
    int generatedType = enemyType.Rand();

    if(generatedType <= 4) return new RobotEnemy();
    if(generatedType <= 7) return new WizardEnemy();
    return new AlienEnemy();
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

    RandI waveType{0, 9};
    int generatedWaveType = waveType.Rand();

    for(int ind=0 ; ind < (int) waveEnemiesByTime ; ind++) {
        Enemy* enemy = GenerateRandomEnemy(generatedWaveType);
        Point* position = GenerateRandomPosition();

        enemy->MoveTo(position->X(), position->Y());
        MultiverseRaid::scene->Add(enemy, MOVING);

        delete position;
    }

    generationTimer->Reset();
}