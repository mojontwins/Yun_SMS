// MT MK1 SMS version 0.1 [Yun]
// Copyleft 2016 The Mojon Twins

// Level preparation & related stuff

#include "../lib/SMSlib.h"
#include "../lib/aPLib.h"

#include "printer.h"
#include "level.h"

extern unsigned char level;
extern unsigned char c_bank;
extern unsigned char c_map_w, c_map_h;
extern const unsigned char *c_map;
extern const unsigned int *c_ts_tmaps;
extern const unsigned char *c_pals;
extern const unsigned char *c_enems;
extern const unsigned char *c_hotspots;
extern const unsigned char *c_behs;
extern unsigned char n_pant;

extern const unsigned char level_banks [];
extern const unsigned char * const level_maps [];
extern const unsigned char * const level_ts_patterns [];
extern const unsigned char * const level_ss_patterns [];
extern const unsigned int * const level_ts_tmaps [];
extern const unsigned char * const level_pals [];
extern const unsigned char level_scr_ini [];
extern const unsigned char level_ini_x [];
extern const unsigned char level_ini_y [];
extern const unsigned char level_map_w [];
extern const unsigned char level_map_h [];
extern const unsigned char * const level_enems [];
extern const unsigned char * const level_behs [];
extern const unsigned char * const level_hotspots [];
extern const unsigned char * const level_tunes [];

void level_prepare (void) {
	// assign variables
	c_bank = level_banks [level];
	c_map = level_maps [level];
	c_ts_tmaps = level_ts_tmaps [level];
	c_pals = level_pals [level];
	c_behs = level_behs [level];
	c_enems = level_enems [level];

	if (level < 5) {
		c_hotspots = level_hotspots [level];
		n_pant = level_scr_ini [level];
		c_map_w = level_map_w [level];
		c_map_h = level_map_h [level];
	}

	SMS_mapROMBank (c_bank);
	
	// uncompress graphics
	aPLib_depack_VRAM (256 * 32, level_ts_patterns [level]);
	aPLib_depack_VRAM (level == 1 ? 170 * 32 : 185 * 32, level_ss_patterns [level]);

	// set palette
	SMS_loadBGPalette (c_pals);
	SMS_loadSpritePalette (c_pals + 16);
	if (level == 2) pal_cycle_desert_do ();
}
