#pragma once
#ifndef ENEMYSETTINGS_H
#define ENEMYSETTINGS_H
#include "GameSettings.h"
#include "PlayerSettings.h"

class EnemySettings
{
public:
	static constexpr const char* texturePath {"assets/enemy.png"};
	static constexpr int speed {50};
	static constexpr int numOfEnemiesPerRow {10};
	static constexpr int numOfEnemiesPerColumn {5};
	static constexpr int enemyWidth {32};
	static constexpr int enemyHeight {32};
	static constexpr int enemyPadding {5};
	static constexpr int enemiesMaxHorizontalDistance {GameSettings::windowWidth - numOfEnemiesPerRow * enemyWidth - numOfEnemiesPerRow * enemyPadding};
	static constexpr int enemiesMaxVerticalDistance {GameSettings::windowHeight - PlayerSettings::playerHeight - (numOfEnemiesPerColumn * enemyHeight) - (numOfEnemiesPerColumn * enemyPadding) };
	static constexpr int NumEnemies () { return numOfEnemiesPerRow * numOfEnemiesPerColumn; }
};
#endif // ENEMYSETTINGS_H