#pragma once

#include "Monster.h"

class Monsters {
public:
	//grass
	Move Photosynthesis{"Photosynthesis", "Heal", "Grass", true, 5, 100, 0, 0, FOREGROUND_GREEN};
	Move Whip{"Quick Whip", "None", "Grass", false, 40, 100, 0, 0, FOREGROUND_GREEN};
	Move Berries{"Poison Berries", "Poision", "Grass", false, 20, 70, 4, 3, FOREGROUND_GREEN};
	Move Thorns{"Thorns", "Thorns", "Grass", true, 40, 80, 0, 0, FOREGROUND_GREEN};
	Move ThornThrow{"Thorn Throw", "None", "Grass", false, 150, 80, 5, 0, FOREGROUND_GREEN};
	Move VineBlock{"Vine Block", "Block", "Grass", true, 50, 90, 3, 3, FOREGROUND_GREEN};

	//fire
	Move BurnTouch{"Burn Touch", "Burn", "Fire", false, 20, 30, 2, 1, FOREGROUND_RED};
	Move FireCircle{"Fire Circle", "None", "Fire", false, 40, 100, 0, 0, FOREGROUND_RED};
	Move FireSpin{"Fire Spin", "Burn", "Fire", false, 25, 90, 4, 2, FOREGROUND_RED};
	Move Overheat{"Overheat", "Overheat", "Fire", true, 75, 100, 0, 0, FOREGROUND_RED};
	Move ShadowFire{"Shadow Fire", "None", "Fire", false, 150, 80, 5, 0, FOREGROUND_RED};
	Move HeatWave{"Heat Wave", "Extreme Heat", "Fire", false, 10, 80, 3, 3, FOREGROUND_RED};

	//water
	Move GoodCurrent{"Good Current", "Speedy Water", "Water", true, 10, 100, 0, 3, FOREGROUND_BLUE};
	Move RainStorm{"Rain Storm", "None", "Water", false, 40, 100, 0, 0, FOREGROUND_BLUE};
	Move Surf{"Surf", "Speed", "Water", true, 20, 100, 3, 3, FOREGROUND_BLUE};
	Move MuddyWater{"Muddy Water", "Slow Water", "Water", false, 20, 100, 0, 2, FOREGROUND_BLUE};
	Move StormyNight{"Stormy Night", "None", "Water", false, 40, 100, 0, 0, FOREGROUND_BLUE};
	Move Drown{"Drown", "Drowned", "Water", false, 15, 90, 3, 3, FOREGROUND_BLUE};

	//dark
	Move LettuceScythe{"Lettuce Scythe", "None", "Dark", false, 40, 100, 0, 0, FOREGROUND_INTENSITY};
	Move ThornCage{"Thorn Cage", "Bleeding", "Dark", false, 17, 80, 4, 2, FOREGROUND_INTENSITY};
	Move ShadowClaw{"Shadow Claw", "None", "Dark", false, 40, 100, 0, 0, FOREGROUND_INTENSITY};
	Move Shroud{"Shroud", "Speed", "Dark", true, 20, 100, 3, 3, FOREGROUND_INTENSITY};
	Move KrakenSummon{"Kraken Summon", "Kraken", "Dark", false, 200, 30, 3, 0, FOREGROUND_INTENSITY};
	Move Sharpen{"Sharpen", "Sharpen", "Dark", true, 15, 100, 3, 3, FOREGROUND_INTENSITY};

	//light
	Move Beam{"Beam of Light", "None", "Light", false, 120, 90, 5, 0, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY};
	Move Kale{"Kimble Kale", "Heal", "Light", true, 20, 100, 7, 0, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY};
	Move BlazingSun{"Blazing Sun", "None", "Light", false, 120, 90, 5, 0, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY};
	Move BlindingLight{"Blinding Light", "Blind", "Light", false, 50, 100, 2, 1, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY};
	Move ThunderStorm{"Thunder Storm", "None", "Light", false, 150, 80, 5, 0, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY};
	Move SuctionCups{"Suction Cups", "Lifesteal", "Light", false, 40, 90, 2, 0, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY};

	//monsters
	Monster _1{"Nugget Lord", "Grass", "Light", 100, 50, 100, 50, FOREGROUND_GREEN | FOREGROUND_INTENSITY, Beam, Whip, Berries, Kale, Photosynthesis};
	Monster _2{"Grim Nugget", "Grass", "Dark", 50, 120, 80, 50, FOREGROUND_GREEN, ThornThrow, LettuceScythe, ThornCage, VineBlock, Thorns};
	Monster _3{"Kayle", "Fire", "Light", 60, 90, 70, 80, FOREGROUND_RED | FOREGROUND_INTENSITY, BlazingSun, FireCircle, FireSpin, BlindingLight, BurnTouch};
	Monster _4{"Doomhound", "Fire", "Dark", 130, 40, 90, 40, FOREGROUND_RED, ShadowFire, ShadowClaw, HeatWave, Shroud, Overheat};
	Monster _5{"Squsher", "Water", "Light", 65, 100, 95, 40, FOREGROUND_BLUE | FOREGROUND_INTENSITY, ThunderStorm, RainStorm, SuctionCups, Surf, GoodCurrent};
	Monster _6{"Scubabear", "Water", "Dark", 60, 60, 120, 60, FOREGROUND_BLUE, KrakenSummon, StormyNight, Drown, Sharpen, MuddyWater};

	//grass
	/*Monster _1{"Skorpislash", "Grass", "Light", 101, 70, 70, 80, FOREGROUND_GREEN, grass_punch, shell_shield, earth_bombardment, kill, light_punch};
	Monster _2{"Pigeonite", "Grass", "Dark", 82, 80, 80, 80, FOREGROUND_GREEN, grass_punch, dark_punch, flame_punch, kill, light_punch};
	Monster _3{"Irobug", "Grass", "Light", 102, 70, 150, 80, FOREGROUND_GREEN | FOREGROUND_INTENSITY, grass_punch, light_punch, earth_bombardment, kill, light_punch};
	Monster _4{"Slowphant", "Grass", "Dark", 81, 80, 80, 80, FOREGROUND_GREEN | FOREGROUND_INTENSITY, grass_punch, light_punch, flame_punch, kill, light_punch};
	//fire
	Monster _5{"Skeleking", "Fire", "Light", 20, 100, 190, 40, FOREGROUND_RED, flame_punch, dark_punch, self_sacrifice, dark_magic, light_punch};
	Monster _6{"Flamepie", "Fire", "Dark", 83, 80, 80, 80, FOREGROUND_RED, flame_punch, dark_punch, flame_punch, kill, light_punch};
	Monster _7{"Dragithe", "Fire", "Light", 105, 70, 70, 80, FOREGROUND_RED | FOREGROUND_INTENSITY, flame_punch, light_punch, volcanic_shield, kill, light_punch};
	Monster _8{"Pheonix", "Fire", "Dark", 86, 80, 80, 80, FOREGROUND_RED | FOREGROUND_INTENSITY, flame_punch, light_punch, melt_armor, superPower, Photosynthesis};
	//water
	Monster _9{"Quilling", "Water", "Light", 104, 70, 70, 80, FOREGROUND_GREEN, water_punch, dark_punch, flame_punch, kill, light_punch};
	Monster _10{"Gladiawhale", "Water", "Dark", 85, 80, 80, 80, FOREGROUND_GREEN, water_punch, dark_punch, flame_punch, kill, light_punch};
	Monster _11{"Penguinite", "Water", "Light", 103, 70, 70, 80, FOREGROUND_GREEN | FOREGROUND_INTENSITY, water_punch, light_punch, flame_punch, kill, light_punch};
	Monster _12{"Oystora", "Water", "Dark", 84, 80, 80, 80, FOREGROUND_GREEN | FOREGROUND_INTENSITY, water_punch, light_punch, tsunami_slam, kill, light_punch};*/
};

struct Party {
	string name;
	Monster mon[6];
	int currentMonSlot = 1;

	Monster* GetCurMon() { return &mon[currentMonSlot]; }
};