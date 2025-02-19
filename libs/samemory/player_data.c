#include <stdbool.h>
#include "player_data.h"
#include "addresses.h"

float GetPlayerHealth(HANDLE hProcess) {
    DWORD baseAddress;
    ReadProcessMemory(hProcess, (LPVOID)PLAYER_BASE_ADDRESS, &baseAddress, sizeof(DWORD), NULL);
    DWORD healthAddress = baseAddress + HEALTH_ADDRESS;
    float healthValue;
    ReadProcessMemory(hProcess, (LPVOID)healthAddress, &healthValue, sizeof(float), NULL);
    return healthValue;
}

float GetPlayerMaxHealth(HANDLE hProcess) {
    DWORD baseAddress;
    ReadProcessMemory(hProcess, (LPVOID)PLAYER_BASE_ADDRESS, &baseAddress, sizeof(DWORD), NULL);
    DWORD healthAddress = baseAddress + MAX_HEALTH_ADDRESS;
    float healthValue;
    ReadProcessMemory(hProcess, (LPVOID)healthAddress, &healthValue, sizeof(float), NULL);
    return healthValue;
}

float GetPlayerArmour(HANDLE hProcess) {
    DWORD baseAddress;
    ReadProcessMemory(hProcess, (LPVOID)PLAYER_BASE_ADDRESS, &baseAddress, sizeof(DWORD), NULL);
    DWORD armourAddress = baseAddress + ARMOUR_ADDRESS;
    float armourValue;
    ReadProcessMemory(hProcess, (LPVOID)armourAddress, &armourValue, sizeof(float), NULL);
    return armourValue;
}

float GetPlayerPosition(HANDLE hProcess, float* x, float* y, float* z) {
    float value = 0;
    ReadProcessMemory(hProcess, (LPVOID)X_ADDRESS, x, sizeof(value), NULL);
    ReadProcessMemory(hProcess, (LPVOID)Y_ADDRESS, y, sizeof(value), NULL);
    ReadProcessMemory(hProcess, (LPVOID)Z_ADDRESS, z, sizeof(value), NULL);
    return value;
}

int GetPlayerMoney(HANDLE hProcess) {
    int value = 0;
    ReadProcessMemory(hProcess, (LPVOID)MONEY_ADDRESS, &value, sizeof(value), NULL);
    return value;
}

int GetPlayerWantedLevel(HANDLE hProcess) {
    int value = 0;
    ReadProcessMemory(hProcess, (LPVOID)WANTED_ADDRESS, &value, sizeof(value), NULL);
    return value;
}

int GetPlayerWeapon(HANDLE hProcess) {
    int value = 0;
    ReadProcessMemory(hProcess, (LPVOID)WEAPON_ID_ADDRESS, &value, sizeof(value), NULL);
    return value;
}

int GetPlayerVehicle(HANDLE hProcess) {
    int value = 0;
    ReadProcessMemory(hProcess, (LPVOID)CURRENT_VEHICLE_ID_ADDRESS, &value, sizeof(value), NULL);
    return value;
}

bool IsPlayerInVehicle(HANDLE hProcess) {
    DWORD baseAddress;
    ReadProcessMemory(hProcess, (LPVOID)PLAYER_BASE_ADDRESS, &baseAddress, sizeof(DWORD), NULL);
    
    DWORD currentVehiclePtr;
    ReadProcessMemory(hProcess, (LPVOID)IN_VEHICLE_ADDRESS, &currentVehiclePtr, sizeof(DWORD), NULL);
    
    return currentVehiclePtr != 0;
}