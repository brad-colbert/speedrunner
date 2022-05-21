#ifndef __PLAYFIELD_H__
#define __PLAYFIELD_H__

#include "types.h"

#define PF_PAGE_ROWS 4
#define PF_PAGE_COLS 4

#ifdef GFX7
#else
#define PF_ROW_TILES 24
#define PF_COL_TILES 40

#define PF_ROW_PIX 8
#define PF_COL_PIX 4

#define PF_LINES_PAGE (PF_ROW_TILES * PF_ROW_PIX)
#define PF_COLS_PAGE  (PF_COL_TILES * PF_COL_PIX)

#define PF_LINES (PF_PAGE_ROWS * PF_ROW_TILES * PF_ROW_PIX)
#define PF_COLS  (PF_PAGE_COLS * PF_COL_TILES * PF_COL_PIX)
#endif

extern byte playfield[PF_PAGE_ROWS * PF_ROW_TILES][PF_PAGE_COLS * PF_COL_TILES];

void init_playfield(void);

void scroll_playfield(u_short line, u_short col);

#endif // __PLAYFIELD_H__