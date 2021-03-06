
#include "../operators.h"
#include "../common.h"

void TrueOperator::Print(std::ostream& out) const
{
	out << "t";
}

char TrueOperator::MyChar()
{
	return 't';
}

void TrueOperator::Create([[maybe_unused]] std::string str)
{
	assert(!str.empty());
	assert(str[0] == MyChar());
	if (str.size() != 1)
		throw "operator syntax error";
}

void TrueOperator::MatchFile(File& , FileMatchStack& m)
{
	m.push_back(TriBool::True);
}

void TrueOperator::MatchLines(File& , LineMatchStack& m)
{
	m.push_back({true, {}});
}

