#include "playfield.h"
#include "graphics.h"
#include "types.h"
#include "playfield_utils.h"

// Atari specific includes next
#include <atari.h>

// Standard C includes
#include <unistd.h>
#include <string.h>

#define COLOR_CLOCK_BUFF 4

#pragma bss-name (push,"PLAYFIELD")
byte playfield[PF_PAGE_ROWS * PF_ROW_TILES][PF_PAGE_COLS * PF_COL_TILES];
#pragma bss-name (pop)

// A description about the "playfield":
// There are PF_PAGE_ROWS x PF_PAGE_COLS pages in the playfield.
// Each page consists of PF_ROW_TILES x PF_COL_TILES tiles.
// Each tile is PF_ROW_PIX x PF_COL_PIX in pixels.
// A line is a pixel in row space, and a col (maybe horrible name) is a pixel in col space.

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
    // Working variables
    byte dl_row;

    // Course scroll indecies
    u_short p_row;
    u_short p_col;

    // Maybe perform some bounds check in here?
    
    p_row = line / PF_ROW_PIX;
    p_col = col  / PF_COL_PIX;

    // Check if we need to perform a course scroll
    if(*((u_short*)&DL[4]) != (u_short)&playfield[p_row][p_col]) {
        // Course scroll
        for(dl_row = 0; dl_row < PF_ROW_TILES; ++dl_row)
            *((u_short*)&DL[(dl_row * 3 + 1) + 3]) = (u_short)&playfield[p_row + dl_row][p_col];

        // Last line is the buffer line
        *((u_short*)&DL[(dl_row * 3 + 1) + 3]) = (u_short)&playfield[p_row + dl_row][p_col];
    }

    // Fine scroll
    ANTIC.vscrol = line % PF_ROW_PIX;
    ANTIC.hscrol = PF_COL_PIX - (col % PF_COL_PIX);

    //
    //wait_for_sync();
}
