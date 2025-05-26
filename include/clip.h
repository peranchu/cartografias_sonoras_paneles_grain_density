
/*
              _ _______
    /\        | |__   __|
   /  \   _ __| |_ | | ___  ___
  / /\ \ | '__| __|| |/ _ \/ __|
 / ____ \| |  | |_ | |  __/ (__
/_/    \_\_|   \__||_|\___|\___|

CARTOGRAFÍAS SONORAS
Honorino García Mayo 2025

Panel Gestión GRAIN DENSITY
"clip.h"
Comprueba si es mayor que el máximo o menor que el mínimo
*/

int clipValue(int in, int minVal, int maxVal)
{
    int out;

    minVal++;

    if (in > maxVal)
    {
        out = maxVal;
    }
    else if (in < minVal)
    {
        out = minVal - 1;
    }
    else
    {
        out = in;
    }
    return out;
}