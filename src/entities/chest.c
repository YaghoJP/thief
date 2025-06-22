#include "chest.h"

Chest* CHEST_init(u16* ind, f16 x, f16 y, const SpriteDefinition* spr){
    Chest* c = MEM_alloc(sizeof(Chest));
    c->ch = CHARACTER_init(ind, x, y, PAL_ENEMY, spr);
    c->key_droped = FALSE;
    SPR_setAnim(c->ch->no->sprite, 0);
    return c;
}

void CHEST_free(Chest* c)
{
    if(c)
    {
        CHARACTER_free(c->ch);
        MEM_free(c);
    }
}
