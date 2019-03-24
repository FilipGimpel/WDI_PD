
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "drawlist.h"
#include "postscript.h"

char s[60];
int arrowLen, currentX, currentY;
int drawingRight = 1;

arrowLen = 200;
currentX = 20;
currentY = 6850;

void DrawArrowLine ( int x0, int y0, int x1, int y1 )
{
  point p[7];
  float dx, dy, d;

  dx = (float)(x1-x0);  dy = (float)(y1-y0);
  d = sqrt ( dx*dx + dy*dy );
  dx /= d;  dy /= d;
  p[0].x = x1;  p[0].y = y1;
  p[1].x = p[0].x-ARRL*dx-ARRW*dy;  p[1].y = p[0].y-ARRL*dy+ARRW*dx;
  p[2].x = p[0].x-ARRL*dx-2*dy;  p[2].y = p[0].y-ARRL*dy+2*dx;
  p[3].x = x0-2*dy;  p[3].y = y0+2*dx;
  p[4].x = x0+2*dy;  p[4].y = y0-2*dx;
  p[5].x = p[0].x-ARRL*dx+2*dy;  p[5].y = p[0].y-ARRL*dy-2*dx;
  p[6].x = p[0].x-ARRL*dx+ARRW*dy;  p[6].y = p[0].y-ARRL*dy-ARRW*dx;
  PSFillPolygon ( 7, p );
} /*DrawArrowLine*/

void drawOnTheRight(const char *fn, pelem first)
{
  PSDrawRect(VWD, VHG, currentX, currentY);

  sprintf ( s, "%d %d moveto (%d) show", currentX + 40, currentY + 40, first->value );
  PSWriteCommand ( s );
  
  currentX += VWD;

  if (first->next) DrawArrowLine(currentX, currentY + VHG/2,currentX + arrowLen, currentY + VHG/2);

  currentX += arrowLen;
}

void drawOnTheLeft(const char *fn, pelem first)
{
  currentX -= arrowLen;

  PSDrawRect(VWD, VHG, currentX, currentY);

  sprintf ( s, "%d %d moveto (%d) show", currentX + 40, currentY + 40, first->value );
  PSWriteCommand ( s );

  if (first->next) DrawArrowLine(currentX, currentY + VHG/2,currentX - arrowLen, currentY + VHG/2);
  currentX -= VWD;
}

void drawDown(const char *fn, pelem first)
{
  PSDrawRect(VWD, VHG, currentX, currentY);

  sprintf ( s, "%d %d moveto (%d) show", currentX + 40, currentY + 40, first->value );
  PSWriteCommand ( s );

  if (first->next) DrawArrowLine(currentX + VWD/2, currentY, currentX + VWD/2, currentY - arrowLen);

  first=first->next;

  currentY -= (VHG + arrowLen);
}

void DrawList(const char *fn, pelem first)
{
  PSOpenFile ( fn, 600 );
  PSWriteCommand ( "/Times-Roman findfont 100 scalefont setfont" );
  PSSetLineWidth ( 3.0 );

  while(first){
    if (drawingRight & currentX < 4000) {
      drawOnTheRight(fn, first);
    } else if (drawingRight & currentX > 4000) {
      drawingRight = 0;
      drawDown(fn, first);
      currentX += arrowLen;
    } else if (drawingRight == 0 & currentX > 400) {
      drawOnTheLeft(fn, first);
    } else if (drawingRight == 0) {
      drawingRight = 1;
      currentX -= arrowLen;
      drawDown(fn, first);
    }
    
    first=first->next;
  }
        
  PSCloseFile ();
}
