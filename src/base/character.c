#include "character.h"

Character* CHARACTER_init(u16* ind, f16 x, f16 y, u8 pal, const SpriteDefinition* spr)
{
    Character* c = MEM_alloc(sizeof(Character));
    c->no = NODE_init(spr, x, y, pal, ind);
    c->health = 0;
    c->vel.x = 0;
    c->vel.y = 0;
    return c;
}

void CHARACTER_free(Character *c)
{
    if (c) {
        SPR_releaseSprite(c->no->sprite);
        MEM_free(c->no);
        MEM_free(c);
    }
}