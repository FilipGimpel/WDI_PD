#define VWD    250
#define VHG    150
#define VHDIST  20
#define VVDIST 100
#define XSH     10
#define YSH     40
#define ARRL    60.0
#define ARRW    12.0

typedef struct elem {
    int value;
    struct elem *next;
} elem, *pelem;

void DrawArrowLine ( int x0, int y0, int x1, int y1 );
void DrawList(const char *fn, pelem e);

