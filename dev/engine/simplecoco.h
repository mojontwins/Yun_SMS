// MT MK1 SMS version 0.1 [Yun]
// Copyleft 2016 The Mojon Twins

// Really really simple coco implementation

inline void simplecoco_init (void) {
	cocoit = COCOS_MAX; while (cocoit --) {
		coco_flag [cocoit] = 0;
	}
}

inline void simplecoco_new () {
	// Create coco @ rdx, rdy
	cocoit = COCOS_MAX; while (cocoit --) if (!coco_flag [cocoit]) {
		// Calculate distance
		rda = DELTA (prx, rdx); // dx
		rdb = DELTA (pry - 16, rdy); // dy
		rdc = MIN (rda, rdb);	// min (dx, dy)
		rdct = rda + rdb - (rdc >> 1) - (rdc >> 2) + (rdc >> 4);
		
		if (rdct > COCO_FAIR_D) {
			// Shoot towards the player.
			coco_x [cocoit] = rdx << FIX_BITS;
			coco_y [cocoit] = rdy << FIX_BITS;

			// Apply formula. Looks awkward but it's optimized for space and shitty compiler
			rds16 = COCO_V * rda / rdct; coco_vx [cocoit] = ADD_SIGN_2 (coco_x [cocoit], px, rds16);
			rds16 = COCO_V * rdb / rdct; coco_vy [cocoit] = ADD_SIGN_2 (coco_y [cocoit], py, rds16);

			coco_flag [cocoit] = 1;
		}
		
		break;
	}
}

inline void simplecoco_do (void) {
	cocoit = COCOS_MAX; while (cocoit --) if (coco_flag [cocoit]) {
		// Move
		coco_x [cocoit] += coco_vx [cocoit];
		coco_y [cocoit] += coco_vy [cocoit];

		// Out of bounds
		if (coco_x [cocoit] < 0 || coco_x [cocoit] > 256<<FIX_BITS || coco_y [cocoit] < 0 || coco_y [cocoit] > 192<<FIX_BITS) {
			coco_flag [cocoit] = 0; break;
		}

		rdx = coco_x [cocoit] >> FIX_BITS;
		rdy = coco_y [cocoit] >> FIX_BITS;

		SMS_MT_addSpriteFast (rdx, rdy, 15); 	// Embedded here for speed

		// Collide w/player
		if (pstate == STATE_NORMAL && rdx + 7 >= prx && rdx <= prx + 7 && rdy + 23 >= pry && rdy + 4 <= pry) {
			pkilled = 1;
			coco_flag [cocoit] = 0; 
		}
	} 
}

/*
void simplecoco_render (void) {
	cocoit = COCOS_MAX; while (cocoit --) if (coco_flag [cocoit]) {
		SMS_MT_addSpriteFast (
			coco_x [cocoit] >> FIX_BITS,
			(coco_y [cocoit] >> FIX_BITS) - 1,
			15
		);
	}
}
*/
