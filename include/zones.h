#ifndef ZONES_H
#define ZONES_H

typedef struct {
    char name[28];
    float area[6];
} SAZone;

extern SAZone gSAZones[];

const char* getPlayerZone(float x, float y, float z);

#endif
