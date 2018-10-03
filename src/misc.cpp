
#include "common.h"
#include "OFM.h"

std::string unparan(std::string_view str)
{
	auto sz = str.size();
	assert( sz > 3 );
	assert( str[1] == '(' );
	assert( str.back() == ')' );
	return str.substr(2, sz-3).to_string();
}

int getparam(std::string_view str, int def)
{
	//[[expects: (def>=0)]]
	str = str.substr(1);
	if (str.empty()) return def;
	return std::stoi(str.to_string());
}

std::vector<std::string> readfile(std::istream& in)
{
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(in, line))
	{
		lines.push_back(line);
	}
	return lines;
}

#include "operators.h"

#define REG( xx ) xx ## Operator{}.Register()

void register_all()
{
	REG(And);
	REG(Dir);
	REG(File);
	REG(CppOnly);
	REG(Line);
	REG(LineCI);
	REG(Not);
	REG(Or);
	REG(Near);
	REG(BM);
	REG(BM_CI);
	REG(Regex);
	REG(Sub);
	REG(True);
	REG(Inv);
	REG(Mod);
	REG(Ident);
	REG(IdentCI);
	REG(Range);
	REG(Dup);
	REG(Swap);
}

#undef REG

TriBool And(TriBool lhs, TriBool rhs)
{
	switch (lhs)
	{
	case tb_false:
		return tb_false;
	case tb_maybe:
		return (rhs==tb_false) ? tb_false : tb_maybe;
	case tb_true:
		return rhs;
	default:
		throw "internal engine error";
	}
}

TriBool Or(TriBool lhs, TriBool rhs)
{
	switch (lhs)
	{
	case tb_true:
		return tb_true;
	case tb_maybe:
		return (rhs==tb_true) ? tb_true : tb_maybe;
	case tb_false:
		return rhs;
	default:
		throw "internal engine error";
	}
}

TriBool Not(TriBool arg)
{
	switch (arg)
	{
	case tb_true:
		return tb_false;
	case tb_maybe:
		return tb_maybe;
	case tb_false:
		return tb_true;
	default:
		throw "internal engine error";
	}
}

TriBool FromBool(bool b)
{
	return b ? tb_true : tb_false;
}




