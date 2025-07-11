#include "collectables.h"

Collectable* COLLECTABLE_init(u16* ind, f16 x, f16 y, const SpriteDefinition* spr, bool lifeadd){
    Collectable* c = MEM_alloc(sizeof(Collectable));

    if(lifeadd) c->ch = CHARACTER_init(ind, x, y, PAL_ENEMY, spr);
    else c->ch = CHARACTER_init(ind, x, y, PAL_PLAYER, spr);
    c->value = 1;
    SPR_setAnim(c->ch->no->sprite, 0);
    c->is_active = TRUE;
    c->is_heart = lifeadd;
    return c;
}

void COLLECTABLE_free(Collectable* c)
{
    if(c)
    {
        CHARACTER_free(c->ch);
        MEM_free(c);
    }
}
