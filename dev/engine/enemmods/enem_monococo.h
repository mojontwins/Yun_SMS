	// All hail the monococo!

	if (en_ud [gpit]) {
		spr_x = en_c_x [gpit] + jitter_x;
		spr_y = en_c_y [gpit] + jitter_y;
		en_cell [gpit] = MONOCOCO_BASE_SPRID_UD + (RAND8 & 1);
	} else {
		// Counter & state change
		MONOCOCO_COUNTER [gpit] --; if (!MONOCOCO_COUNTER [gpit]) {
			MONOCOCO_STATE [gpit] = (MONOCOCO_STATE [gpit] + 1) & 3; MONOCOCO_COUNTER [gpit] = monococo_state_times [MONOCOCO_STATE [gpit]] + (RAND8 & 0x1f);
		}

		// Shoot
		if (MONOCOCO_STATE [gpit] == 2 && MONOCOCO_COUNTER [gpit] == FIRE_COCO_AT) {
			rdx = MONOCOCO_X [gpit] + 4; rdy = MONOCOCO_Y [gpit] + 4; simplecoco_new ();
		}

		// Sprite
		spr_x = en_c_x [gpit];
		spr_y = en_c_y [gpit];

		/*
		en_cell [gpit] = monococo_metasprite [MONOCOCO_STATE [gpit]] + ((MONOCOCO_STATE [gpit] == 2 && ((frame_counter >> 4) & 1)) << 1);
		*/
		switch (MONOCOCO_STATE [gpit]) {
			case 0: en_cell [gpit] = 132; break;
			case 1: 
				if (level) {
					en_cell [gpit] = half_life ? 132 : 135;
				} else {
					en_cell [gpit] = 0;
				}
				break;
			case 2:
				en_cell [gpit] = 2 + ((frame_counter >> 4) & 1);
				break;
		}
	}

