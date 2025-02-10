#ifndef PLAYER_DATA_H
#define PLAYER_DATA_H

#include <windows.h>
#include <stdbool.h>

float GetPlayerHealth(HANDLE hProcess);
float GetPlayerMaxHealth(HANDLE hProcess);
float GetPlayerArmour(HANDLE hProcess);
float GetPlayerPosition(HANDLE hProcess, float* x, float* y, float* z);

int GetPlayerMoney(HANDLE hProcess);
int GetPlayerWantedLevel(HANDLE hProcess);
int GetPlayerWeapon(HANDLE hProcess);
int GetPlayerVehicle(HANDLE hProcess);

bool IsPlayerInVehicle(HANDLE hProcess);

#endif 
