// ***
//  *
//
int t_0[3][3] = {{1, 1, 1}, {0, 1, 0}, {0, 0, 0}};

// *
// **
// *
int t_90[3][3] = {{1, 0, 0}, {1, 1, 0}, {1, 0, 0}};
//  *
// ***
int t_180[3][3] = {{0, 0, 0}, {0, 1, 0}, {1, 1, 1}};
//   *
//  **
//   *
int t_270[3][3] = {{0, 0, 1}, {0, 1, 1}, {0, 0, 1}};

// Contains all rotations of a t block
int t_rotations[4][3][3] = {t_0, t_90, t_180, t_270};

// *
// *
// **
int l_0[3][3] = {{1, 0, 0}, {1, 0, 0}, {1, 1, 0}};
// ***
// *
int l_90[3][3] = {{0, 0 ,0}, {1, 1, 1}, {1, 0, 0}};
//  **
//   *
//   *
int l_180[3][3] = {{0, 1, 1}, {0, 0, 1}, {0, 0, 1}};
//   *
// ***
int l_270[3][3] = {{0, 0 ,0}, {0, 0, 1}, {1, 1, 1}};

// Contains all rotations of a l block
int l_rotations[4][3][3] = {l_0, l_90, l_180, l_270};

// *
// ***
int j_0[3][3] = {{0, 0 ,0}, {1, 0, 0}, {1, 1, 1}};
// **
// *
// *
int j_90[3][3] = {{1, 1, 0}, {1, 0, 0}, {1, 0, 0}};
// ***
//   *
int j_180[3][3] = {{0, 0, 0}, {1, 1, 1}, {0, 0, 1}};
//  **
//   *
//   *
int j_270[3][3] = {{0, 1, 1}, {0, 0, 1}, {0, 0, 1}};

//Contains all j blocks.
int j_rotations[4][3][3] = {j_0, j_90, j_180, j_270};

// **
//  **
int z_0[3][3] = {{0, 0, 0}, {1, 1, 0}, {0, 1, 1}};
//  *
// **
// *
int z_90[3][3] = {{0, 1, 0}, {1, 1, 0}, {1, 0, 0}};

// Contains all z blocks.
int z_rotations[4][3][3] = {z_0, z_90, z_0, z_90};

//  **
// **
int s_0[3][3] = {{0, 0, 0}, {0, 1, 1}, {1, 1, 0}};
// *
// **
//  *
int s_90[3][3] = {{1, 0, 0}, {1, 1, 0}, {0, 1, 0}};

// Contains all z blocks
int s_rotations[4][3][3] = {s_0, s_90, s_0, s_90};

// **
// **
int o_block[3][3] = {{0, 0, 0}, {1, 1, 0}, {1, 1, 0}};

// Use this block 4 times for all rotations
int o_rotations[4][3][3] = {o_block, o_block, o_block, o_block};

// ***
//
//
int i_0[3][3] = {{0, 0, 0}, {0, 0, 0}, {1, 1, 1}};
// *
// *
// *
int i_90[3][3] = {{0, 0, 1}, {0, 0, 1}, {0, 0, 1}};
//
//
// ***
int i_180[3][3] = {{1, 1, 1}, {0, 0, 0}, {0, 0, 0}};
//   *
//   *
//   *
int i_270[3][3] = {{1, 0, 0}, {1, 0, 0}, {1, 0, 0}};

// Contains all i block rotations
int i_rotations = {i_0, i_90, i_180, i_270};

//int blocks[7][4][3][3] = {t_rotations, l_rotations, j_rotations, z_rotations, s_rotations, o_rotations, i_rotations};
