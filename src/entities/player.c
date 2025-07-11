#include "player.h"

Player* PLAYER_init(u16* ind, f16 x, f16 y, const SpriteDefinition* spr)
{
    Player* p = MEM_alloc(sizeof(Player));
    p->ch = CHARACTER_init(ind, x, y, PAL_PLAYER, spr);
    p->ch->anim_sprite = 0;
    p->ch->take_damage = PLAYER_take_damage;
    p->ch->health = 1;
    SPR_setAnim(p->ch->no->sprite, p->ch->anim_sprite);

    return p;
}
void PLAYER_free(Player* p){
    if(p)
    {
        CHARACTER_free(p->ch);
        MEM_free(p);
    }
}

bool PLAYER_input(Player *p) 
{

    u16 button = JOY_readJoypad(JOY_1);

    if (button & BUTTON_RIGHT) 
    {
        p->ch->vel.x =  CHARACTER_SPEED + F16(0.3);
        p->ch->anim_sprite = ANIM_RIGTH;
        return TRUE;
    }
    if (button & BUTTON_LEFT) 
    {
        p->ch->vel.x = - CHARACTER_SPEED - F16(0.3);
        p->ch->anim_sprite = ANIM_LEFT;
        return TRUE;
    }
    if (button & BUTTON_DOWN) 
    {
        p->ch->vel.y =  CHARACTER_SPEED + F16(0.3);
        p->ch->anim_sprite = ANIM_DOWN;
        return TRUE;
    }
    if (button & BUTTON_UP) 
    {
        p->ch->vel.y  = - CHARACTER_SPEED - F16(0.3);
        p->ch->anim_sprite = ANIM_UP;
        return TRUE;
    }

    p->ch->anim_sprite = 0;
    SPR_setAnim(p->ch->no->sprite, p->ch->anim_sprite);
    return FALSE;
}

void PLAYER_update(Player * p, Level *l)
{
    if (p->ch->health == 0) return;

    p->ch->vel.x = 0;
    p->ch->vel.y = 0;

    if (PLAYER_input(p)) 
    {

        PLAYER_check_collision(p, l);
        if(PLAYER_check_end_level(p))
            signal_game_won = TRUE;

        p->ch->no->x = p->ch->no->x + p->ch->vel.x;
        p->ch->no->y = p->ch->no->y + p->ch->vel.y;

        SPR_setPosition(p->ch->no->sprite, F16_toInt(p->ch->no->x), F16_toInt(p->ch->no->y));
        SPR_setAnim(p->ch->no->sprite, p->ch->anim_sprite);
    }
    
}

bool PLAYER_check_end_level(Player *p)
{
    if(signal_key_collected && F16_toInt(p->ch->no->y) == -18)
    {
        kprintf("OI");
        return(TRUE);   
    }
    if(!signal_key_collected && F16_toInt(p->ch->no->y) == -18) 
    {
        p->ch->vel.y = F16(18);
    }
    if(F16_toInt(p->ch->no->y) >= 221) 
    {
        p->ch->vel.y = - F16(18);
    }
    return FALSE;
}

void PLAYER_check_collision(Player *p, Level *l)
{

    s16 pos_x = F16_toInt(p->ch->vel.x + p->ch->no->x);
    s16 pos_y = F16_toInt(p->ch->vel.y + p->ch->no->y);

    s16 coord_left = pos_x + PLAYER_OFFSET_LEFT;
    s16 coord_right = pos_x + PLAYER_OFFSET_RIGHT;
    s16 coord_up = pos_y + PLAYER_OFFSET_UP;
    s16 coord_down = pos_y + PLAYER_OFFSET_DOWN;

    s16 xtile_left = coord_left >> 4;
    s16 xtile_right = coord_right >> 4;
    s16 ytile_up = coord_up >> 4;
    s16 ytile_down = coord_down >> 4;

    bool collision_left = false;
    for (int y = ytile_up; y <= ytile_down; y++) 
    {
        if (l->collision_data[y * COLLISION_COLUMN + xtile_left] == WALL )//|| l->collision_data[y * COLLISION_COLUMN + xtile_left] == START_TILE) 
        {
            collision_left = true;
            break;
        }
        if (l->collision_data[y * COLLISION_COLUMN + xtile_left] == DIAMONDS || l->collision_data[y * COLLISION_COLUMN + xtile_left] == HEART)
        {
            LEVEL_collect(xtile_left, y, l->c, l->qt_collectables);
            break;
        }
        if (l->collision_data[y * COLLISION_COLUMN + xtile_left] == KEY)
        {
            LEVEL_key_collect(l->chest_key);
            break;
        }
    }

    bool collision_right = false;
    for (int y = ytile_up; y <= ytile_down; y++) {
        if (l->collision_data[y * COLLISION_COLUMN + xtile_right] == WALL )//|| l->collision_data[y * COLLISION_COLUMN + xtile_right] == START_TILE) 
        {
            collision_right = true;
            break;
        }
        if (l->collision_data[y * COLLISION_COLUMN + xtile_right] == DIAMONDS || l->collision_data[y * COLLISION_COLUMN + xtile_right] == HEART)
        {
            LEVEL_collect(xtile_right, y, l->c, l->qt_collectables);
            break;
        }
        if (l->collision_data[y * COLLISION_COLUMN + xtile_right] == KEY)
        {
            LEVEL_key_collect(l->chest_key);
            break;
        }
    }

    bool collision_up = false;
    for (int x = xtile_left; x <= xtile_right; x++) 
    {
        if (l->collision_data[ytile_up * COLLISION_COLUMN + x] == WALL )//|| l->collision_data[ytile_up * COLLISION_COLUMN + x] == START_TILE) 
        {
            collision_up = true;
            break;
        }

        if (l->collision_data[ytile_up * COLLISION_COLUMN + x] == DIAMONDS || l->collision_data[ytile_up * COLLISION_COLUMN + x] == HEART)
        {
            LEVEL_collect(x, ytile_up, l->c, l->qt_collectables);
            break;
        }

        if (l->collision_data[ytile_up * COLLISION_COLUMN + x] == KEY)
        {
            LEVEL_key_collect(l->chest_key);
            break;
        }
    }

    bool collision_down = false;
    for (int x = xtile_left; x <= xtile_right; x++) 
    {
        if (l->collision_data[ytile_down * COLLISION_COLUMN + x] == WALL )//|| l->collision_data[ytile_down * COLLISION_COLUMN + x] == START_TILE) 
        {
            collision_down = true;
            break;
        }

        if(l->collision_data[ytile_down * COLLISION_COLUMN + x] == DIAMONDS || l->collision_data[ytile_down * COLLISION_COLUMN + x] == HEART)
        {
            LEVEL_collect(x, ytile_down, l->c, l->qt_collectables);
            break;
        }

        if(l->collision_data[ytile_down * COLLISION_COLUMN + x] == KEY)
        {
            LEVEL_key_collect(l->chest_key);
            break;
        }
    }

    if(collision_left || collision_right)
    {
        p->ch->vel.x = 0;
    }
    if(collision_up || collision_down)
    {
        p->ch->vel.y = 0;
    }
}

void PLAYER_take_damage(Character* c)
{
    life--;
    if (life <= 0)
    {
        c->health = 0;
        signal_game_over = TRUE;
        signal_player_is_dead = TRUE;
    }
}
