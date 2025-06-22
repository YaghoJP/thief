#include "scene/scene.h"

int main()
{

    SCENE_load(SCREEN_START);

    if(!signal_player_is_dead && !signal_game_over && signal_game_started)
        SCENE_load(LEVEL_1);

    if(signal_game_over)
    {
        SCENE_load(SCREEN_GAME_OVER);
    }
    return 0;
}