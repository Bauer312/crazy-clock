#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include "display.h"

display_t output;

void initialize_display() {
  initscr();
  clear();
  output.x = COLS / 2;
  output.y = LINES / 2;
  output.deltaX = 1;
  output.deltaY = 1;
  atexit(cleanup_display);
}

void cleanup_display() {
  endwin();
}

void add_display_text(char clockText[DISPLAY_TEXT_SIZE]) {
  // If this is the first line, clear the screen
  if(output.numLines == 0) {
    clear();
  }

  // Center the text
  move(output.y + output.numLines, output.x - (strlen(clockText) / 2));

  // Add the text to the screen
  addstr(clockText);

  // Add to the line count
  output.numLines++;

  // Update the max string length
  if((int)strlen(clockText) > output.maxLength) {
    output.maxLength = strlen(clockText);
  }
}

void display_clock() {
  // Park the cursor at the bottom right
  move(LINES-1,COLS-1);

  // Refresh the ncurses screen
  refresh();

  // Check to see if the text bounding box is at the edge
  if(output.x + (output.maxLength /2) >= COLS ||
      output.x <= (output.maxLength /2)) {
    // Change direction
    output.deltaX *= -1;
  }
  if(output.y + output.numLines >= LINES || output.y <= 0) {
    // Change direction
    output.deltaY *= -1;
  }

  // Update the starting center
  output.x += output.deltaX;
  output.y += output.deltaY;

  // Reset the line count and max line width
  output.numLines = 0;
  output.maxLength = 0;
}
