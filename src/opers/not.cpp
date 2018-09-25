
#include "../operators.h"
#include "../common.h"

using boost::algorithm::to_lower_copy;
using boost::algorithm::to_lower;

void NotOperator::Register()
{
	auto maker = [](std::string s) -> clone_ptr<Operator>
	{
		auto o = clone_ptr<NotOperator>(NotOperator{s});
		return clone_ptr<Operator>(o);
	};
	Operator::Register( MyChar() , +maker );
}

Operator* NotOperator::clone()
{
	return new NotOperator(*this);
};

char NotOperator::MyChar()
{
	return '!';
}

void NotOperator::Create ( std::string str )
{
	assert(!str.empty());
	assert(str[0] == MyChar());
	if (str.size() != 1)
		throw "operator syntax error";
}

/*void NotOperator::MatchDir ( File&, FileMatchStack& m )
{
	if (m.size() < 1)
	{
		throw "operator not: not enough operands";
	}
	TriBool m1 = m.back(); m.pop_back();
	TriBool res = Not(m1);
	m.push_back(res);
}*/

void NotOperator::MatchFile ( [[maybe_unused]] File& f, FileMatchStack& m )
{
	if (m.size() < 1)
	{
		throw "operator not: not enough operands";
	}
	TriBool m1 = m.back(); m.pop_back();
	TriBool res = Not(m1);
	m.push_back(res);
}

void NotOperator::MatchLines ( File& , LineMatchStack& m )
{
	if (m.size() < 1)
	{
		throw "operator not: not enough operands";
	}
	auto& m1 = m.back();
	m1.match(!m1.match());
	m1.modifiable_lines().clear();
}
