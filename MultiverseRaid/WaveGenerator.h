#ifndef _WAVE_GENERATOR_H_
#define _WAVE_GENERATOR_H_

#include "Types.h"
#include "Enemy.h"
#include "Timer.h"

class WaveGenerator {
    private:
        static float WAVE_TOTAL_TIME;

        float waveSpawningTime = 0.0f, waveEnemiesByTime = 0.0f;
        bool finishedCurrentWave = true;
        uint wave = 0;

        Timer* waveTimer = nullptr;
        Timer* generationTimer = nullptr;

        Enemy* GenerateRandomEnemy(int generatedWaveType);
        Point* GenerateRandomPosition();

        void ResetEnemiesAttributes();
        void UpdateEnemiesAttributes();
    public:
        WaveGenerator();
        ~WaveGenerator();

        bool FinishedCurrentWave();

        void Start(uint wave);
        void UpdateGeneration();
};

inline bool WaveGenerator::FinishedCurrentWave() { return finishedCurrentWave; }

#endif