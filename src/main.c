#include "scene/scene.h"

int main(bool HardReset)
{
    if (!HardReset) 
    {
        SYS_hardReset();
    }

    SCENE_load(SCREEN_START);

    if(!signal_player_is_dead && !signal_game_over)
        SCENE_load(LEVEL_1);
    if(!signal_player_is_dead && !signal_game_over)
        SCENE_load(LEVEL_2);
    if(!signal_player_is_dead && !signal_game_over)
        SCENE_load(LEVEL_3);
    if(!signal_player_is_dead && !signal_game_over)
        SCENE_load(LEVEL_4);
    if(!signal_player_is_dead && !signal_game_over)
        SCENE_load(LEVEL_5);
    if(!signal_player_is_dead && !signal_game_over)
        SCENE_load(SCREEN_VICTORY);
    if(signal_game_over)
        SCENE_load(SCREEN_GAME_OVER);
    return 0;
}