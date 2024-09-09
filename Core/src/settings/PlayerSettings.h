#pragma once
#ifndef PLAYERSETTINGS_H
#define PLAYERSETTINGS_H

class PlayerSettings
{
public:
	static constexpr const char* texturePath {"assets/player_white.png"};
	static constexpr int speed {100};
	static constexpr int playerWidth {48};
	static constexpr int playerHeight {48};
	struct BulletSettings
	{
		static constexpr const char* texturePath {"assets/player_white.png"};
		static constexpr int width {3};
		static constexpr int height {20};
		static constexpr int speed {300};
		static constexpr float lifetimeInSeconds {2};
	};
};

#endif // PLAYERSETTINGS_H