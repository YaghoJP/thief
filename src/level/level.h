#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "singletons/game_manager.h"
#include "entities/collectables.h"
#include "entities/chest.h"
#include "sprites.h"

#define MAP_WIDTH 20
#define MAP_HEIGTH 14

typedef struct {
    const Map* map;
    const u16* collision_data;
    const TileSet* tileset;
    const Palette* palette;
    Collectable* c[30];
    Chest* chest_key;
    u8 qt_collectables;
} Level;


//Level Collision
extern u16 LEVEL_1_collision[280];
extern u16 LEVEL_2_collision[280];

Level* LEVEL_init(u16* ind, const MapDefinition* map, const TileSet* ts, const Palette* pal, u8 level_coll);
void LEVEL_free(Level *l);

void LEVEL_collect(f16 x, f16 y, Collectable** col,u8 qt_collectables);
void LEVEL_key_collect(Chest* c);

#endif