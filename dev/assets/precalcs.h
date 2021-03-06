const unsigned char random_seq [] = {
	177, 198, 88, 157, 122, 240, 194, 36, 196, 13, 
	170, 87, 113, 218, 180, 203, 229, 233, 155, 154, 
	214, 192, 184, 118, 101, 231, 146, 243, 225, 117, 
	140, 248, 68, 3, 221, 15, 22, 107, 39, 144, 
	34, 210, 199, 46, 25, 44, 72, 111, 133, 201, 
	250, 66, 234, 103, 11, 38, 20, 79, 247, 237, 
	100, 35, 109, 148, 106, 187, 12, 116, 160, 59, 
	212, 58, 19, 120, 74, 71, 33, 253, 254, 165, 
	197, 156, 167, 145, 92, 223, 193, 206, 190, 174, 
	45, 137, 255, 98, 40, 31, 51, 230, 136, 1, 
	42, 175, 9, 55, 14, 246, 112, 108, 169, 10, 
	215, 209, 151, 2, 110, 238, 202, 86, 67, 239, 
	143, 213, 47, 96, 63, 245, 29, 159, 186, 127, 
	241, 76, 30, 7, 129, 224, 164, 90, 217, 172, 
	131, 236, 32, 130, 75, 123, 141, 185, 89, 152, 
	23, 227, 235, 78, 52, 150, 26, 64, 138, 94, 
	222, 8, 49, 183, 249, 200, 228, 70, 73, 4, 
	195, 179, 85, 211, 181, 5, 80, 84, 82, 132, 
	139, 61, 188, 252, 124, 147, 28, 102, 77, 244, 
	60, 216, 41, 125, 62, 176, 207, 16, 24, 48, 
	93, 178, 115, 135, 166, 54, 162, 83, 57, 142, 
	50, 219, 27, 81, 208, 6, 21, 43, 65, 168, 
	91, 153, 53, 173, 182, 18, 171, 104, 121, 205, 
	69, 226, 95, 158, 251, 191, 134, 128, 56, 163, 
	99, 242, 126, 119, 149, 220, 232, 114, 105, 37, 
	0, 161, 189, 17, 204, 97
};

const unsigned char jitter [] = {
	0,1,1,0,0,1,0,1,1,0,0,0,1,0,1,1
};

const unsigned char monococo_state_times [] = {
	BASE_TIME_HIDDEN, BASE_TIME_APPEARING, BASE_TIME_ONBOARD, BASE_TIME_APPEARING
};

const unsigned char monococo_metasprite [] = {
	84, 0, 1, 0
};

const unsigned char shl4 [] = {
	0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xa0, 0xb0, 0xc0, 0xd0, 0xe0, 0xf0, 0x00
};

const unsigned char shr4 [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
	0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
	0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 
	0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 
	0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
	0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 
	0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 
	0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 
	0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
	0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 
	0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 
	0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f
};

const unsigned char pal_cycle_desert [] = {
	0x1f, 0x1b, 0x1a, 0x1f
};

const unsigned char pal_cycle_waterfall [] = {
	0x34, 0x34, 0x38, 0x3E, 0x3F, 0x3E, 0x38, 0x34
	//0x34, 0x28, 0x3D, 0x34, 0x34, 0x38, 0x3E, 0x34
};

const unsigned char fbl_incr_x [] = {
	0x02, 0x03, 0x02, 0x03, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 
	0x02, 0x02, 0x02, 0x01, 0x02, 0x02, 0x01, 0x02, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x01, 0x02, 
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 
	0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char fbl_incr_y [] = {
	0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 
	0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 
	0x01, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x01, 0x01, 0x02, 0x01, 0x02, 0x01, 0x01, 
	0x02, 0x02, 0x01, 0x02, 0x01, 0x02, 0x02, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x02
};
