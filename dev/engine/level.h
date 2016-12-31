// MT MK1 SMS version 0.1 [Yun]
// Copyleft 2016 The Mojon Twins

// Level preparation & related stuff

void level_prepare (void) {
	// assign variables
	c_bank = level_banks [level];
	c_map = level_maps [level];
	c_ts_tmaps = level_ts_tmaps [level];
	c_pals = level_pals [level];
	c_map_w = level_map_w [level];
	c_map_h = level_map_h [level];
	c_enems = level_enems [level];
	c_behs = level_behs [level];
	c_hotspots = level_hotspots [level];

	SMS_mapROMBank (c_bank);
	
	// uncompress graphics
	aPLib_depack_VRAM (256 * 32, level_ts_patterns [level]);
	aPLib_depack_VRAM (185 * 32, level_ss_patterns [level]);

	// set palette
	SMS_loadBGPalette (c_pals);
	SMS_loadSpritePalette (c_pals + 16);
	if (level == 2) pal_cycle_desert_do ();

	// Start
	n_pant = level_scr_ini [level];
}
