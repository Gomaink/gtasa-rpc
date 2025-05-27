#include <stddef.h>

#ifndef ZONES_H
#define ZONES_H

typedef struct {
    char name[28];
    float area[6];
} SAZone;

extern SAZone gSAZones[];

void getPlayerZone(float x, float y, float z, char* buffer, size_t bufferSize);


#endif
