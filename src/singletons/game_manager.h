#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <genesis.h>
#include "sprite_eng.h"

//globals
extern u16 score;

//Signals
extern bool signal_game_started;
extern bool signal_game_over;
extern bool signal_player_is_dead;
extern bool signal_key_collected;
extern bool signal_game_won;

//Levels
#define SCREEN_START 0
#define SCREEN_CREDITS 10
#define SCREEN_GAME_OVER 11
#define LEVEL_1 1
#define LEVEL_2 2
#define LEVEL_3 3
#define LEVEL_4 4
#define LEVEL_5 5

//Game Config
#define SCREEN_W 320
#define SCREEN_H 224

#define PAL_PLAYER 		PAL0
#define PAL_ENEMY 		PAL1
#define PAL_MAP 		PAL2
#define PAL_BACKGROUND 	PAL3

#define BG_BACKGROUND BG_B
#define BG_MAP        BG_A

#define SCREEN_TILES_W SCREEN_W/8
#define SCREEN_TILES_H SCREEN_H/8

#define WALL 2
#define DIAMONDS 5
#define KEY 6
#define START_TILE 4

#endif