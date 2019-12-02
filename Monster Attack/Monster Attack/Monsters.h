#pragma once

#include "Monster.h"

class Monsters {
public:
	//grass
	Move Photosynthesis{"Photosynthesis", "Heal", "Grass", true, 5, 100, 0, 0};
	Move Whip{"Quick Whip", "None", "Grass", false, 40, 100, 0, 0};
	Move Berries{"Poison Berries", "Poision", "Grass", false, 20, 70, 4, 3};
	Move Thorns{"Thorns", "Thorns", "Grass", true, 30, 80, 0, 0};
	Move ThornThrow{"Thorn Throw", "None", "Grass", false, 120, 80, 5, 0};
	Move VineBlock{"Vine Block", "Block", "Grass", true, 50, 90, 3, 3};

	//fire
	Move BurnTouch{"Burn Touch", "Burn", "Fire", false, 20, 30, 2, 1};
	Move FireCircle{"Fire Circle", "None", "Fire", false, 40, 100, 0, 0};
	Move FireSpin{"Fire Spin", "Burn", "Fire", false, 25, 90, 4, 2};
	Move Overheat{"Overheat", "Overheat", "Fire", true, 75, 100, 0, 0};
	Move ShadowFire{"Shadow Fire", "None", "Fire", false, 150, 80, 5, 0};
	Move HeatWave{"Heat Wave", "Extreme Heat", "Fire", false, 10, 80, 3, 3};

	//water
	Move GoodCurrent{"Good Current", "Speedy Water", "Water", true, 10, 100, 0, 3};
	Move RainStorm{"Rain Storm", "None", "Water", false, 40, 100, 0, 0};
	Move Surf{"Surf", "Speed", "Water", true, 20, 100, 3, 3};
	Move MuddyWater{"Muddy Water", "Slow Water", "Water", false, 20, 100, 0, 2};
	Move StormyNight{"Stormy Night", "None", "Water", false, 40, 100, 0, 0};
	Move Drown{"Drown", "Drowned", "Water", false, 15, 90, 3, 3};

	//dark
	Move LettuceScythe{"Lettuce Scythe", "None", "Dark", false, 40, 100, 0, 0};
	Move ThornCage{"Thorn Cage", "Bleeding", "Dark", false, 17, 80, 4, 2};
	Move ShadowClaw{"Shadow Claw", "None", "Dark", false, 40, 100, 0, 0};
	Move Shroud{"Shroud", "Speed", "Dark", true, 20, 100, 3, 3};
	Move KrakenSummon{"Kraken Summon", "Kraken", "Dark", false, 200, 30, 3, 0};
	Move Sharpen{"Sharpen", "Sharpen", "Dark", true, 15, 100, 3, 3};

	Move Mimic{ "Mimic", "Mimic", "Dark", false, 0, 100, 0, 0 };
	Move MimicPassive{ "Mimic Passive", "MimicPassive", "Dark", false, 0, 100, 0, 0 };

	//light
	Move Beam{"Beam of Light", "None", "Light", false, 120, 90, 5, 0};
	Move Kale{"Kimble Kale", "Heal", "Light", true, 20, 100, 7, 0};
	Move BlazingSun{"Blazing Sun", "None", "Light", false, 120, 90, 5, 0};
	Move BlindingLight{"Blinding Light", "Blind", "Light", false, 50, 100, 2, 1};
	Move ThunderStorm{"Thunder Storm", "None", "Light", false, 150, 80, 5, 0};
	Move SuctionCups{"Suction Cups", "Lifesteal", "Light", false, 40, 90, 2, 0};

	//monsters
	Monster _1{"Nugget Lord", "Grass", "Light", 100, 50, 100, 50, Beam, Whip, Berries, Kale, Photosynthesis};
	Monster _2{ "Grim Nugget", "Grass", "Dark", 50, 90, 80, 50, ThornThrow, LettuceScythe, ThornCage, VineBlock, Thorns };
	Monster _3{"Kayle", "Fire", "Light", 60, 80, 70, 80, BlazingSun, FireCircle, FireSpin, BlindingLight, BurnTouch};
	Monster _4{"Doomhound", "Fire", "Dark", 130, 40, 90, 40, ShadowFire, ShadowClaw, HeatWave, Shroud, Overheat};
	Monster _5{"Squsher", "Water", "Light", 65, 100, 95, 40, ThunderStorm, RainStorm, SuctionCups, Surf, GoodCurrent};
	Monster _6{"Scubabear", "Water", "Dark", 60, 60, 120, 60, KrakenSummon, StormyNight, Drown, Sharpen, MuddyWater};
	Monster _7{ "ERROR", "Error", "Dark", 100, 100, 100, 100, Mimic , Mimic , Mimic , Mimic, MimicPassive };

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