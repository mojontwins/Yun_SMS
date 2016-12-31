// MT MK1 SMS version 0.1 [Yun]
// Copyleft 2016 The Mojon Twins

// Printer. Auxiliary printing functions

void sprites_out (void) {
	SMS_MT_initSpritesEx (7); 	// Sprites 0-6 are reserved for the hud.
	SMS_finalizeSprites ();
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
