#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "node.h"
#include "singletons/game_manager.h"

#define CHARACTER_SPRITE_W 32
#define CHARACTER_SPRITE_H 32
#define CHARACTER_SPEED (F16_mul(F16(0.8), F16(1.1)))

typedef struct Character Character;
typedef void (*CHARACTER_take_damage)(Character* p);

typedef struct {
    fix16 x;
    fix16 y;
}Velocity;

struct Character{
    Velocity vel;
    Node* no;
    u8 anim_sprite;
    u8 health;
    CHARACTER_take_damage take_damage;
};

Character* CHARACTER_init(u16* ind, f16 x, f16 y, u8 pal, const SpriteDefinition* spr);
void CHARACTER_free(Character *c);

void CHARACTER_hud_update(Character* c, bool is_key);
#endif