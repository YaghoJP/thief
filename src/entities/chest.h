#ifndef _CHEST_H_
#define _CHEST_H_

#include "base/character.h"
#include "collectables.h"

typedef struct{
    Character* ch;
    bool key_droped;
}Chest;

Chest* CHEST_init(u16* ind, f16 x, f16 y, const SpriteDefinition* spr);
void CHEST_free(Chest* c);

#endif