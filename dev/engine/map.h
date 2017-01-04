// MT MK1 SMS version 0.1 [Yun]
// Copyleft 2016 The Mojon Twins

// Map and map-related functions

void map_prepare (void) {
	// uncompress map
	aPLib_depack (map, c_map);
}

void map_scr_prepare (void) {
	gp_map = map_scr = map + (n_pant << 7) + (n_pant << 6);
}

void map_screen_update (void) {
	SMS_MT_initSpritesEx (7); 	// Sprites 0-6 are reserved for the hud.
	player_render ();
	SMS_MT_finalizeSpritesEx ();
	SMS_waitForVBlank ();
	UNSAFE_SMS_copySpritestoSAT ();
	ogt_run ();	
}

/*
void map_scr_draw (void) {
	map_scr_prepare ();

	rdx = 0; rdy = cur_col_y; gpit = 192; while (gpit --) {
		rdt = *gp_map ++;
		SMS_MT_draw2x2MetaTileatXY (rdx, rdy, c_ts_tmaps + (rdt << 2));
		rdx += 2; if (rdx == 32) { rdx = 0; rdy += 2; if (rdy >= 28) rdy -= 28; }
	}
}
*/

unsigned char map_real_y (unsigned char y) {
	rdyn = cur_col_y + y; if (rdyn >= 28) rdyn -= 28;
	return rdyn;
}

void map_set (unsigned char x, unsigned char y, unsigned char t) {
	map_scr [x + (y << 4)] = t;
	SMS_MT_draw2x2MetaTileatXY (x + x, map_real_y (y + y), c_ts_tmaps + (t << 2));
}

// Clears the screen using a box pattern of tile 0
void map_scr_clear (void) {
	sprites_out ();
	for (gpit = 0; gpit < 6; gpit ++) {
		rda = 16 - gpit;
		rdb = gpit + gpit;
		for (rdx = gpit; rdx < rda; rdx ++) {
			SMS_MT_draw2x2MetaTileatXY (rdx + rdx, map_real_y (rdb), c_ts_tmaps);
			SMS_MT_draw2x2MetaTileatXY (rdx + rdx, map_real_y (22 - rdb), c_ts_tmaps);
		}
		rda = 11 - gpit;
		for (rdy = gpit + 1; rdy < rda; rdy ++) {
			SMS_MT_draw2x2MetaTileatXY (rdb, map_real_y (rdy + rdy), c_ts_tmaps);
			SMS_MT_draw2x2MetaTileatXY (30 - rdb, map_real_y (rdy + rdy), c_ts_tmaps);
		}
		wait_for (4);
	}
}

const unsigned char *map_tile (unsigned char x, unsigned char y) {
	return c_ts_tmaps + (map_scr [x + (y << 4)] << 2);
}

// Draws the map using a box pattern from the center.
void map_scr_draw_box (void) {
	map_scr_prepare ();
	sprites_out ();
	for (gpit = 0; gpit < 6; gpit ++) {
		rda = 16 - gpit;
		rdb = gpit + gpit;
		for (rdx = gpit; rdx < rda; rdx ++) {
			SMS_MT_draw2x2MetaTileatXY (rdx + rdx, map_real_y (rdb), map_tile (rdx, gpit));
			SMS_MT_draw2x2MetaTileatXY (rdx + rdx, map_real_y (22 - rdb), map_tile (rdx, 11 - gpit));
		}
		rda = 11 - gpit;
		for (rdy = gpit + 1; rdy < rda; rdy ++) {
			SMS_MT_draw2x2MetaTileatXY (rdb, map_real_y (rdy + rdy), map_tile (gpit, rdy));
			SMS_MT_draw2x2MetaTileatXY (30 - rdb, map_real_y (rdy + rdy), map_tile (15 - gpit, rdy));
		}
		wait_for (4);
	}	
}

// The next four functions can be heavily optimized.

void map_scr_draw_from_right (void) {
	map_scr_prepare ();

	for (gpit = 0; gpit < 32; gpit ++) {
		SMS_setBGScrollX ((31 - gpit) << 3);
		gp_gen = gp_map + (gpit >> 1);
		rdy = cur_col_y; gpjt = 12; while (gpjt --) {
			rdt = *gp_gen; gp_gen += 16;
			SMS_MT_draw2x2MetaTileColatXY (gpit, rdy, gpit & 1, c_ts_tmaps + (rdt << 2));
			rdy += 2; if (rdy == 28) rdy = 0;
		}
		if (prx > 4) prx -= 8; 
		map_screen_update ();
	}
}

void map_scr_draw_from_left (void) {
	map_scr_prepare ();

	gpit = 32; while (gpit --) {
		SMS_setBGScrollX ((32 - gpit) << 3);
		gp_gen = gp_map + (gpit >> 1);
		rdy = cur_col_y; gpjt = 12; while (gpjt --) {
			rdt = *gp_gen; gp_gen += 16;
			SMS_MT_draw2x2MetaTileColatXY (gpit, rdy, gpit & 1, c_ts_tmaps + (rdt << 2));
			rdy += 2; if (rdy == 28) rdy = 0;
		}
		if (prx < 244) prx += 8; 
		map_screen_update ();
	}
}

void map_scr_draw_from_down (void) {
	map_scr_prepare ();
	psprid = pfacing + CELL_DESCENDING;

	for (gpit = 0; gpit < 24; gpit ++) {
		rdy = cur_col_y + 24; if (rdy >= 28) rdy -= 28;
		cur_col_y ++; if (cur_col_y == 28) cur_col_y = 0;
		SMS_setBGScrollY (cur_col_y << 3);
		gp_gen = gp_map + ((gpit >> 1) << 4);
		for (rdx = 0; rdx < 32; rdx += 2) {
			rdt = *gp_gen ++;
			SMS_MT_draw2x2MetaTileRowatXY (rdx, rdy, gpit & 1, c_ts_tmaps + (rdt << 2));
		}
		rdy ++;
		if (pry) pry -= 8;
		map_screen_update ();
	}
}

void map_scr_draw_from_up (void) {
	map_scr_prepare ();
	psprid = pfacing + CELL_ASCENDING;

	gpit = 24; while (gpit --) {
		if (cur_col_y) cur_col_y --; else cur_col_y = 27;
		gp_gen = gp_map + ((gpit >> 1) << 4);
		for (rdx = 0; rdx < 32; rdx += 2) {
			rdt = *gp_gen ++;
			SMS_MT_draw2x2MetaTileRowatXY (rdx, cur_col_y, gpit & 1, c_ts_tmaps + (rdt << 2));
		}
		SMS_setBGScrollY (cur_col_y << 3);
		rdy --;
		if (pry < 192) pry += 8;
		map_screen_update ();
	}
}
