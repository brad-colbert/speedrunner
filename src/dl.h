#ifndef __SR_DL_H__
#define __SR_DL_H__

#include <atari.h>

//extern byte playfield[];
extern byte playfield[96][160];

#ifdef GFX7
void DISPLAY_LIST_GFX7 =
{
    DL_BLK8,
    DL_BLK8,
    DL_BLK8,

    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0000, // GFX 7, ANTIC D @ mem 0x3000
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0050,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x00A0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x00F0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0140,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0190,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x01E0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0230,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0280,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x02D0, // Ln 10,  33 bytes

    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0320,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0370,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x03C0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0410,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0460,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x04B0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0500,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0550,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x05A0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x05F0, // Ln 20,  33 bytes

    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0640,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0690,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x06E0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0730,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0780,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x07D0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0820,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0870,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x08C0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0910, // Ln 30,  33 bytes

    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0960,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x09B0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0A00,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0A50,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0AA0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0AF0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0B40,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0B90,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0BE0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0C30, // Ln 40,  33 bytes

    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0C80,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0CD0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0D20,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0D70,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0DC0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0E10,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0E60,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0EB0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0F00,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0F50, // Ln 50,  33 bytes

    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x0FA0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1000, // 0x1000 boundary
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1050,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x10A0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x10F0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1140,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1190,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x11E0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1230,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1280, // Ln 60,  33 bytes

    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x12D0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1320,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1370,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x13C0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1410,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1460,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x14B0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1500,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1550,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x15A0, // Ln 70,  33 bytes

    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x15F0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1640,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1690,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x16E0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1730,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1780,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x17D0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1820,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1870,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x18C0, // Ln 80,  33 bytes

    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1910,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1960,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x19B0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1A00,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1A50,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1AA0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1AF0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1B40,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1B90,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1BE0, // Ln 90,  33 bytes

    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1C30,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1C80,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1CD0,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1D20,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1D70,
    DL_LMS(DL_MAP160x2x4),  &playfield[0][0]+ 0x1DC0, // Ln 96,  33 bytes

    DL_JVB, &DISPLAY_LIST_GFX7      // 33 bytes
};
#else
void DISPLAY_LIST_ANTIC4 =
{
    DL_BLK8,
    DL_BLK8,
    DL_BLK8,
//DL_HSCROL(
    DL_LMS(DL_VSCROL(DL_HSCROL(DL_CHR40x8x4))),  &playfield[0][0]+ 0x0000, // ANTIC 4
    DL_LMS(DL_VSCROL(DL_HSCROL(DL_CHR40x8x4))),  &playfield[0][0]+ 0x00A0,
    DL_LMS(DL_VSCROL(DL_HSCROL(DL_CHR40x8x4))),  &playfield[0][0]+ 0x0140,
    DL_LMS(DL_VSCROL(DL_HSCROL(DL_CHR40x8x4))),  &playfield[0][0]+ 0x01E0,
    DL_LMS(DL_VSCROL(DL_HSCROL(DL_CHR40x8x4))),  &playfield[0][0]+ 0x0280,
    DL_LMS(DL_VSCROL(DL_HSCROL(DL_CHR40x8x4))),  &playfield[0][0]+ 0x0320,
    DL_LMS(DL_VSCROL(DL_HSCROL(DL_CHR40x8x4))),  &playfield[0][0]+ 0x03C0,
    DL_LMS(DL_VSCROL(DL_HSCROL(DL_CHR40x8x4))),  &playfield[0][0]+ 0x0460,
    DL_LMS(DL_VSCROL(DL_HSCROL(DL_CHR40x8x4))),  &playfield[0][0]+ 0x0500,
    DL_LMS(DL_VSCROL(DL_HSCROL(DL_CHR40x8x4))),  &playfield[0][0]+ 0x05A0, // Ln 10,  33 bytes

    DL_LMS(DL_VSCROL(DL_HSCROL(DL_CHR40x8x4))),  &playfield[0][0]+ 0x0640,
    DL_LMS(DL_VSCROL(DL_HSCROL(DL_CHR40x8x4))),  &playfield[0][0]+ 0x06E0,
    DL_LMS(DL_VSCROL(DL_HSCROL(DL_CHR40x8x4))),  &playfield[0][0]+ 0x0780,
    DL_LMS(DL_VSCROL(DL_HSCROL(DL_CHR40x8x4))),  &playfield[0][0]+ 0x0820,
    DL_LMS(DL_VSCROL(DL_HSCROL(DL_CHR40x8x4))),  &playfield[0][0]+ 0x08C0,
    DL_LMS(DL_VSCROL(DL_HSCROL(DL_CHR40x8x4))),  &playfield[0][0]+ 0x0960,
    DL_LMS(DL_VSCROL(DL_HSCROL(DL_CHR40x8x4))),  &playfield[0][0]+ 0x0A00,
    DL_LMS(DL_VSCROL(DL_HSCROL(DL_CHR40x8x4))),  &playfield[0][0]+ 0x0AA0,
    DL_LMS(DL_VSCROL(DL_HSCROL(DL_CHR40x8x4))),  &playfield[0][0]+ 0x0B40,
    DL_LMS(DL_VSCROL(DL_HSCROL(DL_CHR40x8x4))),  &playfield[0][0]+ 0x0BE0, // Ln 20,  63 bytes

    DL_LMS(DL_VSCROL(DL_HSCROL(DL_CHR40x8x4))),  &playfield[0][0]+ 0x0C80,
    DL_LMS(DL_VSCROL(DL_HSCROL(DL_CHR40x8x4))),  &playfield[0][0]+ 0x0D20,
    DL_LMS(DL_VSCROL(DL_HSCROL(DL_CHR40x8x4))),  &playfield[0][0]+ 0x0DC0,
    DL_LMS(DL_VSCROL(DL_HSCROL(DL_CHR40x8x4))),  &playfield[0][0]+ 0x0E60, // Ln 24,  75 bytes

    DL_JVB, &DISPLAY_LIST_ANTIC4      // 78 bytes
};
#endif

#endif // __SR_DL_H__


























































































