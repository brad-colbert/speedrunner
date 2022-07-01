#include "playfield.h"
#include "graphics.h"
#include "types.h"
#include "playfield_utils.h"

// Atari specific includes next
#include <atari.h>
#include <conio.h>

// Standard C includes
#include <unistd.h>
#include <string.h>

#define COLOR_CLOCK_BUFF 4

// A description about the "playfield":
// There are PF_PAGE_ROWS x PF_PAGE_COLS pages in the playfield.
// Each page consists of PF_ROW_TILES x PF_COL_TILES tiles.
// Each tile is PF_ROW_PIX x PF_COL_PIX in pixels.
// A line is a pixel in row space, and a col (maybe horrible name) is a pixel in col space.

#pragma data-name(push,"ZEROPAGE")
byte scroll_flag = 0x00; // goes into ZEROPAGE
byte col = 0x00;         // course scroll playfield row byte offset
byte row = 0x00;         // course scroll playfield address LUT index
byte h_fs = 0x00;        // horizontal fine scroll
byte v_fs = 0x00;        // vertical fine scroll
#pragma data-name(pop)

// There could be an issue where adding the number of skip lines to the
// playfield buffer makes you cross another 4K boundary... we'll deal with
// that later.
#define NUM_ROWS_TO_SKIP (PF_COURSE_ROWS / (4096 / PF_COURSE_COLS))

#pragma bss-name (push,"PLAYFIELD")
byte* address_lut[PF_COURSE_ROWS];
byte playfield[PF_COURSE_ROWS + NUM_ROWS_TO_SKIP][PF_COURSE_COLS];
u_short pf_x, pf_y;
#pragma bss-name (pop)

// Convert an address to text hex and stores those chars
// add a destination address.
void addr_to_hex_to_addr(byte* src, byte* dst)
{
    //char lut[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    char lut[] = {16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 33, 34, 35, 36, 37, 38};
    u_short src_s = (u_short)src;
    byte ival = 0x00;
    byte value = 0x00;

    // First char
    ival = (byte)(src_s >> 8);
    value = (ival & 0xF0) >> 4;
    *(dst + 3) = lut[value];

    // Second char
    value = ival & 0x0F;
    *(dst + 4) = lut[value];

    // Third char
    ival = (byte)(src_s & 0x00FF);
    value = (ival & 0xF0) >> 4;
    *(dst + 5) = lut[value];

    // Fourth char
    value = ival & 0x0F;
    *(dst + 6) = lut[value];
}

void init_playfield()
{
    int i;

    // Initialize the address LUT
    address_lut[0] = (byte*)playfield;

    for(i = 1; i < PF_COURSE_ROWS; ++i)
    {
        u_short addr = (u_short)(address_lut[i-1]) + (u_short)PF_COURSE_COLS;
        u_short addr_next = (u_short)addr + (u_short)PF_COURSE_COLS;

        if(addr_next % 0x1000 < (u_short)PF_COURSE_COLS)
            addr = addr_next & 0xFF00;

        address_lut[i] = (byte*)addr;
    }

    for(row = 0; row < PF_COURSE_ROWS; ++row)
    {
        for(col = 0; col < PF_COURSE_COLS; col+=40)
        {
            byte* addr = address_lut[row] + col;
            addr_to_hex_to_addr(addr, addr);
        }
    }

    setup_vbi();
}

// X and Y specify the upper left hand corner of the viewable
// portion of the playfield.  These are in pixel space which
// is implemented using fine scrolling to move to the specific
// upper left position.
void scroll_playfield(u_short x, u_short y)
{
    byte h_fs_lcl, v_fs_lcl, col_lcl, row_lcl;

    pf_x = x;
    pf_y = y;

    // Fine scroll coordinates
    h_fs_lcl = PF_COL_PIX - (byte)(x %  (u_short)PF_COL_PIX);
    v_fs_lcl = (byte)(y % (u_short)PF_ROW_PIX); 

    // Course scroll coordinates are used to select the byte level
    // memory location of the playfield.
    col_lcl = (byte)(x  / (u_short)PF_COL_PIX);
    row_lcl = (byte)(y / (u_short)PF_ROW_PIX);

    // Update the memory locations used by the VBI so it can update
    // the display lists (for course scroll) and fine scroll memory locations.
    // Keep the VBI from reading the coordinates while we write them.
    scroll_flag = 0xFF;

    col = col_lcl;
    row = row_lcl;

    h_fs = h_fs_lcl;
    v_fs = v_fs_lcl; 

    scroll_flag = 0x00;  // Allow the VBI to update the DL and scroll var's
}
