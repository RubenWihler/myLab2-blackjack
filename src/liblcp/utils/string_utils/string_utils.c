#include "string_utils.h"
#include <stdlib.h>

//j'ai essayer pas moi meme, j'ai pas reussi :(
//ducoup merci chatgpt
//lien de la dicsussion: https://chatgpt.com/share/68420357-2878-800a-95a9-ebd31d846256


char* str_from_uint16(uint16_t n)
{
    const int max_digits = 5 + 1;
    char buffer[max_digits];
    int i = max_digits - 1;
    buffer[i] = '\0';

    do {
        buffer[--i] = '0' + (n % 10);
        n /= 10;
    } while (n > 0);

    // Alloue juste la taille nécessaire pour la chaîne
    const int len = max_digits - i;
    char *result = malloc(len * sizeof(char));
    if (!result) return NULL;

    for (int j = 0; j < len; j++) {
        result[j] = buffer[i + j];
    }

    return result;
}


char* str_from_uint64(uint64_t n)
{
    const int max_digits = 20 + 1; // 20 chiffres max pour uint64_t + 1 pour '\0'
    char buffer[max_digits];
    int i = max_digits - 1;
    buffer[i] = '\0';

    // Construction à l'envers dans le buffer temporaire
    do {
        buffer[--i] = '0' + (n % 10);
        n /= 10;
    } while (n > 0);

    // Calcul de la longueur réelle de la chaîne
    int len = max_digits - i;
    char *result = malloc(len * sizeof(char));
    if (!result) return NULL;

    // Copie dans le buffer alloué dynamiquement
    for (int j = 0; j < len; j++) {
        result[j] = buffer[i + j];
    }

    return result;
}
