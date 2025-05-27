#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP_FUNC Sleep(1000)
#else
    #include <unistd.h>
    #define SLEEP_FUNC sleep(1)
#endif

#include <discord_rpc.h>
#include "samemory.h"

static void handleDiscordReady(const DiscordUser* user) {
    printf("Connected as %s#%s\n", user->username, user->discriminator);
}

static void handleDiscordError(int code, const char* message) {
    printf("Error %d: %s\n", code, message);
}

static void handleDiscordDisconnected(int code, const char* message) {
    printf("Disconnected %d: %s\n", code, message);
}

int main() {
    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));
    handlers.ready = handleDiscordReady;
    handlers.errored = handleDiscordError;
    handlers.disconnected = handleDiscordDisconnected;

    Discord_Initialize("1338607854659178547", &handlers, 1, NULL);

    const char* processName = "gta_sa.exe";

    DWORD processId = GetProcessIdByName(processName);
    if (processId == 0) {
        fprintf(stderr, "GTA: San Andreas is not running.\n");
        Discord_Shutdown();
        return 1;
    }

    HANDLE hProcess = OpenProcess(PROCESS_VM_READ, FALSE, processId);
    if (hProcess == NULL) {
        fprintf(stderr, "Failed to open GTA San Andreas.\n");
        Discord_Shutdown();
        return 1;
    }

    DiscordRichPresence presence;
    memset(&presence, 0, sizeof(presence));
    presence.startTimestamp = time(NULL);

    while (1) {
        Discord_RunCallbacks();

        float x, y, z;
        GetPlayerPosition(hProcess, &x, &y, &z);
        int playerMoney = GetPlayerMoney(hProcess);
        int playerWanted = GetPlayerWantedLevel(hProcess);
        int playerWeapon = GetPlayerWeapon(hProcess);
        bool playerInVehicle = IsPlayerInVehicle(hProcess);

        char stateText[32], largeImageText[32], weaponText[32], zoneText[64];;
        getPlayerZone(x, y, z, zoneText, sizeof(zoneText));

        snprintf(stateText, sizeof(stateText), "$%d", playerMoney);
        snprintf(weaponText, sizeof(weaponText), "%d", playerWeapon);
        snprintf(largeImageText, sizeof(largeImageText), "%s", playerInVehicle ? "In a vehicle." : "On foot.");

        presence.state = stateText;
        presence.details = zoneText;
        presence.largeImageKey = "sa-logo";
        presence.largeImageText = largeImageText;
        presence.smallImageKey = weaponText;
        presence.smallImageText = GetWeaponName(playerWeapon);

        Discord_UpdatePresence(&presence);

        SLEEP_FUNC;
    }

    CloseHandle(hProcess);
    Discord_Shutdown();
    return 0;
}
