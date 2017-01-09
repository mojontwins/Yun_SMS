// MT MK1 SMS version 0.1 [Yun]
// Copyleft 2016 The Mojon Twins

// Map and map-related functions

#ifndef __MAP_H
#define __MAP_H

void map_prepare (void);
void map_scr_prepare (void);
void map_screen_update (void);
unsigned char map_real_y (unsigned char y);
void map_set (unsigned char x, unsigned char y, unsigned char t);
void map_scr_clear (void);
const unsigned char *map_tile (unsigned char x, unsigned char y);
void map_scr_draw_box (void);
void map_scr_draw_from_right (void);
void map_scr_draw_from_left (void);
void map_scr_draw_from_down (void);
void map_scr_draw_from_up (void);

#endif
