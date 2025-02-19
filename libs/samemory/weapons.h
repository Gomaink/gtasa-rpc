#ifndef WEAPONS_H
#define WEAPONS_H

#include <windows.h>


typedef struct {
    DWORD weaponID;
    const char* weaponName;
} WeaponInfo;


const char* GetWeaponName(DWORD weaponID);

#endif 
