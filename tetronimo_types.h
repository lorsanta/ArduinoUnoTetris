#ifndef TETRONIMO_TYPES_H
#define TETRONIMO_TYPES_H

#define TETR_I_SIZE    1
#define TETR_I2_SIZE   4
#define TETR_O_SIZE    2
#define TETR_T_SIZE    3
#define TETR_T2_SIZE   2
#define TETR_T4_SIZE   2
#define TETR_L_SIZE    3
#define TETR_L2_SIZE   2
#define TETR_L4_SIZE   2
#define TETR_J_SIZE    3
#define TETR_J2_SIZE   2
#define TETR_J4_SIZE   2
#define TETR_Z_SIZE    3
#define TETR_Z2_SIZE   2
#define TETR_S_SIZE    3
#define TETR_S2_SIZE   2


#define ROTATED_TETR_I   2
#define ROTATED_TETR_O   1
#define ROTATED_TETR_T   4
#define ROTATED_TETR_L   4
#define ROTATED_TETR_J   4
#define ROTATED_TETR_Z   2
#define ROTATED_TETR_S   2

#define TETR_I_R1_HEIGHT   4
#define TETR_I_R2_HEIGHT   1
#define TETR_O_R1_HEIGHT   2
#define TETR_T_R1_HEIGHT   2
#define TETR_T_R2_HEIGHT   3
#define TETR_T_R3_HEIGHT   2
#define TETR_T_R4_HEIGHT   3
#define TETR_L_R1_HEIGHT   2
#define TETR_L_R2_HEIGHT   3
#define TETR_L_R3_HEIGHT   2
#define TETR_L_R4_HEIGHT   3
#define TETR_J_R1_HEIGHT   2
#define TETR_J_R2_HEIGHT   3
#define TETR_J_R3_HEIGHT   2
#define TETR_J_R4_HEIGHT   3
#define TETR_Z_R1_HEIGHT   2
#define TETR_Z_R2_HEIGHT   3
#define TETR_S_R1_HEIGHT   2
#define TETR_S_R2_HEIGHT   3

byte tetr_I_r1[TETR_I_SIZE] = {
  B01111
};

byte tetr_I_r2[TETR_I2_SIZE] = {
  B00001,
  B00001,
  B00001,
  B00001
};

byte tetr_O_r1[TETR_O_SIZE] = {
  B00011,
  B00011
};

byte tetr_T_r1[TETR_T_SIZE] = {
  B00001,
  B00011,
  B00001
};

byte tetr_T_r2[TETR_T2_SIZE] = {
  B00010,
  B00111
};

byte tetr_T_r3[TETR_T_SIZE] = {
  B00010,
  B00011,
  B00010
};

byte tetr_T_r4[TETR_T4_SIZE] = {
  B00111,
  B00010
};

byte tetr_L_r1[TETR_L_SIZE] = {
  B00011,
  B00001,
  B00001
};

byte tetr_L_r2[TETR_L_SIZE] = {
  B00001,
  B00111
};

byte tetr_L_r3[TETR_L_SIZE] = {
  B00010,
  B00010,
  B00011
};

byte tetr_L_r4[TETR_L_SIZE] = {
  B00111,
  B00100
};

byte tetr_J_r1[TETR_J_SIZE] = {
  B00001,
  B00001,
  B00011
};

byte tetr_J_r2[TETR_J_SIZE] = {
  B00100,
  B00111
};

byte tetr_J_r3[TETR_J_SIZE] = {
  B00011,
  B00010,
  B00010
};

byte tetr_J_r4[TETR_J_SIZE] = {
  B00111,
  B00001
};



byte tetr_Z_r1[TETR_Z_SIZE] = {
  B00001,
  B00011,
  B00010
};

byte tetr_Z_r2[TETR_Z_SIZE] = {
  B00110,
  B00011,
  B00000
};

byte tetr_S_r1[TETR_S_SIZE] = {
  B00010,
  B00011,
  B00001
};

byte tetr_S_r2[TETR_S_SIZE] = {
  B00011,
  B00110,
  B00000
};

byte* ptetr_I[MAX_SIZE_TETRONIMO] = {tetr_I_r1, tetr_I_r2, 0, 0};
byte* ptetr_O[MAX_SIZE_TETRONIMO] = {tetr_O_r1, 0, 0, 0};
byte* ptetr_T[MAX_SIZE_TETRONIMO] = {tetr_T_r1, tetr_T_r2, tetr_T_r3, tetr_T_r4};
byte* ptetr_L[MAX_SIZE_TETRONIMO] = {tetr_L_r1, tetr_L_r2, tetr_L_r3, tetr_L_r4};
byte* ptetr_J[MAX_SIZE_TETRONIMO] = {tetr_J_r1, tetr_J_r2, tetr_J_r3, tetr_J_r4};
byte* ptetr_Z[MAX_SIZE_TETRONIMO] = {tetr_Z_r1, tetr_Z_r2, 0, 0};
byte* ptetr_S[MAX_SIZE_TETRONIMO] = {tetr_S_r1, tetr_S_r2, 0, 0};

byte tetr_I_height[MAX_SIZE_TETRONIMO] = {TETR_I_R1_HEIGHT, TETR_I_R2_HEIGHT, 0, 0};
byte tetr_O_height[MAX_SIZE_TETRONIMO] = {TETR_O_R1_HEIGHT, 0, 0, 0};
byte tetr_T_height[MAX_SIZE_TETRONIMO] = {TETR_T_R1_HEIGHT, TETR_T_R2_HEIGHT, TETR_T_R3_HEIGHT, TETR_T_R4_HEIGHT};
byte tetr_L_height[MAX_SIZE_TETRONIMO] = {TETR_L_R1_HEIGHT, TETR_L_R2_HEIGHT, TETR_L_R3_HEIGHT, TETR_L_R4_HEIGHT};
byte tetr_J_height[MAX_SIZE_TETRONIMO] = {TETR_J_R1_HEIGHT, TETR_J_R2_HEIGHT, TETR_J_R3_HEIGHT, TETR_J_R4_HEIGHT};
byte tetr_Z_height[MAX_SIZE_TETRONIMO] = {TETR_Z_R1_HEIGHT, TETR_Z_R2_HEIGHT, 0, 0};
byte tetr_S_height[MAX_SIZE_TETRONIMO] = {TETR_S_R1_HEIGHT, TETR_S_R2_HEIGHT, 0, 0};

byte tetr_I_size[MAX_SIZE_TETRONIMO] = {TETR_I_SIZE, TETR_I2_SIZE, 0, 0};
byte tetr_O_size[MAX_SIZE_TETRONIMO] = {TETR_O_SIZE, 0, 0, 0};
byte tetr_T_size[MAX_SIZE_TETRONIMO] = {TETR_T_SIZE, TETR_T2_SIZE, TETR_T_SIZE, TETR_T4_SIZE};
byte tetr_L_size[MAX_SIZE_TETRONIMO] = {TETR_L_SIZE, TETR_L2_SIZE, TETR_L_SIZE, TETR_L4_SIZE};
byte tetr_J_size[MAX_SIZE_TETRONIMO] = {TETR_J_SIZE, TETR_J2_SIZE, TETR_J_SIZE, TETR_J4_SIZE};
byte tetr_Z_size[MAX_SIZE_TETRONIMO] = {TETR_Z_SIZE, TETR_Z2_SIZE, 0, 0};
byte tetr_S_size[MAX_SIZE_TETRONIMO] = {TETR_S_SIZE, TETR_S2_SIZE, 0, 0};

byte tetr_null[MAX_SIZE_TETRONIMO] = {0, 0, 0, 0};

#endif
