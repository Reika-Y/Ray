#include "Perlin.h"

Vector3* Perlin::ranvec = PerlinGenerate();
int* Perlin::perm_x = PerlinGeneratePerm();
int* Perlin::perm_y = PerlinGeneratePerm();
int* Perlin::perm_z = PerlinGeneratePerm();
