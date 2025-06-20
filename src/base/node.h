#ifndef _NODE_H_
#define _NODE_H_

#include <genesis.h>
#include "singletons/game_manager.h"

typedef struct {
	s16 left;
	s16 right;
	s16 top;
	s16 bottom;
} BoundBox;

typedef struct {
	Sprite* sprite;
	fix16 x;
	fix16 y;
} Node;

Node* NODE_init(const SpriteDefinition* const sprite, s16 x, s16 y, u8 pal, u16* ind);

#endif