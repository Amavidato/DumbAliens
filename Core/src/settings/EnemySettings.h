#pragma once
#ifndef ENEMYSETTINGS_H
#define ENEMYSETTINGS_H

class EnemySettings
{
public:
	static constexpr const char* texturePath {"assets/enemy.png"};
	static constexpr int speed {50};
	static constexpr int numOfEnemiesPerRow {10};
	static constexpr int numOfEnemiesPerColumn {5};
	static constexpr int enemiesMaxHorizontalDistance {200};
	static constexpr int enemiesMaxVerticalDistance {100};
	static constexpr int enemyWidth {24};
	static constexpr int enemyHeight {24};
	static constexpr int NumEnemies () { return numOfEnemiesPerRow * numOfEnemiesPerColumn; }
};
#endif // ENEMYSETTINGS_H