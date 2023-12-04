#include <stdio.h>
#include <stdint.h>

#include "vxlib_signature.h"

//

int main() {

    VL_CODE_FLATTENING_SIG_BEGIN;

    printf("Hello, Obfuscator ! \n");

    VL_CODE_FLATTENING_SIG_END;

    //

    VL_CODE_FLATTENING_SIG_LV1_BEGIN;

    printf("Hello, Obfuscator: 1 ! \n");

    VL_CODE_FLATTENING_SIG_LV1_END;

    //

    VL_CODE_FLATTENING_SIG_LV2_BEGIN;

    printf("Hello, Obfuscator: 2 ! \n");

    VL_CODE_FLATTENING_SIG_LV2_END;

    //

    VL_CODE_FLATTENING_SIG_LV3_BEGIN;

    printf("Hello, Obfuscator: 3 ! \n");

    VL_CODE_FLATTENING_SIG_LV3_END;

    //

    VL_VIRTUALIZATION_SIG_BEGIN;

    printf("Hello, Virtualizer ! \n");

    VL_VIRTUALIZATION_SIG_END;

    return 1;
}

