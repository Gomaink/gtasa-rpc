#include "weapons.h"
#include <stdio.h>


const WeaponInfo weaponTable[] = {
    { 0, "Fist" },
    { 1, "Brass Knuckles" },
    { 2, "Golf Club" },
    { 3, "Night Stick" },
    { 4, "Knife" },
    { 5, "Bat" },
    { 6, "Shovel" },
    { 7, "Pool Cue" },
    { 8, "Katana" },
    { 9, "Chainsaw" },
    { 10, "Purple Dildo" },
    { 11, "Dildo" },
    { 12, "Vibrator" },
    { 13, "Silver Vibrator" },
    { 14, "Flowers" },
    { 15, "Cane" },
    { 16, "Grenade" },
    { 17, "Teargas" },
    { 18, "Molotov" },
    { 22, "Colt 45" },
    { 23, "Silenced Pistol" },
    { 24, "Desert Eagle" },
    { 25, "Shotgun" },
    { 26, "Sawnoff Shotgun" },
    { 27, "Combat Shotgun" },
    { 28, "Uzi" },
    { 29, "MP5" },
    { 30, "AK-47" },
    { 31, "M4" },
    { 32, "Tec-9" },
    { 33, "Country Rifle" },
    { 34, "Sniper Rifle" },
    { 35, "Rocket Launcher" },
    { 36, "Heat-Seeking RPG" },
    { 37, "Flamethrower" },
    { 38, "Minigun" },
    { 39, "Satchel Charges" },
    { 40, "Detonator" },
    { 41, "Spray Can" },
    { 42, "Fire Extinguisher" },
    { 43, "Camera" },
    { 44, "Night Vision" },
    { 45, "Thermal Goggles" },
    { 46, "Parachute" },
    { 47, "Fake Pistol" }
};


const char* GetWeaponName(DWORD weaponID) {
    for (int i = 0; i < sizeof(weaponTable) / sizeof(weaponTable[0]); ++i) {
        if (weaponTable[i].weaponID == weaponID) {
            return weaponTable[i].weaponName;
        }
    }
    return "Unknown";
}
