#ifndef DISPLAY_H
#define DISPLAY_H

#include "constants.h"

typedef struct display_t {
  int x;
  int y;
  int deltaX;
  int deltaY;
  int numLines;
  int maxLength;
} display_t;

void initialize_display();
void cleanup_display();
void add_display_text(char clockText[DISPLAY_TEXT_SIZE]);
void display_clock();

#endif
