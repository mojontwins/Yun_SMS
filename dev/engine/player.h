// MT MK1 SMS version 0.1 [Yun]
// Copyleft 2016 The Mojon Twins

// Player movement & stuff

inline void player_init (void) {
	// Init player data

	px = (signed int) (level_ini_x [level] << 4) << FIX_BITS;
	py = (signed int) (level_ini_y [level] << 4) << FIX_BITS;
	
	psprid = 6;
	pvx = pvy = pfacing = pj = pctj = 0;
	pobjs = pkeys = pgotten = pfiring = 0;
	pstate = STATE_NORMAL;
	pkilled = 0;

	px_safe = px;
	py_safe = py;
	n_pant_safe = n_pant;
}

inline void player_kill (void) {
	if (plife) plife --; else pisdead = 1;
	hud_render_numbers ();
	pstate = STATE_FLICKERING;
	pctstate = 100;	
	//sfx_play (4, 0);
	PSGSFXPlay (SFX_PLAYER_HIT, SC_PLAYER);
	px = px_safe;
	py = py_safe;
	n_pant = n_pant_safe;
	on_pant = 99; 			// Forces a full fuck
	//music_pause (1);
	wait_for (ticks);
	pvx = pvy = pj = 0;
	//music_pause (0);
}

void map_set (unsigned char x, unsigned char y, unsigned char t);

void player_process_block (unsigned char x0, unsigned char y0) {
	y0 -= TILE_ORIGIN;

	// Some cheese while I think of something better
	if (10 != c_behs [map_scr [x0 + (y0 << 4)]]) return;

	if (pkeys) {
		map_set (x0, y0, 0);
		pkeys --;
		hud_render_numbers ();
		// SOUND
	} else {
		no_x = (x0 << 4) + 8; no_y = (y0 << 4) - 13;
		no_ct = 100;
	}
}

inline void player_do (void) {
	if (pstate != STATE_NORMAL) {
		if (pctstate) pctstate --; else pstate = STATE_NORMAL;
	}

	// ********
	// Vertical
	// ********

	phit = 0;

	// gravity
	if (!pgotten) {
		if (pvy < PLAYER_VY_FALLING_MAX) pvy += PLAYER_G; else pvy = PLAYER_VY_FALLING_MAX;
	}

	// Move
	py += pvy;
	if (py < 0) py = 0;
	if (py > 192 << FIX_BITS) py = 192 << FIX_BITS;

	// Collision
	prx = px >> FIX_BITS;
	pry = py >> FIX_BITS;
	
	cx1 = prx >> 4;
	cx2 = (prx + 7) >> 4;
	if (pvy + pgtmy < 0) {
		cy1 = cy2 = pry >> 4;
		cm_two_points ();
		if ((at1 & 8) || (at2 & 8)) {
			pgotten = pvy = 0;
			pry = (cy1 + 1) << 4;
			py = pry << FIX_BITS;
			if (at1 == 10) player_process_block (cx1, cy1);
			if (at2 == 10) player_process_block (cx2, cy2);
		} else if ((at1 & 2) || (at2 & 2)) {
			if (pctj > 2) pj = 0;
		}
	} else if (pvy + pgtmy > 0)	{
		cy1 = cy2 = (pry + 15) >> 4;
		cm_two_points ();
		if (((pry - 1) & 15) < 4 && ((at1 & 12) || (at2 & 12))) {
			pgotten = pvy = 0;
			pry = (cy1 - 1) << 4;
			py = pry << FIX_BITS;
			if (at1 == 10) player_process_block (cx1, cy1);
			if (at2 == 10) player_process_block (cx2, cy2);
		} else {
			phit = ((at1 & 1) || (at2 & 1));
			if ((at1 & 2) || (at2 & 2)) pvy = PLAYER_VY_SINK;
		}
	}
	cy1 = cy2 = (pry + 16) >> 4;
	cm_two_points ();
	ppossee = ((at1 & 14) || (at2 & 14));
	pice = (ppossee && ((at1 & 64) || (at2 & 64)));
	
	// Conveyors
	
	if (ppossee) {
		pconvd1 = at1 & 1; pconvd2 = at2 & 1; 
		if (at1 & 32) { if (pconvd1) pgtmx = 16; else pgtmx = -16; pgotten = 1; }
		if (at2 & 32) { if (pconvd2) pgtmx = 16; else pgtmx = -16; pgotten = 1; }
	}

	// Jump: PAD_A
	if (gpint & PORT_A_KEY_2) { 
		if (!pjb) {
			pjb = 1;
			if (!pj) {
				if (pgotten || ppossee) {
					pj = 1; pctj = 0;
					PSGSFXPlay (SFX_JUMP, SC_PLAYER);
					pvy = -PLAYER_VY_JUMP_INITIAL;
					if (ppossee) {
						px_safe = px;
						py_safe = py;
						n_pant_safe = n_pant;
					}
				}
			} 
		}
		if (pj) {
			rda = PLAYER_AY_JUMP - (pctj >> 2) - (pctj >> 3);
			pvy -= (rda > 1 ? rda : 1);
			if (pvy < -PLAYER_VY_JUMP_MAX) pvy = -PLAYER_VY_JUMP_MAX;
			pctj ++; if (pctj == PLAYER_VY_JUMP_A_STEPS) pj = 0;	
		}
	} else {
		pj = 0; pjb = 0;
	}

	// **********
	// Horizontal
	// **********
	
	// Poll pad
	if (gpint & PORT_A_KEY_LEFT) {
		if (pvx > -PLAYER_VX_MAX) pvx -= pice ? PLAYER_AX_SLIP : PLAYER_AX;			
		pfacing = CELL_FACING_LEFT;
	} else if (gpint & PORT_A_KEY_RIGHT) {
		if (pvx < PLAYER_VX_MAX) pvx += pice ? PLAYER_AX_SLIP : PLAYER_AX;
		pfacing = CELL_FACING_RIGHT;		
	} else {
		if (pvx > 0) {
			pvx -= pice ? PLAYER_RX_SLIP : PLAYER_RX;
			if (pvx < 0) pvx = 0;
		} else if (pvx < 0) {
			pvx += pice ? PLAYER_RX_SLIP : PLAYER_RX;
			if (pvx > 0) pvx = 0;
		}
	}
	
	// Move
	px += pvx;
	if (pgotten) px += pgtmx;
	if (px < 4 << FIX_BITS) px = 4 << FIX_BITS;
	if (px > 244 << FIX_BITS) px = 244 << FIX_BITS;
	
	// Collision
	prx = px >> FIX_BITS;

	cy1 = pry >> 4;
	cy2 = (pry + 15) >> 4;
	if (pvx + pgtmx < 0) {
		cx1 = cx2 = prx >> 4;
		cm_two_points ();
		if ((at1 & 8) || (at2 & 8)) {
			pvx = 0;
			prx = (cx1 + 1) << 4;
			px = prx << FIX_BITS;
			if (at1 == 10) player_process_block (cx1, cy1);
			if (at2 == 10) player_process_block (cx2, cy2);
		}
	} else if (pvx + pgtmx > 0) {
		cx1 = cx2 = (prx + 7) >> 4;
		cm_two_points ();
		if ((at1 & 8) || (at2 & 8)) {
			pvx = 0;
			prx = ((cx1 - 1) << 4) + 8;
			px = prx << FIX_BITS;
			if (at1 == 10) player_process_block (cx1, cy1);
			if (at2 == 10) player_process_block (cx2, cy2);
		}
	}

	// *************
	// Killing tiles
	// *************
	if (phit) {
		if (pstate == STATE_FLICKERING) pvy = -PLAYER_VY_JUMP_MAX; else pkilled = 1;
		PSGSFXPlay (SFX_COIN, SC_PLAYER);
	}

	// ********
	// Fabolees
	// ********
	if (gpint & PORT_A_KEY_1) {
		if (!pfiring) fabolee_new ();
		pfiring = 1;
	} else pfiring = 0;

	// facing = 0 || 8
	// frame = 0 standing, 1 2 3 4 running, 5 jumping, 6 7 falling
	if (ppossee || pgotten) {
		if (pvx > PLAYER_VX_MIN || pvx < -PLAYER_VX_MIN) {
			psprid = pfacing + CELL_WALK_BASE + ((prx >> 4) & 3);
		} else {
			psprid = pfacing;
		}
	} else {
		psprid = pfacing + (pvy >= (PLAYER_VY_FALLING_MAX >> 3) ? CELL_DESCENDING : CELL_ASCENDING);
	}

	// This is very important.
	pgotten = 0; pgtmx = 0;	pgtmy = 0;
		
	// Pa tó tu coño
}

inline void player_render (void) {
	if (pstate == STATE_NORMAL || half_life) {
		//SMS_MT_addMetaspriteSimple (prx, pry - 17, spr_pl [psprid]);
		SMS_MT_add2x3MetaSpriteSimpleUnrolled (prx, pry - 17, spr_pl [psprid]);
	}
}
