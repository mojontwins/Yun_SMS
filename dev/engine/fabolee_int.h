// MT MK1 SMS version 0.1 [Yun]
// Copyleft 2016 The Mojon Twins

// Fabolee - Simple bubbles
// Faster, less accurate implementation using integer math.

void enems_kill (void);

const unsigned char fabolee_frames [] = { 4, 5, 6, 5 };

inline void fabolee_init (void) {
	gpit = FABOLEES_MAX; while (gpit --) {
		fbl_ct [gpit] = 0; 
	}
}

inline void fabolee_new (void) {
	// Creates new fabolee at px, py.
	gpit = FABOLEES_MAX; while (gpit --) {
		if (!fbl_ct [gpit]) {
			fbl_y [gpit] = pry - 16; fbl_x [gpit] = prx - 4;
			fbl_idx_y [gpit] = 0; fbl_idx_my [gpit] = 1;
			fbl_idx_x [gpit] = 0;
			fbl_facing [gpit] = !!pfacing;
			fbl_ct [gpit] = 200; fbl_lock_on [gpit] = 0xff;
			fbl_accctr [rdct] = 0;
			//sfx_play (5, 0);
			break;
		}
	}
}

inline void fabolee_do (void) {
	rdct = FABOLEES_MAX; while (rdct --) {
		if (fbl_ct [rdct]) {
			gpit = fbl_lock_on [rdct];

			if (gpit == 0xff) {
				if (fbl_facing [rdct]) 
					fbl_x [rdct] -= fbl_incr_x [fbl_idx_x [rdct]]; 
				else
					fbl_x [rdct] += fbl_incr_x [fbl_idx_x [rdct]]; 
				if (fbl_idx_x [rdct] < FBL_INCR_MAX) fbl_idx_x [rdct] ++;

				if (fbl_idx_my [rdct]) {
					fbl_y [rdct] -= fbl_incr_y [fbl_idx_y [rdct]]; 
					if (fbl_idx_y [rdct] < FBL_INCR_MAX) fbl_idx_y [rdct] ++;
				} else {
					fbl_y [rdct] += fbl_incr_y [fbl_idx_y [rdct]]; 
					fbl_idx_y [rdct] --; if (!fbl_idx_y [rdct]) fbl_idx_my [rdct] = 1;
				}
				
				if (fbl_x [rdct] > 240) {
					if (fbl_facing [rdct]) {
						fbl_x [rdct] = fbl_facing [rdct] = 0;
					} else {
						fbl_x [rdct] = 240; fbl_facing [rdct] = 1;
					}
				}

				if (fbl_y [rdct] > 240) {
					fbl_y [rdct] = 0;
					fbl_idx_y [rdct] = (4 + (RAND8 & 7)) << 1;
					fbl_idx_my [rdct] = 0;
				}
			} else {	
				fbl_x [rdct] = en_c_x [gpit]; fbl_y [rdct] = en_c_y [gpit];
				if (en_c_y [gpit] == 192) {
					fbl_lock_on [rdct] = 0xff;
					enems_kill ();
				}
			}	

			rdx = fbl_x [rdct];
			rdy = fbl_y [rdct];

			if (fbl_ct [rdct] > 50 || half_life) SMS_MT_addMetaspriteSimple (rdx, rdy, spr_it [fabolee_frames [(frame_counter + rdct) & 3]]); // Embedded here for speed

			// Collide
			if (gpit == 0xff) {
				
				if (run_flip_flop) {
					gpjt = 3; while (gpjt --) {
						if (en_c_t [gpjt] && en_c_t [gpjt] != 4 && (en_c_t [gpjt] != 9 || en_c_mx [gpjt] == 2) && !en_ud [gpjt]) {
							if (collide (rdx, rdy, en_c_x [gpjt], en_c_y [gpjt])) {
								en_ud [gpjt] = 1;
								fbl_lock_on [rdct] = gpjt;
								//sfx_play (5, 0);
							}
						}
					}	
				}
				
				if (rdy > 16 && (!pj)) {
					if (prx + 9 >= rdx && prx <= rdx + 17) {
						//if (pry + 17 >= rdy && pry + 12 <= rdy) {
						if (pry + 1 >= rdy && pry <= rdy + 4) {
							pgotten = 1; 
							//pgtmy = fbl_vy [rdct]; pgtmx = fbl_vx [rdct];
							//py = (rdy - 16) << FIX_BITS; pry = py >> FIX_BITS;
							pcy = py;
							pry = rdy; py = pry << FIX_BITS;
							pgtmy = py - pcy;
							pvy = 0;
						}
					}
				}
			}

			fbl_ct [rdct] --;

			// Free?
			if (!fbl_ct [rdct] && gpit != 0xff) {
				en_ud [gpit] = 0;
				if (en_c_t [gpit] == 9) enems_kill ();
			}
		} 
	}
}
