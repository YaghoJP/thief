#ifndef _COLLECTABLES_H_
#define _COLLECTABLES_H_

#include "base/character.h"

typedef struct{
    Character* ch;
    u8 value;
    bool key;
    bool is_active;
    bool is_heart;
}Collectable;

Collectable* COLLECTABLE_init(u16* ind, f16 x, f16 y, const SpriteDefinition* spr, bool lifeadd);
void COLLECTABLE_free(Collectable* c);

#endif