#include <stdio.h>
#include <stdint.h>

#define CODE_FLA_BEGIN \
__asm__(\
   "sti \n"\
   "sti \n"\
   "sti \n"\
   "nop \n"\
   "hlt \n"\
)

#define CODE_FLA_END \
__asm__(\
   "cli \n"\
   "cli \n"\
   "cli \n"\
   "nop \n"\
   "hlt \n"\
);

//

int main() {

    CODE_FLA_BEGIN;

    printf("Hello, World ! \n");

    CODE_FLA_END;

    return 1;
}

