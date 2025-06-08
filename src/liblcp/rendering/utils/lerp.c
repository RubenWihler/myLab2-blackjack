#include "lerp.h"

/// @brief Interpolation lineaire entre deux entiers
/// @param start Valeur de depart
/// @param end Valeur de fin
/// @param t Parametre d'interpolation entre 0 et 1
/// @return Valeur interpolee
uint16_t lerp(const uint16_t start, const uint16_t end, const float t)
{
    return (uint16_t)((1 - t) * start + t * end);
}

/// @brief Interpolation lineaire entre deux couleurs dans le format RGB565
/// @param start Couleur de depart
/// @param end Couleur de fin
/// @param t Parametre d'interpolation entre 0 et 1
/// @return Couleur interpolee
uint16_t lerp_color(const uint16_t start, const uint16_t end, const float t)
{
    uint16_t r_start = (start >> 11) & 0x1F;
    uint16_t g_start = (start >> 5) & 0x3F;
    uint16_t b_start = start & 0x1F;

    uint16_t r_end = (end >> 11) & 0x1F;
    uint16_t g_end = (end >> 5) & 0x3F;
    uint16_t b_end = end & 0x1F;

    uint16_t r = lerp(r_start, r_end, t);
    uint16_t g = lerp(g_start, g_end, t);
    uint16_t b = lerp(b_start, b_end, t);

    return (r << 11) | (g << 5) | b;
}
