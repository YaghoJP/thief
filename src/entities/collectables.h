#ifndef _COLLECTABLES_H_
#define _COLLECTABLES_H_

#include "base/character.h"

typedef struct{
    Character* ch;
    u8 value;
    bool key;
}Collectable;

Collectable* COLLECTABLE_init(u16* ind, f16 x, f16 y, const SpriteDefinition* spr);
void COLLECTABLE_free(Collectable* c);

#endif