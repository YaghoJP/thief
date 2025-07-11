#include "game_manager.h"

u16 score = 0;
u16 life = 0;

bool signal_game_started = FALSE;
bool signal_game_over = FALSE;
bool signal_player_is_dead = FALSE;
bool signal_key_collected = FALSE;
bool signal_game_won = FALSE;

void GAME_MANAGER_play_music()
{
    XGM_startPlay(music);
    XGM_setLoopNumber(-1);
}