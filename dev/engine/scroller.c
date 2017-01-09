// MT MK1 SMS version 0.1 [Yun]
// Copyleft 2016 The Mojon Twins

// Simple, 1 way scroller

#include "../lib/SMSlib.h"

#include "scroller.h"

extern const unsigned char *c_map_ptr;
extern const unsigned int *c_ts_tmaps;
extern const unsigned char *c_behs;

extern unsigned char map [];
extern unsigned char advance_cam;
extern signed int cam_x;
extern signed int cam_x_coarse, cam_x_coarse_old;
extern unsigned char column;
extern unsigned char draw_new_column;
extern volatile unsigned char need_new_column_from_map;

extern unsigned char collision_buffer [];
extern unsigned char collision_buffer_idx;

extern unsigned int scroll_buffer [];
extern unsigned int *scroll_buffer_ptr0, *scroll_buffer_ptr1;

extern unsigned char rdx, rdy, rdt, gpit;
extern const unsigned int *gp_gint;

inline void scroller_cam_advance (void) {
	if (advance_cam) cam_x ++;
	cam_x_coarse = (cam_x >> 3);
	draw_new_column = (cam_x_coarse != cam_x_coarse_old);
	cam_x_coarse_old = cam_x_coarse;
}

inline void scroller_fill_buffer (void) {
	if (need_new_column_from_map) {
		gpit = 4; while (gpit --) {
			// Get tile from map
			rdt = *c_map_ptr ++;
			
			// Draw to the collision circular buffer
			collision_buffer [collision_buffer_idx] = rdt; //c_behs [rdt];
			collision_buffer_idx += 16;

			// Draw metatile
			
			gp_gint = c_ts_tmaps + (rdt << 2); 
			*scroll_buffer_ptr0 ++ = *gp_gint ++;
			*scroll_buffer_ptr1 ++ = *gp_gint ++;
			*scroll_buffer_ptr0 ++ = *gp_gint ++;
			*scroll_buffer_ptr1 ++ = *gp_gint ++;
		}

		need_new_column_from_map --;
	}
}

inline void scroller_draw_new_column_in_blank (void) {
	if (draw_new_column) {
			UNSAFE_SMS_MT_ScrollUpdateVDP (
			scroll_buffer + (column ? 24 : 0),
			cam_x_coarse & 0x1f
		);
		draw_new_column = 0;

		// Need new column from map?
		if (column) {
			need_new_column_from_map = 3;
			collision_buffer_idx = ((cam_x_coarse + 1) >> 1) & 0x0f;

			scroll_buffer_ptr0 = scroll_buffer;
			scroll_buffer_ptr1 = scroll_buffer + 24;
		}

		column = 1 - column;
	}
}

inline void scroller_init (void) {
	c_map_ptr = map;
	column = 0;
	cam_x = 0;

	for (rdx = 0; rdx < 16; rdx ++) {
		for (rdy = 0; rdy < 12; rdy ++) { 
			rdt = *c_map_ptr ++;
			collision_buffer [(rdy << 4) + rdx] = rdt;
			SMS_MT_draw2x2MetaTileatXY (rdx + rdx, rdy + rdy, c_ts_tmaps + (rdt << 2));
		}
	}

	// Fill buffer
	collision_buffer_idx = 0;
	scroll_buffer_ptr0 = scroll_buffer;
	scroll_buffer_ptr1 = scroll_buffer + 24;
	need_new_column_from_map = 3; 
	collision_buffer_idx = 0;
	scroller_fill_buffer ();
	scroller_fill_buffer ();
	scroller_fill_buffer ();

	cam_x_coarse_old = cam_x_coarse = 0;
	draw_new_column = 1; column = 0;
	need_new_column_from_map = 0;
}
