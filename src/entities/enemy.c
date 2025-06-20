#include "enemy.h"

bool ENEMY_check_player_collision(Enemy *e, Character* p);

void ENEMY_attack(Character* p);

Enemy* ENEMY_init(u16* ind, f16 x, f16 y, TYPE enemy, f16 x_end, f16 y_end, bool direc, u8 anim, const SpriteDefinition* spr)
{
    Enemy* e = MEM_alloc(sizeof(Enemy));
    e->ch = CHARACTER_init(ind, x, y, PAL_ENEMY,spr);
    e->type_enemy = enemy;
    e->pos_x_start = e->ch->no->x;
    e->pos_y_start = e->ch->no->y;
    e->pos_x_end = x_end;
    e->pos_y_end = y_end;
    e->ch->vel.x = 0;
    e->ch->vel.y = 0;
    e->ch->anim_sprite = anim;
    e->in_going = TRUE;
    e->direction = direc;

    switch (enemy)
    {
    case PATROL:
        e->ENEMY_update = PATROL_update;
        break;
    case FIXED:
        e->ENEMY_update = FIXED_update;
        break;
    default:
        break;
    }

    SPR_setAnim(e->ch->no->sprite, e->ch->anim_sprite);
    return e;
}

void PATROL_update(Enemy* e, Character* p)
{   

    if(e->direction)
    {
        if(e->in_going)
        {
            if(F16_toInt(e->ch->no->x) < e->pos_x_end)
            {
                if(ENEMY_check_player_collision(e, p)) ENEMY_attack(p);
                else e->ch->no->x += F16_mul(CHARACTER_SPEED, F16(0.8));
            }else
            {
                e->ch->anim_sprite -= 1;
                e->in_going = FALSE;
            }
        }
        if(!e->in_going)
        {
            if(e->ch->no->x >= e->pos_x_start)
            {
                if(ENEMY_check_player_collision(e, p)) ENEMY_attack(p);
                else e->ch->no->x -= F16_mul(CHARACTER_SPEED, F16(0.8));
            }else
            {
                e->ch->anim_sprite += 1;
                e->in_going = TRUE;
            }
        }
    }else
    {
        if(e->in_going)
        {
            if(F16_toInt(e->ch->no->y) < e->pos_y_end)
            {
                if(ENEMY_check_player_collision(e, p)) ENEMY_attack(p);
                else e->ch->no->y += F16_mul(CHARACTER_SPEED, F16(0.8));

            }else
            {
                e->ch->anim_sprite -= 1;
                e->in_going = FALSE;
            }
        }
        if(!e->in_going)
        {
            if(e->ch->no->y >= e->pos_y_start)
            {
                if(ENEMY_check_player_collision(e, p)) ENEMY_attack(p);
                else e->ch->no->y -= F16_mul(CHARACTER_SPEED, F16(0.8));
            }else
            {
                e->ch->anim_sprite += 1;
                e->in_going = TRUE;
            }
        }
    }
    
    SPR_setPosition(e->ch->no->sprite, F16_toInt(e->ch->no->x), F16_toInt(e->ch->no->y));
    SPR_setAnim(e->ch->no->sprite, e->ch->anim_sprite);
}

void FIXED_update(Enemy* e, Character* p);


bool ENEMY_check_player_collision(Enemy *e, Character* p)
{
    s16 px = F16_toInt(p->no->x);
    s16 py = F16_toInt(p->no->y);

    s16 ex = F16_toInt(e->ch->no->x);
    s16 ey = F16_toInt(e->ch->no->y);
    
    // Box do player
    s16 p_left   = px;
    s16 p_right  = px + 16;
    s16 p_top    = py;
    s16 p_bottom = py + 16;

    // Box do inimigo
    s16 e_left   = ex;
    s16 e_right  = ex + 16;
    s16 e_top    = ey;
    s16 e_bottom = ey + 16;

    
    bool isColliding = !(p_right < e_left || p_left > e_right || p_bottom < e_top || p_top > e_bottom);

    if (isColliding) {
        return TRUE;  
    }

    return FALSE;
}

void ENEMY_attack(Character* p)
{
    p->take_damage(p);
}

void ENEMY_free(Enemy* e){
    CHARACTER_free(e->ch);
    MEM_free(e);
}