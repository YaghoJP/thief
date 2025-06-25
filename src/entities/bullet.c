#include "bullet.h"

Bullet* BULLET_init(u16* ind, f16 x, f16 y, const SpriteDefinition* spr, u8 anim)
{
    Bullet* b = MEM_alloc(sizeof(Bullet));
    b->ch = CHARACTER_init(ind, x, y, PAL_ENEMY, spr);
    b->ch->anim_sprite = anim;
    b->pos_x_start = F16(x);
    b->pos_y_start = F16(y);
    SPR_setAnim(b->ch->no->sprite, b->ch->anim_sprite);

    return b;
}

void BULLET_free(Bullet* b)
{
    if(b)
    {
        CHARACTER_free(b->ch);
        MEM_free(b);
    }
}

bool BULLET_check_level_collision(Bullet* b, Level* l)
{

    s16 pos_x = F16_toInt(b->ch->vel.x + b->ch->no->x);
    s16 pos_y = F16_toInt(b->ch->vel.y + b->ch->no->y);

    s16 coord_left = pos_x + BULLET_OFFSET_LEFT;
    s16 coord_right = pos_x + BULLET_OFFSET_RIGHT;
    s16 coord_up = pos_y + BULLET_OFFSET_UP;
    s16 coord_down = pos_y + BULLET_OFFSET_DOWN;

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
    }

    bool collision_right = false;
    for (int y = ytile_up; y <= ytile_down; y++) {
        if (l->collision_data[y * COLLISION_COLUMN + xtile_right] == WALL )//|| l->collision_data[y * COLLISION_COLUMN + xtile_right] == START_TILE) 
        {
            collision_right = true;
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
    }

    bool collision_down = false;
    for (int x = xtile_left; x <= xtile_right; x++) 
    {
        if (l->collision_data[ytile_down * COLLISION_COLUMN + x] == WALL )//|| l->collision_data[ytile_down * COLLISION_COLUMN + x] == START_TILE) 
        {
            collision_down = true;
            break;
        }
    }

    if(collision_left || collision_right)
    {
        return TRUE;
    }
    if(collision_up || collision_down)
    {
        return TRUE;
    }
    return FALSE;
}

bool BULLET_check_player_collision(Bullet* fb, Character* p)
{
    s16 px = F16_toInt(p->no->x);
    s16 py = F16_toInt(p->no->y);
    s16 ex = F16_toInt(fb->ch->no->x);
    s16 ey = F16_toInt(fb->ch->no->y);
    
    // Box do player
    s16 p_left   = px + 2;
    s16 p_right  = px + 14;
    s16 p_top    = py + 2;
    s16 p_bottom = py + 14;

    // Box do inimigo
    s16 e_left   = ex + 2;
    s16 e_right  = ex + 14;
    s16 e_top    = ey + 2;
    s16 e_bottom = ey + 14;

    
    bool isColliding = !(p_right < e_left || p_left > e_right || p_bottom < e_top || p_top > e_bottom);

    if (isColliding) {
        return TRUE;  
    }

    return FALSE;
}

void BULLET_update(Bullet *fb, Level *l, Character* c)
{
    if(BULLET_check_player_collision(fb, c))
    {
        c->take_damage(c);
    }
    if(BULLET_check_level_collision(fb, l))
    {
        fb->ch->no->x = fb->pos_x_start;
        fb->ch->no->y = fb->pos_y_start;
    }else
    {
        if(fb->ch->anim_sprite == 0) fb->ch->vel.y = -F16(1.5);
        if(fb->ch->anim_sprite == 1) fb->ch->vel.x = -F16(1.5);
        if(fb->ch->anim_sprite == 2) fb->ch->vel.y = +F16(1.5);
        if(fb->ch->anim_sprite == 3) fb->ch->vel.x = +F16(1.5);

        fb->ch->no->x = fb->ch->no->x + fb->ch->vel.x;
        fb->ch->no->y = fb->ch->no->y + fb->ch->vel.y;
    }

    SPR_setPosition(fb->ch->no->sprite, F16_toInt(fb->ch->no->x), F16_toInt(fb->ch->no->y));
}