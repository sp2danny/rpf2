
#include "../operators.h"
#include "../common.h"

using boost::algorithm::to_lower_copy;
using boost::algorithm::to_lower;

void InvOperator::Register()
{
	auto maker = [](std::string s) -> clone_ptr<Operator>
	{
		auto o = clone_ptr<InvOperator>(InvOperator{s});
		return clone_ptr<Operator>(o);
	};
	Operator::Register( MyChar() , +maker );
}

Operator* InvOperator::clone()
{
	return new InvOperator(*this);
};

char InvOperator::MyChar()
{
	return '~';
}

void InvOperator::Create ( std::string str )
{
	assert(!str.empty());
	assert(str[0] == MyChar());
	if (str.size() != 1)
		throw "operator syntax error";
}

void InvOperator::MatchDir ( File&, FileMatchStack& m )
{
	if (m.size() < 1)
	{
		throw "operator inv: not enough operands";
	}
}

void InvOperator::MatchFile ( File& f, FileMatchStack& m )
{
	MatchDir(f, m);
}

void InvOperator::MatchLines ( File& f, LineMatchStack& m )
{
	if (m.size() < 1)
	{
		throw "operator inv: not enough operands";
	}
	auto m1 = std::move(m.back()); m.pop_back();

	if (!m1.match())
	{
		m.push_back({false,{}});
		return;
	}

	LineMatch res{true, {}};
	UL i, n = f.lines().size();
	for (i=0; i<n; ++i)
	{
		if (!m1.have_line(i))
			res.add_simple_match(i);
	}
	res.match(!res.lines().empty());
	m.push_back(std::move(res));
}