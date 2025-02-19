#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>
#include <windows.h>

#include <discord_rpc.h>
#include "samemory.h"

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP_FUNC Sleep(1000)
#else
    #include <unistd.h>
    #define SLEEP_FUNC sleep(1)
#endif

void handleDiscordReady(const DiscordUser* user) {
    printf("Conectado como %s#%s\n", user->username, user->discriminator);
}

void handleDiscordError(int code, const char* message) {
    printf("Erro %d: %s\n", code, message);
}

void handleDiscordDisconnected(int code, const char* message) {
    printf("Desconectado %d: %s\n", code, message);
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
        return 1;
    }

    HANDLE hProcess = OpenProcess(PROCESS_VM_READ, FALSE, processId);
    if (hProcess == NULL) {
        fprintf(stderr, "Failed to open GTA San Andreas.\n");
        return 1;
    }

    float x, y, z;
    GetPlayerPosition(hProcess, &x, &y, &z);
    int playerMoney = GetPlayerMoney(hProcess);
    int playerWanted = GetPlayerWantedLevel(hProcess);
    int playerWeapon = GetPlayerWeapon(hProcess);
    int playerVehicle = GetPlayerVehicle(hProcess);
    float playerHealth = GetPlayerHealth(hProcess);
    float playerMaxHealth = GetPlayerMaxHealth(hProcess);
    float playerArmour = GetPlayerArmour(hProcess);
    bool playerInVehicle = IsPlayerInVehicle(hProcess);

    DiscordRichPresence presence;
    memset(&presence, 0, sizeof(presence));

    char formatedText[32];  
    sprintf(formatedText, "$%d", playerMoney);
    presence.state = formatedText;
    presence.details = getPlayerZone(x, y, z);

    presence.startTimestamp = time(NULL);
    presence.largeImageKey = "sa-logo";

    sprintf(formatedText, "Wanted Level: %d", playerWanted);
    presence.largeImageText = formatedText;

    Discord_UpdatePresence(&presence);
    CloseHandle(hProcess);

    while (1) {
        Discord_RunCallbacks();
        SLEEP_FUNC;
    }

    Discord_Shutdown();
    return 0;
}
