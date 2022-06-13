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

//#define USE_IMMEDIATE_ADDRESSING
#ifdef USE_IMMEDIATE_ADDRESSING

#pragma bss-name (push,"PLAYFIELD")
byte playfield[PF_COURSE_ROWS][PF_COURSE_COLS];
#pragma bss-name (pop)

#pragma data-name(push,"ZEROPAGE")
byte* ul_addr_tmp = &playfield[0][0];
byte* row_addr = 0x0000;
byte scroll_flag = 0x00; // goes into ZEROPAGE
byte h_fs = 0x00;        // horizontal fine scroll
byte v_fs = 0x00;        // vertical fine scroll
#pragma data-name(pop)
u_short line_r, col_r;
byte* ul_addr = &playfield[0][0];
byte num_rows = PF_COURSE_ROWS / (4096 / PF_COURSE_COLS);

void init_playfield()
{
    u_short page_row = 0, page_col, row;

    setup_vbi();

    // Initialize memory
    for(page_row = 0; page_row < PF_PAGE_ROWS; ++page_row)
    {
        for(page_col = 0; page_col < PF_PAGE_COLS; ++page_col)
        {
            for(row = 0; row < PF_ROW_TILES-1; ++row) {
                memset((void*)&playfield[page_row * PF_ROW_TILES + row][page_col * PF_COL_TILES],
                       (int)'a' + page_row * PF_PAGE_COLS + page_col,
                       (size_t)PF_COL_TILES);

                playfield[page_row * PF_ROW_TILES + row][page_col * PF_COL_TILES + (PF_COL_TILES-1)] = (byte)'|';        
            }

            memset((void*)&playfield[page_row * PF_ROW_TILES + row][page_col * PF_COL_TILES],
                    (int)'?',
                    (size_t)PF_COL_TILES-1);
        }
    }
}

void scroll_playfield(u_short line, u_short col)
{
    // Local temporaries.  Values get copied when we have a lock on the memory accessed by the VBI.
    byte h_cs, v_cs, h_fs_lcl, v_fs_lcl;
    //u_short col_lcl;
    //byte* ul_addr_lcl;

    //col_lcl = col + (4*16);
    //col = col + (4*16);

    // Put some bounds on the coordinates
    if(line >= (PF_LINES - PF_LINES_PER_PAGE))
        line = PF_LINES - PF_LINES_PER_PAGE;

    if(col >= (PF_COLS - PF_COLS_PER_PAGE))
        col = PF_COLS - PF_COLS_PER_PAGE;

    // Course scroll coordinates
    v_cs = (byte)(line / (u_short)PF_ROW_PIX);
    h_cs = (byte)(col  / (u_short)PF_COL_PIX);

    // Fine scroll coordinates
    v_fs_lcl = (byte)(line % (u_short)PF_ROW_PIX); 
    h_fs_lcl = PF_COL_PIX - (byte)(col %  (u_short)PF_COL_PIX);

    // Update the memory locations used by the VBI so it can update
    // the display lists (for course scroll) and fine scroll memory locations.
    // Keep the VBI from reading the coordinates while we write them.
    scroll_flag = 0xFF;

    v_fs = v_fs_lcl; 
    h_fs = h_fs_lcl;

    ul_addr = &playfield[v_cs][h_cs];
    row_addr = &playfield[v_cs][0];
    
    scroll_flag = 0x00;  // Allow the VBI to update the DL and scroll var's
}

#else

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
#pragma bss-name (pop)

void init_playfield()
{
    u_short page_row = 0, page_col, row;
    int i;

    // Initialize the address LUT
    address_lut[0] = (byte*)playfield;

    for(i = 1; i < PF_COURSE_ROWS; ++i)
    {
        u_short addr = (u_short)(address_lut[i-1]) + (u_short)PF_COURSE_COLS;
        u_short addr_next = (u_short)addr + (u_short)PF_COURSE_COLS;

        if(addr_next % 0x1000 < (u_short)PF_COURSE_COLS)
            addr = addr_next & 0xFF00;

        address_lut[i] = addr;
    }

    // Initialize memory
    for(page_row = 0; page_row < PF_PAGE_ROWS; ++page_row)
    {
        for(page_col = 0; page_col < PF_PAGE_COLS; ++page_col)
        {
            for(row = 0; row < PF_ROW_TILES-1; ++row) {
                memset((void*)&playfield[page_row * PF_ROW_TILES + row][page_col * PF_COL_TILES],
                       (int)'a' + page_row * PF_PAGE_COLS + page_col,
                       (size_t)PF_COL_TILES);

                playfield[page_row * PF_ROW_TILES + row][page_col * PF_COL_TILES + (PF_COL_TILES-1)] = (byte)'|';        
            }

            memset((void*)&playfield[page_row * PF_ROW_TILES + row][page_col * PF_COL_TILES],
                    (int)'?',
                    (size_t)PF_COL_TILES-1);
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
#endif
