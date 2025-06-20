#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "base/character.h"

typedef struct Enemy Enemy;
typedef void (*ENEMY_update_funcao)(Enemy* e, Character* p);

#define DETECT_PLAYER_WIDTH_H 1
#define DETECT_PLAYER_HEIGTH_H 1

#define DETECT_PLAYER_WIDTH_V 1
#define DETECT_PLAYER_HEIGTH_V 1

#define SPR_PLAYER 8

typedef enum TYPE {
    PATROL, 
    FIXED
} TYPE;

struct Enemy{
    Character* ch;
    TYPE type_enemy;
    fix16 pos_x_start;
    fix16 pos_y_start;
    fix16 pos_x_end;
    fix16 pos_y_end;
    bool in_going;
    bool direction;
    ENEMY_update_funcao ENEMY_update;
};

Enemy* ENEMY_init(u16* ind, f16 x, f16 y, TYPE enemy, f16 x_end, f16 y_end, bool direc, u8 anim, const SpriteDefinition* spr);
void ENEMY_free(Enemy* e);
void PATROL_update(Enemy* e, Character* p);
void FIXED_update(Enemy* e, Character* p);

#endif