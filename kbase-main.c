#include <apple2enh.h>
#include <conio.h>
#include <stdlib.h>
#include <tuilibap.h>

#define   STATE_DEFAULT       0
#define   STATE_INPUT         1
#define   STATE_TERMINATE     2

void cursorOn(void);
void newline(char address);
void blankLine(void);
void displayMemory(char address, int value);
void displayPc(char value);
void displayAccumulator(int value);
int getInput(char address);
int shift(char left, char right, int accumulator);
void displayOutput(int value);

char cardiacState = STATE_DEFAULT;

void main(void) {
  int col80prev = videomode(VIDEOMODE_80x24);
  char inc = 0, cIndex;
  int memory[100], programCounter = 0, accumulator = 0;

  tgui_Window *tgw3;

  clrscr();

	tgw3=newwindow(0,0,79,23,COLOR_BLACK, 1,"A2 CARDIAC");

  for (cIndex = 0; cIndex < 100; cIndex++) {
    if (cIndex == 0) {
      memory[cIndex] = 001;
    } else {
      memory[cIndex] = 000;
    }
  }

//  clrscr();
//  cputsxy(35, 0, "A2 CARDIAC\r\n");
//  chlinexy(0, 1, 80);

//  chlinexy(0, 22, 80);

//  cvlinexy(50, 23, 1);

  for (cIndex = 0; cIndex < 100; cIndex++) {
    displayMemory(cIndex, memory[cIndex]);
  }

  displayPc(programCounter);
  displayAccumulator(accumulator);

  blankLine();
  while (1) {
    if (kbhit()) {
      inc = cgetc();
      if (inc == 'Q' || inc == 'q') {
        break;
      }
    };

    if (cardiacState == STATE_DEFAULT) {
      int instruction = memory[programCounter];
      char op = instruction/100;
      char arg = instruction - (op * 100);
      int value, left, right;

      displayPc(programCounter++);

      switch (op) {
        case 0: // input
          value = getInput(arg);
          memory[arg] = value;
          displayMemory(arg, value);
          break;
        case 1: // clear and add
          accumulator = memory[arg];
          displayAccumulator(accumulator);
          break;
        case 2: // add
          accumulator += memory[arg];
          displayAccumulator(accumulator);
          break;
        case 3: // test accumulator
          if (accumulator < 0) {
            programCounter = arg;
          }
          break;
        case 4: // shift
          left = arg / 10;
          right = arg - (left * 10);
          accumulator = shift(left, right, accumulator);
          displayAccumulator(accumulator);
          break;
        case 5: // output
          displayOutput(memory[arg]);
          break;
        case 6: // store accumulator
          memory[arg] = accumulator;
          displayMemory(arg, accumulator);
          break;
        case 7: // subtract
          accumulator -= memory[arg];
          displayAccumulator(accumulator);
          break;
        case 8: // jump
          programCounter = arg;
          break;
        case 9: // halt and reset
          programCounter = arg;
          break;
      }
    }

    if (cardiacState == STATE_TERMINATE) {
      break;
    }
  }


  if (col80prev == VIDEOMODE_40x24) {
    clrscr();
    videomode(VIDEOMODE_40x24);
  }
}

void displayMemory(char address, int value) {
  int y = (address % 20) + 2, x = ((int)(address/20) * 10) + 2;
  gotoxy(x, y);
  cprintf("%02d:%03d", address, abs(value));
  if (value < 0) {
    cputc('-');
  } else {
    cputc(' ');
  }
}

void displayPc(char value) {
  gotoxy(58, 5);
  cputs("PROGRAM COUNTER");
  chlinexy(56, 6, 19);
  chlinexy(56, 10, 19);
  cvlinexy(55, 7, 3);
  cvlinexy(75, 7, 3);
  gotoxy(64, 8);
  cprintf("%02d", value);
}

void displayOutput(int value) {
  gotoxy(64, 23);
  if (value < 0) {
    cputc('-');
  } else {
    cputc(' ');
  }
  cprintf("%03d", abs(value));
}

void displayAccumulator(int value) {
  gotoxy(60, 13);
  cputs("ACCUMULATOR");
  chlinexy(56, 14, 19);
  chlinexy(56, 18, 19);
  cvlinexy(55, 15, 3);
  cvlinexy(75, 15, 3);
  gotoxy(63, 16);
  if (value < 0) {
    cputc('-');
  } else {
    cputc(' ');
  }
  cprintf("%03d", abs(value));
}

void cursorOn(void) {
  cputc('_');
  gotox(wherex() - 1);
}

void newline(char address) {
  gotoxy(0, 23);
  cclear(40);
  gotoxy(0, 23);
  cprintf("%02d:", address);
  cursorOn();
}

void blankLine(void) {
  gotoxy(0, 23);
  cclear(40);
  gotoxy(0, 23);
}

int getInput(char address) {
  int result = 0;
  char num[4], numIndex = 0;

  num[3]= '\0';
  newline(address);

  while (1) {
    if (kbhit()) {
      char c = cgetc();
      if (c == 'Q' || c == 'q') {
        cardiacState = STATE_TERMINATE;
        return 0;
      } else if (c >= '0' && c <= '9' && numIndex < 3) {
        num[numIndex++] = c;
        cputc(c);
      } else if (c == '\r' || c == '\n') {
        result = atoi(num);
        break;
      }
    }
  }

  blankLine();
  return result;
}

int shift(char left, char right, int accumulator) {
  char index = left;
  int result = accumulator;
  for (index = 0; index < left; index++) {
    result *= 10;
  }

  if (result > 999) {
    result %= 1000;
  }

  for (index = 0; index < right; index++) {
    result /= 10;
  }

  return result;
}
