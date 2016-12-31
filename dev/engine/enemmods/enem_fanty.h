	if (en_ud [gpit]) {
		spr_x = en_c_x [gpit] + jitter_x;
		spr_y = en_c_y [gpit] + jitter_y;
		en_cell [gpit] = FANTY_BASE_SPRID_UD + (en_c_x [gpit] > prx);
	} else {
		// Modify v
		if (run_flip_flop) {
			enf_vx [gpit] = saturate (enf_vx [gpit] + ADD_SIGN_2 (en_c_x [gpit], prx, FANTY_A + FANTY_A), FANTY_MAXV);
			enf_vy [gpit] = saturate (enf_vy [gpit] + ADD_SIGN_2 (en_c_y [gpit], pry, FANTY_A + FANTY_A), FANTY_MAXV);
		}

		// Horizontal
		enf_x [gpit] += enf_vx [gpit]; 
		enf_y [gpit] += enf_vy [gpit]; 

		if (run_flip_flop) {
			if (enf_x [gpit] < (4<<FIX_BITS)) { enf_x [gpit] = (4<<FIX_BITS); enf_vx [gpit] = -enf_vx [gpit]; }
			if (enf_x [gpit] > (236<<FIX_BITS)) { enf_x [gpit] = (236<<FIX_BITS); enf_vx [gpit] = -enf_vx [gpit]; }

			if (enf_y [gpit] < (4<<FIX_BITS)) { enf_y [gpit] = (4<<FIX_BITS); enf_vy [gpit] = -enf_vy [gpit]; }
			if (enf_y [gpit] > (172<<FIX_BITS)) { enf_y [gpit] = (172<<FIX_BITS); enf_vy [gpit] = -enf_vy [gpit]; } 
		}

		spr_x = en_c_x [gpit] = enf_x [gpit] >> FIX_BITS;
		spr_y = en_c_y [gpit] = enf_y [gpit] >> FIX_BITS;

		en_facing = (en_c_x [gpit] > prx) ? 2 : 0;
		en_fr = (en_c_x [gpit] >> 3) & 1;

		en_cell [gpit] = FANTY_BASE_SPRID + en_facing + en_fr;

		run_flip_flop = !run_flip_flop;
	}
