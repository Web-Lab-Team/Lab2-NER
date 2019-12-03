#pragma once
#include <string>
#include <iostream>

class Output {
public:
	using Color = enum { Gray, Red, GREEN, BLUE, YELLOW, PINK, CYAN, WHITE };
	static std::wostream &print_color(const std::wstring &ws, Color color, std::wostream &wos = std::wcout);
	static std::wostream &print_color(wchar_t wc, Color color, std::wostream &wos = std::wcout);
	static std::ostream &print_color(const std::string &s, Color color, std::ostream &os = std::cout);
	static std::ostream &print_color(char c, Color color, std::ostream &os = std::cout);
	static void change_color(Color color = WHITE);
};

