#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "base/character.h"
#include "level/level.h"
#include "singletons/game_manager.h"
#include "enemy.h"

#define ANIM_RIGTH 4
#define ANIM_LEFT 3
#define ANIM_UP 2
#define ANIM_DOWN 1

#define PLAYER_W 16
#define PLAYER_H 16

#define PLAYER_OFFSET_LEFT 1
#define PLAYER_OFFSET_RIGHT 15
#define PLAYER_OFFSET_UP 1
#define PLAYER_OFFSET_DOWN 14

typedef struct {
    Character* ch; 
} Player;

bool PLAYER_input(Player *p);
Player* PLAYER_init(u16* ind, f16 x, f16 y, const SpriteDefinition* spr);
void PLAYER_free(Player* p);
void PLAYER_update(Player *p, Level *l);
void PLAYER_check_collision(Player *p, Level *l);
bool PLAYER_check_end_level(Player *p);
void PLAYER_take_damage(Character* c);

#endif