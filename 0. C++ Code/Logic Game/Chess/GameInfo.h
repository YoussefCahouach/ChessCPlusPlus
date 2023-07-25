#ifndef GameInfo_h
#define GameInfo_h
#include <vector>
#include "ChessPosition.hpp"

struct Direction {
    int dirX;
    int dirY;
};

const int NUM_COLS = 8;
const int NUM_ROWS = 8;


// Tamany en píxels dels gràfics de les peces
const int CELL_W = 62;
const int CELL_H = 62;

// Posició a pantalla de la casella superior esquerra del tauler
const int CELL_INIT_X = 55;
const int CELL_INIT_Y = 64;

// Posició a pantalla de la casella superior esquerra del tauler per dibuixar les posicions vàlides
const int GREEN_INIT_X = 52;
const int GREEN_INIT_Y = 68;

// Tamany en píxels de la pantalla
const int SCREEN_SIZE_X = 750;
const int SCREEN_SIZE_Y = 850;

typedef enum {
    GM_NORMAL,
    GM_REPLAY,
    GM_NONE
} GameMode;

#endif /* GameInfo_h */
