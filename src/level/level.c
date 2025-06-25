#include "level.h"

void LEVEL_collectables_init(u16* ind, const u16 map_collision[280], Level *l);


//Mapas de colisão de cada level
u16 LEVEL_1_collision[280] = {
2,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
2,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,2,
2,1,0,0,1,0,1,2,6,1,1,1,1,1,1,1,1,1,1,2,
2,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,2,
2,2,2,2,1,1,1,2,2,2,2,2,2,2,2,0,1,1,2,2,
2,5,5,5,1,1,1,2,1,1,1,1,1,1,1,1,1,1,5,2,
2,5,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,5,2,
2,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,2,
2,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,2,
2,5,5,5,1,1,1,0,0,1,1,1,0,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,2,
2,5,5,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,1,2,
2,5,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,4,4,2
};

u16 LEVEL_2_collision[280] = {
2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,2,
2,5,1,1,0,0,0,0,0,0,0,0,5,2,0,0,0,0,0,2,
2,5,1,0,0,0,0,0,0,0,0,0,5,2,0,0,0,0,0,2,
2,5,1,1,0,0,0,0,0,0,0,0,5,2,0,0,2,2,2,2,
2,2,2,2,2,2,2,0,0,2,2,2,2,2,0,0,0,0,5,2,
2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,5,2,
2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,5,2,
2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,2,2,2,2,
2,0,0,0,2,2,2,2,2,2,0,0,0,2,0,0,0,0,0,2,
2,0,0,0,2,5,5,5,0,0,0,0,0,2,0,0,0,0,0,2,
2,0,0,0,2,5,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
2,0,0,0,2,5,0,0,0,0,0,0,0,0,0,0,2,0,6,2,
2,0,0,0,2,5,5,5,2,0,0,0,0,0,0,0,2,0,1,2,
2,4,4,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2
};

u16 LEVEL_3_collision[280] = {
2,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
2,0,0,0,5,5,5,5,5,2,5,5,2,5,5,2,0,0,0,2,
2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,6,2,
2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
2,1,5,5,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,
2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,
2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5,5,2,
2,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,2,
2,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,2,
2,5,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
2,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
2,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,4,4,2
};

u16 tilemap_buff[SCREEN_TILES_W * SCREEN_TILES_H];

static void LEVEL_scroll_map(s16 x, s16 y, Map* map) 
{
    MAP_getTilemapRect(map, x/16, y/16, SCREEN_TILES_W/2, SCREEN_TILES_H/2, FALSE, tilemap_buff);
    
    VDP_setTileMapDataRect(BG_A, tilemap_buff, 0, 0, SCREEN_TILES_W, SCREEN_TILES_H, SCREEN_TILES_W, DMA_QUEUE);
}

Level* LEVEL_init(u16* ind, const MapDefinition* map, const TileSet* ts, const Palette* pal, u8 level_coll) 
{
    PAL_setPalette(PAL_MAP, pal->data, DMA);
    VDP_loadTileSet(ts, *ind, DMA);

    Map *m = MAP_create(map, BG_A, TILE_ATTR_FULL(PAL_MAP, FALSE, FALSE, FALSE, *ind));
    
    LEVEL_scroll_map(0, 0, m);
    
    Level *l = MEM_alloc(sizeof(Level));

    switch (level_coll)
    {
    case 1:
        l->collision_data = LEVEL_1_collision;
        LEVEL_collectables_init(ind, l->collision_data, l);
        break;
    case 2:
        l->collision_data = LEVEL_2_collision;
        LEVEL_collectables_init(ind, l->collision_data, l);
        break;
    case 3:
        l->collision_data = LEVEL_3_collision;
        LEVEL_collectables_init(ind, l->collision_data, l);
        break;
    default:
        break;
    }
    l->map = m;
    l->palette = pal;
    l->tileset = ts;
    *ind = *ind + ts->numTile;
    return l;
}

void LEVEL_free(Level *l)
{
    MEM_free(l);
}

void LEVEL_collectables_init(u16* ind, const u16 map_collision[280], Level *l)
{
    l->qt_collectables = 0;
    for(s16 y=0; y<MAP_HEIGTH; y++)
    {
        for(s16 x=0; x<MAP_WIDTH; x++)
        {
            u16 tile = map_collision[y * MAP_WIDTH + x];

            if(tile == 5) l->c[l->qt_collectables++] = COLLECTABLE_init(ind, x*16, y*16, &spr_diamond);
            if(tile == 6) l->chest_key = CHEST_init(ind, x*16, y*16, &spr_chest);
        }
    }
}

void LEVEL_collect(f16 x, f16 y, Collectable** col, u8 qt_collectables)
{
    f16 px = x*16;
    f16 py = y*16;

    for(s16 i=0; i<qt_collectables; i++)
    {
        if(F16_toInt(col[i]->ch->no->x) == px && F16_toInt(col[i]->ch->no->y) == py){
            if(col[i]->is_active)
            {
                col[i]->is_active = FALSE;
                score += col[i]->value;
                COLLECTABLE_free(col[i]);
            }
        }
    }
}

void LEVEL_key_collect(Chest* c)
{
    //CHEST_free(c);
    SPR_setAnim(c->ch->no->sprite, 1);
    signal_key_collected = TRUE;
}