// MT MK1 SMS version 0.1 [Yun]
// Copyleft 2016 The Mojon Twins

// Printer. Auxiliary printing functions

#include "../lib/SMSlib.h"

#include "../definitions.h"
#include "printer.h"

extern unsigned char rda;
extern unsigned char frame_counter;
extern const unsigned char pal_cycle_desert [];
extern const unsigned char pal_cycle_waterfall [];
extern const unsigned char work_level1_conveyor_left_bin [];
extern const unsigned char work_level1_conveyor_right_bin [];
extern unsigned char anim_tile_conveyor_offs;

void sprites_out (void) {
	SMS_MT_initSpritesEx (7); 	// Sprites 0-6 are reserved for the hud.
	SMS_MT_finalizeSpritesEx ();
	SMS_waitForVBlank ();
	SMS_copySpritestoSAT ();
}

inline void pal_cycle_desert_do (void) {
	rda = (frame_counter >> 4) & 3;	// Offset
	SMS_setBGPaletteColor (11 + rda, pal_cycle_desert [0]); rda ++; rda &= 3;
	SMS_setBGPaletteColor (11 + rda, pal_cycle_desert [1]); rda ++; rda &= 3;
	SMS_setBGPaletteColor (11 + rda, pal_cycle_desert [2]); rda ++; rda &= 3;
	SMS_setBGPaletteColor (11 + rda, pal_cycle_desert [3]); rda ++; rda &= 3;
}

inline void pal_cycle_waterfall_do (void) {
	rda = (frame_counter >> 2) & 7;	// Offset
	SMS_setBGPaletteColor (8 + rda, pal_cycle_waterfall [0]); rda ++; rda &= 7;
	SMS_setBGPaletteColor (8 + rda, pal_cycle_waterfall [1]); rda ++; rda &= 7;
	SMS_setBGPaletteColor (8 + rda, pal_cycle_waterfall [2]); rda ++; rda &= 7;
	SMS_setBGPaletteColor (8 + rda, pal_cycle_waterfall [3]); rda ++; rda &= 7;
	SMS_setBGPaletteColor (8 + rda, pal_cycle_waterfall [4]); rda ++; rda &= 7;
	SMS_setBGPaletteColor (8 + rda, pal_cycle_waterfall [5]); rda ++; rda &= 7;
	SMS_setBGPaletteColor (8 + rda, pal_cycle_waterfall [6]); rda ++; rda &= 7;
	SMS_setBGPaletteColor (8 + rda, pal_cycle_waterfall [7]); rda ++; rda &= 7;
}

inline void tile_effects_factory_do (void) {
	// Update tiles
	UNSAFE_SMS_MT_VRAMmemcpy24 (VDP_ADDR_CONVEYOR_LEFT, (const unsigned char *) (work_level1_conveyor_left_bin + anim_tile_conveyor_offs));
	UNSAFE_SMS_MT_VRAMmemcpy24 (VDP_ADDR_CONVEYOR_RIGHT, (const unsigned char *) (work_level1_conveyor_right_bin + anim_tile_conveyor_offs));
	anim_tile_conveyor_offs += 24; if (anim_tile_conveyor_offs == 96) anim_tile_conveyor_offs = 0;
}

void debug_print_hex (unsigned char x, unsigned char y, unsigned char v) {
	SMS_setTileatXY (x, y, 432 + (v >> 4));
	SMS_setTile (432 + (v & 15));
}
