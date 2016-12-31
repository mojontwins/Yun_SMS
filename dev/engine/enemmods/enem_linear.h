	if (en_ud [gpit]) {
		spr_x = en_c_x [gpit] + jitter_x;
		spr_y = en_c_y [gpit] + jitter_y;
		en_cell [gpit] = CELL_UPSIDEDOWN_BASE + en_s [gpit] + en_s [gpit] + (RAND8 & 1);
	} else {
		if (!en_c_fs [gpit] || half_life) {
			en_c_x [gpit] += en_c_mx [gpit];
			en_c_y [gpit] += en_c_my [gpit];

			if ((en_c_mx [gpit] < 0 && en_c_x [gpit] <= en_c_x1 [gpit]) || (en_c_mx [gpit] > 0 && en_c_x [gpit] >= en_c_x2 [gpit])) en_c_mx [gpit] = -en_c_mx [gpit];
			if ((en_c_my [gpit] < 0 && en_c_y [gpit] <= en_c_y1 [gpit]) || (en_c_my [gpit] > 0 && en_c_y [gpit] >= en_c_y2 [gpit])) en_c_my [gpit] = -en_c_my [gpit];
		}
		if (en_c_mx [gpit]) {
			en_facing = en_c_mx [gpit] > 0 ? 0 : 2;
			en_fr = (((en_c_x [gpit]) >> 4) & 1);
		} else {
			en_facing = en_c_my [gpit] > 0 ? 0 : 2;
			en_fr = (((en_c_y [gpit]) >> 4) & 1);
		}

		if (en_c_t [gpit] == 4) {
			en_cell [gpit] = CELL_LEVELENEMS_BASE + (en_s [gpit] << 2) + en_fr;
		} else {
			en_cell [gpit] = CELL_LEVELENEMS_BASE + (en_s [gpit] << 2) + en_facing + en_fr;
		}
		spr_x = en_c_x [gpit];
		spr_y = en_c_y [gpit];
	}
