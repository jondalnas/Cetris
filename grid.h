typedef struct {
	wchar_t screenObj;
	char x;
	char y;
} tile_t;

typedef struct {
	tile_t* tiles_p;
	char width;
	char height;
} grid_t;

grid_t* createNewGrid(char width, char height);
void renderGrid(grid_t* grid_p);
void drawBoxChar(grid_t* grid_p, char fill, int x, int y, int width, int height);

const char _NONE;
const char _BORDER_V;
const char _BORDER_H;
const char _BORDER_UR;
const char _BORDER_UL;
const char _BORDER_DR;
const char _BORDER_DL;
const char _BLOCK;