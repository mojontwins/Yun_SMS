// MT MK1 SMS version 0.1 [Yun]
// Copyleft 2016 The Mojon Twins

// General & all purpose

inline signed int saturate (signed int v, signed int max) {
	return v >= 0 ? (v > max ? max : v) : (v < -max ? -max : v);
}

inline void cm_two_points (void) {
	// Calculates at1 & at2 from cx1, cy1 & cx2, cy2
	at1 = c_behs [map_scr [cx1 + (((cy1 >= TILE_ORIGIN) ? (cy1 - TILE_ORIGIN) : 0) << 4)]];
	at2 = c_behs [map_scr [cx2 + (((cy2 >= TILE_ORIGIN) ? (cy2 - TILE_ORIGIN) : 0) << 4)]];
}

inline signed int add_sign (signed int sign, signed int value) {
	return sign == 0 ? 0 : sign < 0 ? -value : value;
}

inline unsigned char collide (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2) {
	return (x1 + 8 >= x2 && x1 <= x2 + 8 && y1 + 8 >= y2 && y1 <= y2 + 8);
}

inline void ogt_run (void) {
	SMS_mapROMBank (2);
	PSGSFXFrame ();
	SMS_mapROMBank (c_bank);
	PSGFrame ();	
}

void wait_for (unsigned char nticks) {
	ticker = nticks; while (-- ticker) {
		SMS_waitForVBlank ();
		ogt_run ();
	}
}
