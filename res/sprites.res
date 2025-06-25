##-----------------BACKGROUND'S-----------------
IMAGE bg "sprites/bg/bg.png" BEST

#-----------------MAP'S-----------------
TILESET ts_level_1 "sprites/level_1/level_1.png" BEST ALL
MAP map_level_1 "sprites/level_1/level_1.png" ts_level_1 BEST 0
PALETTE pal_level_1 "sprites/level_1/level_1.png"

TILESET ts_level_2 "sprites/level_2/level_2_map.png" BEST ALL
MAP map_level_2 "sprites/level_2/level_2_map.png" ts_level_2 BEST 0
PALETTE pal_level_2 "sprites/level_2/level_2_map.png"

TILESET ts_level_3 "sprites/level_3/level_3_map.png" BEST ALL
MAP map_level_3 "sprites/level_3/level_3_map.png" ts_level_3 BEST 0
PALETTE pal_level_3 "sprites/level_3/level_3_map.png"

TILESET ts_level_4 "sprites/level_4/level_4_map.png" BEST ALL
MAP map_level_4 "sprites/level_4/level_4_map.png" ts_level_4 BEST 0
PALETTE pal_level_4 "sprites/level_4/level_4_map.png"

TILESET ts_level_5 "sprites/level_5/level_5_map.png" BEST ALL
MAP map_level_5 "sprites/level_5/level_5_map.png" ts_level_5 BEST 0
PALETTE pal_level_5 "sprites/level_5/level_5_map.png"

#-----------------Collectables-----------------
SPRITE spr_diamond "sprites/collectables/diamond.png" 2 2 FAST 10
SPRITE spr_key "sprites/collectables/key.png" 2 2 FAST 10
SPRITE spr_chest "sprites/collectables/chest.png" 2 2 FAST 0


#-----------------PLAYERS-----------------
SPRITE spr_thief "sprites/player/thief.png" 2 2 FAST 8


#-----------------Enemies-----------------
SPRITE spr_enemy_patrol_green "sprites/enemy/patrol_green.png" 4 4 FAST 10
SPRITE spr_enemy_patrol_red "sprites/enemy/patrol_red.png" 2 2 FAST 8
SPRITE spr_enemy_fixed_gray "sprites/enemy/fixed_gray.png" 2 2 FAST 0
SPRITE spr_fireball "sprites/enemy/fireball.png" 2 2 FAST 0

#-----------------Screens-----------------
IMAGE start_screen "sprites/level_0/start.png" BEST
IMAGE credits_screen "sprites/level_0/screen_credists.png" BEST
IMAGE game_over_screen "sprites/level_0/game_over.png" BEST
IMAGE victory_screen "sprites/level_0/victory.png" BEST

#-----------------HUD-----------------
SPRITE hud_diamond "sprites/hud/diamond_hud.png" 1 1 FAST 8
SPRITE hud_key "sprites/hud/key_hud.png" 1 1 FAST 0
SPRITE hud_life "sprites/hud/life.png" 1 1 FAST 0
