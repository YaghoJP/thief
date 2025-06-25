#ifndef _BULLET_H_
#define _BULLET_H_

#include "base/character.h"
#include "level/level.h"

#define BULLET_OFFSET_LEFT 4
#define BULLET_OFFSET_RIGHT 13
#define BULLET_OFFSET_UP 5
#define BULLET_OFFSET_DOWN 11

typedef struct {
    Character* ch;
    f16 pos_x_start;
    f16 pos_y_start;
} Bullet;

Bullet* BULLET_init(u16* ind, f16 x, f16 y, const SpriteDefinition* spr, u8 anim);
void BULLET_update(Bullet *fb, Level *l, Character* c);
bool BULLET_check_level_collision(Bullet* b, Level* l);
bool BULLET_check_player_collision(Bullet * fb, Character* p);
void BULLET_free(Bullet* b);
#endif