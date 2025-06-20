#include "background.h"

void BACKGROUND_init(u16* ind, const Image* bg_img)
{
    PAL_setPalette(PAL_BACKGROUND, bg_img->palette->data, DMA);
    VDP_drawImageEx(BG_BACKGROUND, bg_img, TILE_ATTR_FULL(PAL_BACKGROUND, FALSE, FALSE, FALSE, *ind), FALSE, FALSE, FALSE, TRUE);
    *ind = *ind + bg_img->tileset->numTile;
}