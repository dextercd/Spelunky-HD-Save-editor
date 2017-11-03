#ifndef SPELUNKY_SAVE_HPP
#define SPELUNKY_SAVE_HPP

#include <array>
#include <variant>
#include <string>

using save = std::array<std::int32_t, 806>;

void read_save(save& sav, std::string path);
void write_save(const save& sav, std::string path);

class int_value {
public:
	const char* description;
	const std::size_t index;

	int_value(const char* d, std::size_t i);

	std::int32_t get_value(const save& s) const;

	void set_value(save& s, std::int32_t val);
};

class bool_value {
public:
	const char* const description;
	const std::size_t index;

	bool_value(const char* d, std::size_t i);

	bool get_value(const save& s);

	void set_value(save& s, bool val);
};


using save_element = std::variant<int_value, bool_value>;

class save_layout {
public:
	save_element elements[289];

	save_layout();
};

#endif // SPELUNKY_SAVE_HPP
