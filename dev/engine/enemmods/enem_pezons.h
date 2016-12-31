// All hail the pezons!

// mx is counter, my is max value for counter.

	if (en_ud [gpit]) {
		spr_x = en_c_x [gpit] + jitter_x;
		spr_y = en_c_y [gpit] + jitter_y;
		en_cell [gpit] = PEZON_BASE_SPRID_UD;
	} else {
		switch (PEZON_STATE [gpit]) {
			case 0:
				if (PEZON_COUNTER [gpit]) {
					PEZON_COUNTER [gpit] --;
				} else {
					PEZON_COUNTER [gpit] = PEZON_COUNT_MAX [gpit];
					PEZON_STATE [gpit] = 1;
					enf_y [gpit] = en_c_y1 [gpit] << 4;
					enf_vy [gpit] = -PEZON_THRUST;
				}
				break;
			case 1:
				if (enf_vy [gpit] < PEZON_VY_FALLING_MAX) enf_vy [gpit] += PEZON_G;
				enf_y [gpit] += enf_vy [gpit];
				en_c_y [gpit] = enf_y [gpit] >> 4;
				if (en_c_y [gpit] > en_c_y1 [gpit]) {
					en_c_y [gpit] = en_c_y1 [gpit];
					PEZON_STATE [gpit] = 0;
				}
				break;
		}

		spr_x = en_c_x [gpit];
		spr_y = en_c_y [gpit];
		en_cell [gpit] = PEZON_BASE_SPRID;
	}
