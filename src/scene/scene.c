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

    signal_game_started = FALSE;
    signal_game_over = FALSE;
    signal_player_is_dead = FALSE;
    signal_key_collected = FALSE;
    signal_game_won = FALSE;
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
    case SCREEN_CREDITS:
        SCENE_screen_credits();
        break;
    case SCREEN_GAME_OVER:
        SCENE_screen_game_over();
        break;
    default:
        break;
    }
}

void SCENE_screen_game_over()
{
    u16 VRAM_tile_index = TILE_USER_INDEX;

    BACKGROUND_init(&VRAM_tile_index, &game_over_screen);

    SYS_doVBlankProcess();

    while(TRUE)
    {
        u16 button = JOY_readJoypad(JOY_1);
    
        if(button & BUTTON_START){
            break;
        }

        SPR_update();
        SYS_doVBlankProcess();
    }
    SCENE_load(SCREEN_START);
}

void SCENE_screen_credits()
{

    u16 VRAM_tile_index = TILE_USER_INDEX;

    BACKGROUND_init(&VRAM_tile_index, &credits_screen);

    SYS_doVBlankProcess();

    while(TRUE)
    {
        u16 button = JOY_readJoypad(JOY_1);
    
        if(button & BUTTON_START){
            break;
        }

        SPR_update();
        SYS_doVBlankProcess();
    }
    SCENE_load(SCREEN_START);
}

void SCENE_screen_start()
{
    u16 VRAM_tile_index = TILE_USER_INDEX;

    BACKGROUND_init(&VRAM_tile_index, &start_screen);

    s8 button_select = 0;
    Character *diamond = MEM_alloc(sizeof(Character));
    diamond = CHARACTER_init(&VRAM_tile_index, 86, 130, PAL_PLAYER, &spr_diamond);

    SPR_setAnimationLoop(diamond->no->sprite, TRUE);

    SYS_doVBlankProcess();

    while(!signal_game_started)
    {
        u16 button = JOY_readJoypad(JOY_1);
    
        if(button & BUTTON_DOWN)
        {
            button_select = 1;
            SPR_setPosition(diamond->no->sprite, F16_toInt(diamond->no->x), 165);
        }

        if(button & BUTTON_UP)
        {
            button_select = 0;
            SPR_setPosition(diamond->no->sprite, F16_toInt(diamond->no->x), 130);
        }

        if(button & BUTTON_START){
            if (button_select == 1) SCENE_load(SCREEN_CREDITS);
            else signal_game_started = TRUE;
        }

        SPR_update();
        SYS_doVBlankProcess();
    }

    CHARACTER_free(diamond);
}

void SCENE_level_1()
{
    u16 vRAM_tile_user_index = TILE_USER_INDEX;
    
    Level* level = LEVEL_init(&vRAM_tile_user_index, &map_level_1, &ts_level_1, &pal_level_1, 1);

    BACKGROUND_init(&vRAM_tile_user_index, &bg);


    Player* p = PLAYER_init(&vRAM_tile_user_index, SCREEN_W-60, SCREEN_H-50, &spr_thief);

    Enemy* e = ENEMY_init(&vRAM_tile_user_index, 150, 18, PATROL, 280, 18, TRUE, 4, &spr_enemy_patrol_red);
    Enemy* e1 = ENEMY_init(&vRAM_tile_user_index, 150, 40, PATROL, 220, 40, TRUE, 4, &spr_enemy_patrol_red);
    
    Enemy* e2 = ENEMY_init(&vRAM_tile_user_index, 144, 90, PATROL, 230, 90, TRUE, 4, &spr_enemy_patrol_red);
    Enemy* e3 = ENEMY_init(&vRAM_tile_user_index, 160, 110, PATROL, 260, 110, TRUE, 4, &spr_enemy_patrol_red);

    Enemy* e4 = ENEMY_init(&vRAM_tile_user_index, 80, 32, PATROL, 80, 140, FALSE, 1, &spr_enemy_patrol_red);


    char gems[5];
    while(!signal_game_over && !signal_game_won){

        VDP_drawText("Score: ", 26, 1);
	    intToStr(score, gems, 3);
        VDP_drawText(gems, 33, 1);

        PLAYER_update(p, level);
        e->ENEMY_update(e, p->ch);
        e1->ENEMY_update(e1, p->ch);
        e2->ENEMY_update(e2, p->ch);
        e3->ENEMY_update(e3, p->ch);
        e4->ENEMY_update(e4, p->ch);
        SPR_update();
        SYS_doVBlankProcess();
    }


    PLAYER_free(p);
    ENEMY_free(e);
    ENEMY_free(e1);
    ENEMY_free(e2);
    ENEMY_free(e3);
    ENEMY_free(e4);

    LEVEL_free(level);
}