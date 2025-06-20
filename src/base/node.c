#include "node.h"

Node* NODE_init(const SpriteDefinition* const sprite, s16 x, s16 y, u8 pal, u16* ind) 
{
	Node *no = MEM_alloc(sizeof(Node));
	no->x = FIX16(x);
	no->y = FIX16(y);
	PAL_setPalette(pal, sprite->palette->data, DMA);
	no->sprite = SPR_addSprite(sprite, x, y, TILE_ATTR_FULL(pal, FALSE, FALSE, 0, *ind));	
	*ind += no->sprite->definition->maxNumTile;
	return no;
}