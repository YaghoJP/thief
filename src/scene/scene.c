#include "scene.h"

//Scenes
void SCENE_screen_start();
void SCENE_screen_game_over();
void SCENE_screen_credits();
void SCENE_level_1();

void SCENE_init()
{
    SYS_disableInts();
    SYS_showFrameLoad(true);
    SPR_init();
    
    SYS_enableInts();
    
    VDP_setScreenHeight224();
    VDP_setScreenWidth320();
    VDP_clearPlane(BG_BACKGROUND, TRUE);
    VDP_clearPlane(BG_MAP, TRUE);
    
    SYS_doVBlankProcess();
}

void SCENE_unload()
{
    SPR_reset();
    VDP_clearTextArea(0, 0, 40, 28);
    VDP_clearPlane(BG_A, TRUE);
    VDP_clearPlane(BG_B, TRUE);
    SYS_doVBlankProcess();

    signal_game_over = FALSE;
    signal_game_started = FALSE;
    signal_player_is_dead = FALSE;
}

void SCENE_load(u8 scene)
{
    SCENE_unload();
    SCENE_init();

    switch (scene)
    {
    case SCREEN_START:
        SCENE_screen_start();
        break;
    case LEVEL_1:
        SCENE_level_1();
        break;
    case LEVEL_2:
        SCENE_level_2();
        break;
    case LEVEL_3:
        SCENE_level_3();
        break;
    case SCREEN_GAME_OVER:
        SCENE_screen_game_over();
        break;
    default:
        break;
    }
}

void SCENE_screen_start()
{
   // u16 vRAM_tile_user_index = TILE_USER_INDEX;


}

void SCENE_level_1()
{
    u16 vRAM_tile_user_index = TILE_USER_INDEX;
    
    Level* level = LEVEL_init(&vRAM_tile_user_index, &map_level_1, &ts_level_1, &pal_level_1, 1);

    BACKGROUND_init(&vRAM_tile_user_index, &bg);


    Player* p = PLAYER_init(&vRAM_tile_user_index, SCREEN_W-60, SCREEN_H-50, &spr_thief);

    Enemy* e = ENEMY_init(&vRAM_tile_user_index, 150, 18, PATROL, 220, 18, TRUE, 4, &spr_enemy_patrol_red);
    Enemy* e1 = ENEMY_init(&vRAM_tile_user_index, 144, 90, PATROL, 190, 50, TRUE, 4, &spr_enemy_patrol_red);

    while(!signal_game_over && !signal_game_won){

        PLAYER_update(p, level);
        e->ENEMY_update(e, p->ch);
        e1->ENEMY_update(e1, p->ch);
        SPR_update();
        SYS_doVBlankProcess();
    }
}