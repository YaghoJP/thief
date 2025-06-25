#ifndef _SCENE_H_
#define _SCENE_H_

#include "singletons/game_manager.h"
#include "background/background.h"
#include "level/level.h"
#include "entities/player.h"
#include "entities/enemy.h"
#include "entities/bullet.h"
#include "sprites.h"

void SCENE_init();
void SCENE_load(u8 scene);
void SCENE_unload();

extern bool game_over;

#endif