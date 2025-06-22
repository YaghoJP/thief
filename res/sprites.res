##-----------------BACKGROUND'S-----------------
IMAGE bg "sprites/bg/bg.png" BEST

#-----------------MAP'S-----------------
TILESET ts_level_1 "sprites/level_1/level_1.png" BEST ALL
MAP map_level_1 "sprites/level_1/level_1.png" ts_level_1 BEST 0
PALETTE pal_level_1 "sprites/level_1/level_1.png"

#-----------------Collectables-----------------
SPRITE spr_diamond "sprites/collectables/diamond.png" 2 2 FAST 10
SPRITE spr_key "sprites/collectables/key.png" 2 2 FAST 10
SPRITE spr_chest "sprites/collectables/chest.png" 2 2 FAST 0


#-----------------PLAYERS-----------------
SPRITE spr_thief "sprites/player/thief.png" 2 2 FAST 8


#-----------------Enemies-----------------
SPRITE spr_enemy_patrol_green "sprites/enemy/patrol_green.png" 4 4 FAST 10
SPRITE spr_enemy_patrol_red "sprites/enemy/patrol_red.png" 2 2 FAST 8

#-----------------Screens-----------------
IMAGE start_screen "sprites/level_0/start.png" BEST
IMAGE credits_screen "sprites/level_0/screen_credists.png" BEST
IMAGE game_over_screen "sprites/level_0/game_over.png" BEST