#include "playfield.h"
#include "graphics.h"
#include "types.h"

// Atari specific includes next
#include <atari.h>

// Standard C includes
#include <unistd.h>
#include <string.h>

#pragma bss-name (push,"PLAYFIELD")
byte playfield[PF_PAGE_ROWS * PF_ROW_TILES][PF_PAGE_COLS * PF_COL_TILES];
#pragma bss-name (pop)

void init_playfield()
{
    unsigned short page_row = 0, page_col, row;

    // Initialize memory
    for(page_row = 0; page_row < PF_PAGE_ROWS; ++page_row)
    {
        for(page_col = 0; page_col < PF_PAGE_COLS; ++page_col)
        {
            for(row = 0; row < PF_ROW_TILES; ++row)
            {
                memset((void*)&playfield[page_row * PF_ROW_TILES + row][page_col * PF_COL_TILES], (int)'a' + page_row * PF_PAGE_COLS + page_col, (size_t)PF_COL_TILES);
            }
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

    // Bounds check
    if (line >= PF_LINES)
        return;

    if (col >= PF_COLS)
        return;

    p_row = line / PF_ROW_PIX;
    p_col = col  / PF_COL_PIX;

    // Check if we need to perform a course scroll
    if(*((short*)&DL[4]) != (unsigned short)&playfield[p_row][p_col])
        // Course scroll
        for(dl_row = 0; dl_row < PF_ROW_TILES; ++dl_row)
            *((short*)&DL[(dl_row * 3 + 1) + 3]) = (unsigned short)&playfield[p_row + dl_row][p_col];

    // Fine scroll
    ANTIC.vscrol = line % PF_ROW_PIX;
    ANTIC.hscrol = PF_COL_PIX - (col % PF_COL_PIX);
}
