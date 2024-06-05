#include <iostream>
#include <conio.h>

#include "methods.hpp"
#include "math/expression.hpp"
#include "math/parser.hpp"

#define KEY_UP 72
#define KEY_DOWN 80
#define ENTER 13
#define Q_KEY 113
#define ESC 27
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

int selection = 0;

void setCursorPosition(int x, int y) {
  static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  std::cout.flush();
  COORD coord = {(SHORT) x, (SHORT) y};
  SetConsoleCursorPosition(hOut, coord);
}

void cls() {
  static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  COORD topLeft = {0, 0};
  std::cout.flush();
  if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
    abort();
  }
  DWORD length = csbi.dwSize.X * csbi.dwSize.Y;
  DWORD written;
  FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);
  FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);
  SetConsoleCursorPosition(hOut, topLeft);
}


void process_expression() {
  system("CLS");
  std::cout << "=== Integral solver XXX ===" << std::endl;
  std::cout << "Enter equation:" << std::endl;
  std::string line;
  std::cin >> line;
  Expression *eq;
  for (;;) {
    try {
      eq = parse(line);
      break;
    } catch (...) {
      std::cout << "Parsing error, try again" << std::endl;
    }
  }
  double a, b;
  int n;
  std::cout << "Enter left border: ";
  std::cin >> a;
  std::cout << "Enter right border: ";
  std::cin >> b;
  std::cout << "Enter interval count: ";
  std::cin >> n;
  if (!does_converge(a, b, eq)) {
    std::cout << "It does not converge" << std::endl;
    return;
  }
  switch (selection) {
    case 0:
      calculate_left_rect(a, b, n, eq);
      break;
    case 1:
      calculate_cent_rect(a, b, n, eq);
      break;
    case 2:
      calculate_right_rect(a, b, n, eq);
      break;
    case 3:
      calculate_trapezia(a, b, n, eq);
      break;
    case 4:
      calculate_simpson(a, b, n, eq);
      break;
    default: ;
  }
}

int main() {

  setlocale(LC_ALL, "rus");
  cls();
  std::string output;
  for (;;) {
    std::cout << "=== Integral solver XXX ===" << std::endl;
    std::cout << "Choose method:" << std::endl;
    std::cout << (selection == 0 ? "> " : "  ") << "Left rectangles" << std::endl;
    std::cout << (selection == 1 ? "> " : "  ") << "Central rectangles" << std::endl;
    std::cout << (selection == 2 ? "> " : "  ") << "Right rectangles" << std::endl;
    std::cout << (selection == 3 ? "> " : "  ") << "Trapezoid" << std::endl;
    std::cout << (selection == 4 ? "> " : "  ") << "Simpson" << std::endl;
    std::cout << std::endl << "Press 'q' to exit" << std::endl;
    switch (getch()) {
      case KEY_UP:
        selection--;
        if (selection < 0) {
          selection = 0;
        }
        break;
      case KEY_DOWN:
        selection++;
        if (selection > 4) {
          selection = 4;
        }
        break;
      case ENTER:
        process_expression();
        std::cout << "Enter any key to continue..." << std::endl;
        getch();
        cls();
        break;
      case Q_KEY:
      case ESC:
        goto p_exit;
      default: ;
    }
    setCursorPosition(0, 0);
  }
p_exit:
  return 0;
}
