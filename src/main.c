#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <discord_rpc.h>

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP_FUNC Sleep(1000)  // Windows usa Sleep em milissegundos
#else
    #include <unistd.h>
    #define SLEEP_FUNC sleep(1)  // Linux usa sleep em segundos
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

    DiscordRichPresence presence;
    memset(&presence, 0, sizeof(presence));
    presence.state = "$3000";
    presence.details = "Vinewood (In vehicle)";
    presence.startTimestamp = time(NULL);
    presence.largeImageKey = "sa-logo";
    presence.largeImageText = "Launcher Alternativo";

    Discord_UpdatePresence(&presence);

    while (1) {
        Discord_RunCallbacks();
        SLEEP_FUNC;
    }

    Discord_Shutdown();
    return 0;
}
