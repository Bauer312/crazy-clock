# Alt-Clock

## Features
* Displays a clock in binary, hex, or octal
* uses ncures to display
* If the size of the terminal is too small, use 0 and 1.
* If the size of the terminal is large enough, draw the 0 and 1 using other characters
* Accept configuration commands via command line or passed in via pipe (STDIN)
* One option - plain old time, but can specify the time zone
* One option - countdown timer, can specify the action that happens when the timer finishes
* The refresh rate should be at least 2 times per second - ideally at least 4 or 8
