
#include "../operators.h"
#include "../common.h"

using boost::algorithm::to_lower_copy;
using boost::algorithm::to_lower;

void AndOperator::Register()
{
	auto maker = [](std::string s) -> clone_ptr<Operator>
	{
		auto o = clone_ptr<AndOperator>(AndOperator{s});
		return clone_ptr<Operator>(o);
	};
	Operator::Register( MyChar() , +maker );
}

Operator* AndOperator::clone()
{
	return new AndOperator(*this);
};

char AndOperator::MyChar()
{
	return 'a';
}

void AndOperator::Create(std::string str)
{
	assert(!str.empty());
	assert(str[0] == MyChar());
	if (str.size() == 1)
		all = false;
	else if (str=="a+")
		all = true;
	else
		throw "operator syntax error";
}

/*
void AndOperator::MatchDir ( File&, FileMatchStack& m )
{
	if (!all)
	{
		if (m.size() < 2)
		{
			throw "operator and: not enough operands";
		}
		TriBool m1 = m.back(); m.pop_back();
		TriBool m2 = m.back(); m.pop_back();
		TriBool res = And(m1, m2);
		m.push_back(res);
	} else {
		if (m.size() < 1)
			throw "operator and: not enough operands";
		TriBool res = m.back(); m.pop_back();
		while (!m.empty())
		{
			TriBool m1 = m.back(); m.pop_back();
			res = And(res, m1);
		}
		m.push_back(res);
	}
}
*/

void AndOperator::MatchFile ( [[maybe_unused]] File& f, FileMatchStack& m )
{
	if (!all)
	{
		if (m.size() < 2)
		{
			throw "operator and: not enough operands";
		}
		TriBool m1 = m.back(); m.pop_back();
		TriBool m2 = m.back(); m.pop_back();
		TriBool res = And(m1, m2);
		m.push_back(res);
	} else {
		if (m.size() < 1)
			throw "operator and: not enough operands";
		TriBool res = m.back(); m.pop_back();
		while (!m.empty())
		{
			TriBool m1 = m.back(); m.pop_back();
			res = And(res, m1);
		}
		m.push_back(res);
	}
}

void AndOperator::MatchLines ( File& f, LineMatchStack& m )
{
	auto sz = m.size();
	if (all && (sz==0))
		throw "operator and: not enough operands";
	if (all && (sz==1))
		return;
	if (sz < 2)
		throw "operator and: not enough operands";
	auto m2 = std::move(m.back()); m.pop_back();
	auto m1 = std::move(m.back()); m.pop_back();
	if (m1.match() && m2.match())
	{
		LineMatch res;
		res.match(true);
		res.modifiable_lines() = std::move(m1.modifiable_lines());
		for (auto&& l : m2.lines())
		{
			if (l.second.empty())
				res.add_simple_match(l.first);
			else
				for (auto&& x : l.second)
					res.add_full_match(l.first, x);
		}
		m.push_back(std::move(res));
	} else {
		m.emplace_back();
	}
	if (all)
		MatchLines(f, m);
}

