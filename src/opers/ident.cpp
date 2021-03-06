
#include "../operators.h"
#include "../common.h"
#include "../stringtools.h"

void IdentOperator::Print(std::ostream& out) const
{
	out << "i='" << id << "'";
}

char IdentOperator::MyChar()
{
	return 'i';
}

void IdentOperator::Create(std::string str)
{
	assert(!str.empty());
	assert(str[0] == MyChar());
	id = unParan(str);
}

void IdentOperator::MatchFile(File&, FileMatchStack& m)
{
	m.push_back(TriBool::Maybe);
}

void IdentOperator::MatchLines(File& f, LineMatchStack& m)
{
	UnCache();
	LinesCache(f);
	ExeCached(m);
}

void IdentOperator::LinesCache(File& f)
{
	if (mHaveCache) return;
	UL ln = 0;
	UL sz = id.size();
	for (auto&& l : f.lines())
	{
		auto vsp = tokenify(l);
		for (auto&& t : vsp)
		{
			if (t.first == id)
			{
				mLmCache.addFullMatch(ln, t.second, t.second+sz);
			}
		}
		++ln;
	}
	mHaveCache = true;
}

bool IdentOperator::IsCached() { return mHaveCache; }

int IdentOperator::MyPrio() { return 20; }

void IdentOperator::ExeCached(LineMatchStack& lms)
{
	if (mHaveCache)
		lms.push_back(mLmCache);
	else
		lms.push_back({TriBool::Maybe});
}

void IdentOperator::UnCache()
{
	mHaveCache = false;
	mLmCache = LineMatch{false,{}};
}

// ----------------------------------------------------------------------------

void IdentCIOperator::Print(std::ostream& out) const
{
	out << "I='" << id << "'";
}

char IdentCIOperator::MyChar()
{
	return 'I';
}

void IdentCIOperator::Create(std::string str)
{
	assert(!str.empty());
	assert(str[0] == MyChar());
	id = to_lower_copy(unParan(str));
}

void IdentCIOperator::MatchFile(File&, FileMatchStack& m)
{
	m.push_back(TriBool::Maybe);
}

void IdentCIOperator::MatchLines(File& f, LineMatchStack& m)
{
	UnCache();
	LinesCache(f);
	ExeCached(m);
}

void IdentCIOperator::LinesCache(File& f)
{
	if (mHaveCache) return;
	UL ln = 0;
	UL sz = id.size();
	for (auto&& l : f.lines())
	{
		auto vsp = tokenify(l);
		for (auto&& t : vsp)
		{
			if (to_lower_copy(t.first) == id)
			{
				mLmCache.addFullMatch(ln, t.second, t.second+sz);
			}
		}
		++ln;
	}
	mHaveCache = true;
}

bool IdentCIOperator::IsCached() { return mHaveCache; }

int IdentCIOperator::MyPrio() { return 25; }

void IdentCIOperator::ExeCached(LineMatchStack& lms)
{
	if (mHaveCache)
		lms.push_back(mLmCache);
	else
		lms.push_back({TriBool::Maybe});
}

void IdentCIOperator::UnCache()
{
	mHaveCache = false;
	mLmCache = LineMatch{false,{}};
}


