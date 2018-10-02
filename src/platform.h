
#pragma once

#include "common.h"

extern void MakeRed();
extern void MakeGreen();
extern void MakeHighlight();
extern void MakeNormal();

struct RDE_Item
{
	std::string dir_name;
	std::string file_name;
};

struct RDE
{
	RDE() = default;
	RDE(std::string dir);
	~RDE();

	RDE& operator=(RDE&&) noexcept = default;
	RDE(RDE&&) noexcept = default;

	void swap(RDE& other) noexcept { pimpl.swap(other.pimpl); }

	std::unique_ptr<RDE_Item> getNext();
	void skipDir();

private:
	struct PIMPL;
	typedef std::unique_ptr<PIMPL> UPIMPL;
	UPIMPL pimpl;
};

extern std::time_t parse_date_from_string(std::string);
extern std::time_t get_modification_time_from_file(std::string);
extern bool        stdout_isatty();
extern void        clear_screen();
