#ifndef __PIC_PROCESS_H
#define __PIC_PROCESS_H
#include "sys.h"

#define V 120
#define H 120
#define THRESHOLD 0x6a


void Image_Binaryzation(void);
void Image_Filter(void);


u8 get_horizontal(void);
u8 get_row(void);

#endif
