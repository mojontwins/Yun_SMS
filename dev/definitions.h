// MT MK1 SMS version 0.1 [Yun]
// Copyleft 2016 The Mojon Twins

// Macros
#define ADD_SIGN_2(a,b,c)		(((a)==(b))?0:(((a)<(b))?(c):-(c)))
#define RAND8 					(random_seq [cur_rand ++])
#define DELTA(a,b)				((a) < (b) ? (b) - (a) : (a) - (b))
#define MIN(a,b)				((a) < (b) ? (a) : (b))
#define ABS(n)					((n) < 0 ? -(n) : (n))

// Game values

#define FIX_BITS 				4
#define TILE_ORIGIN 			1
#define MAX_LEVELS 				5

#define CELL_LEVELENEMS_BASE 	8
#define CELL_UPSIDEDOWN_BASE    CELL_LEVELENEMS_BASE+16*MAX_LEVELS+4

#define CELL_FACING_LEFT		7
#define CELL_FACING_RIGHT 		0
#define CELL_WALK_BASE			1
#define CELL_ASCENDING			5
#define CELL_DESCENDING 		6

// This game customs

#define SPR_EXPLOSION 			ss_items_02

// General

#define MAX_SCREENS				24
#define MAX_ENEMS_SCREEN		3
#define MAX_ENEMS 				MAX_ENEMS_SCREEN*MAX_SCREENS

// Enems stuff

#define ENABLE_FANTY
#define FANTY_BASE_SPRID		4
#define FANTY_BASE_SPRID_UD 	90
#define FANTY_A 				1
#define FANTY_MAXV 				16
//#define FANTY_COLLIDES

#define ENABLE_MONOCOCO
#define MONOCOCO_BASE_SPRID		0
#define MONOCOCO_BASE_SPRID_UD 	88
#define BASE_TIME_HIDDEN		150
#define BASE_TIME_APPEARING		50
#define BASE_TIME_ONBOARD		50
#define FIRE_COCO_AT			BASE_TIME_ONBOARD/2
#define MONOCOCO_X 				en_c_x 
#define MONOCOCO_Y 				en_c_y 
#define MONOCOCO_COUNTER 		en_c_my
#define MONOCOCO_STATE 			en_c_mx

#define ENABLE_COCOS
#define COCOS_MAX				3
#define COCO_V					48
#define COCO_PATTERN			34
#define COCO_FAIR_D				32

#define PEZON_WAIT				50
#define PEZON_THRUST			96
#define PEZON_VY_FALLING_MAX	64	
#define PEZON_G					4
// Make code more readable:
#define PEZON_COUNT_MAX			en_c_my
#define PEZON_COUNTER			en_c_mx
#define PEZON_STATE				en_r
#define PEZON_BASE_SPRID		133
#define PEZON_BASE_SPRID_UD 	134

// Player stuff

#define PLAYER_VY_FALLING_MAX	64
#define PLAYER_G				4
#define PLAYER_VY_JUMP_INITIAL	16
#define PLAYER_VY_JUMP_MAX		64		
#define PLAYER_VY_JUMP_BUTT		96
#define PLAYER_VY_JUMP_A_STEPS  16
#define PLAYER_VY_MIN_FLICK		12
#define PLAYER_VY_SINK			2
#define PLAYER_AY_JUMP 			8	
#define PLAYER_VX_MAX			32	
#define PLAYER_AX				2 // 4	
#define PLAYER_RX				2 // 4
#define PLAYER_AX_SLIP			1
#define PLAYER_RX_SLIP			1
#define PLAYER_VX_MIN (PLAYER_AX << 2)
#define PLAYER_V_REBOUND		56

#define STATE_NORMAL			0
#define STATE_FLICKERING 		1

// Fabolees

#define ENABLE_FABOLEES
#define FABOLEES_MAX 			3
#define FABOLEES_AX 			1
#define FABOLEES_AY 			129 	// === .5, half! ufff
#define FABOLEES_VY_MAX 		32
#define FABOLEES_VX_INI			42 

#define FBL_INCR_MAX 			63

// Sound effects

#define SFX_SELECT		sfx_select_psg
#define SFX_START		sfx_start_psg
#define SFX_JUMP		sfx_jump_psg
#define SFX_CLOTHES		sfx_shirt_psg
#define SFX_PLAYER_HIT	sfx_kill_psg
#define SFX_COIN		sfx_coins_psg
#define SFX_TIC_TOC		sfx_select_psg
#define SFX_LAST_COIN	sfx_start_psg
#define SFX_SPIKE		sfx_kill_psg
#define SFX_FANTY		sfx_fanty_psg
#define SFX_NINTENDONT	sfx_select_psg

// Sound channels

#define SC_PLAYER		0
#define SC_ENEMS		1
#define SC_LEVEL		2

// Conveyors animated tiles address

#define VDP_ADDR_CONVEYOR_LEFT		((256+26)<<5)
#define VDP_ADDR_CONVEYOR_RIGHT		((256+27)<<5)
