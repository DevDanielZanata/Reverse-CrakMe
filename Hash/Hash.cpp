#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <cstdint>


int __cdecl hash(int8_t* a1)
{
    signed char* v1; // eax
    int v3; // [esp+Ch] [ebp-4h]

    v3 = -1515870811;

    for (int i = 0; i < 4; i++)
    {
        v1 = a1++;
        v3 = 31 * v3 + *v1;
    }

    return v3;
}


int main() {
    //char s[24];
    int8_t s[4]{ 0 };
    int32_t c_hash = 1770989405;
    printf("==========================================\n");
    printf("|--------Realizando o Brute Force--------|\n");
    printf("==========================================\n");
    printf("\n");
    printf("Carregando...\n");


    for (int i = 0; i <= INT_MAX; i++) {
   
    
        s[0] = (int8_t)((i >> 24) & 0xFF); 
        s[1] = (int8_t)((i >> 16) & 0xFF); 
        s[2] = (int8_t)((i >> 8) & 0xFF); 
        s[3] = (int8_t)(i & 0xFF);         

        int h = hash(s);


        if (h == c_hash) {
            printf("Hash Encontrada: \n");
            printf("Hash = %02X\nNumero Correspondente [%d]\n", h, i);
            return 0;  
        }
    }
    printf("Nenhum Valor Encontrado!");

    return 0;
}
