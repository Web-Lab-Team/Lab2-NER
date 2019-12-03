#include "Output.h"
#include <windows.h>

#define SET_GRAY SetConsoleTextAttribute(\
			GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
#define SET_RED SetConsoleTextAttribute(\
			GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
#define SET_GREEN SetConsoleTextAttribute(\
			GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
#define SET_BLUE SetConsoleTextAttribute(\
			GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
#define SET_YELLOW SetConsoleTextAttribute(\
			GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
#define SET_PINK SetConsoleTextAttribute(\
			GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
#define SET_CYAN SetConsoleTextAttribute(\
			GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
#define SET_WHITE SetConsoleTextAttribute(\
			GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

std::wostream &Output::print_color(const std::wstring &ws, Color color, std::wostream &wos /*= std::wcout*/) {
	change_color(color);
	return wos << ws;
}

std::wostream &Output::print_color(wchar_t wc, Color color, std::wostream &wos /*= std::wcout*/) {
	change_color(color);
	return wos << wc;
}

std::ostream &Output::print_color(const std::string &s, Color color, std::ostream &os /*= std::cout*/) {
	change_color(color);
	return os << s;
}

std::ostream &Output::print_color(char c, Color color, std::ostream &os /*= std::cout*/) {
	change_color(color);
	return os << c;
}

void Output::change_color(Color color /*= WHITE*/) {
	switch (color) {
		case 0: SET_GRAY; break;
		case 1: SET_RED; break;
		case 2: SET_GREEN; break;
		case 3: SET_BLUE; break;
		case 4: SET_YELLOW; break;
		case 5: SET_PINK; break;
		case 6: SET_CYAN; break;
		case 7: SET_WHITE; break;
		default: SET_WHITE; break;
	}
}
