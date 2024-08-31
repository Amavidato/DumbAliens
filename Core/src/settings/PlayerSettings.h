#pragma once
#ifndef PLAYERSETTINGS_H
#define PLAYERSETTINGS_H

class PlayerSettings
{
public:
	static constexpr const char* texturePath {"assets/player.png"};
	static constexpr int speed = 100;
	static constexpr int playerWidth = 48;
	static constexpr int playerHeight = 48;
};

#endif // PLAYERSETTINGS_H