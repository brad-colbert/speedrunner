#ifndef __PLAYFIELD_H__
#define __PLAYFIELD_H__

#include "types.h"

#define PF_PAGE_ROWS 4
#define PF_PAGE_COLS 4

#ifdef GFX7
#else
#define PF_ROW_TILES 24
#define PF_COL_TILES 40

#define PF_ROW_BYTES (PF_ROW_TILES * PF_PAGE_ROWS)
#define PF_COL_BYTES (PF_COL_TILES * PF_PAGE_COLS)

#define PF_ROW_PIX 8
#define PF_COL_PIX 4

#define PF_LINES (PF_ROW_PIX * PF_ROW_BYTES)
#define PF_COLS  (PF_COL_PIX * PF_COL_BYTES)

#define PF_LINES_PER_PAGE (PF_ROW_TILES * PF_ROW_PIX)
#define PF_COLS_PER_PAGE (PF_COL_TILES * PF_COL_PIX)
#endif

extern byte playfield[PF_ROW_BYTES][PF_COL_BYTES];

void init_playfield(void);

extern u_short line_r, col_r;
void scroll_playfield(u_short line, u_short col);

#endif // __PLAYFIELD_H__