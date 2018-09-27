

#include "../operators.h"
#include "../common.h"

using boost::algorithm::to_lower_copy;
using boost::algorithm::to_lower;

char BMOperator::MyChar()
{
	return 'b';
}

void BMOperator::Create ( std::string str )
{
	assert(!str.empty());
	assert(str[0] == MyChar());
	str = unparan(str);
	sz = str.size();
	bm.emplace(str);
}

void BMOperator::MatchFile ( File& , FileMatchStack& m )
{
	m.push_back(tb_maybe);
}

void BMOperator::MatchLines ( File& f, LineMatchStack& m )
{
	UnCache();
	LinesCache(f);
	ExeCached(m);
}

void BMOperator::LinesCache(File& f)
{
	if (have_cache) return;
	UL ln = 0;
	for (auto&& l : f.lines())
	{
		auto lst = bm->match_all(l);
		for (auto&& p : lst)
			lm_cache.add_full_match(ln, p, p+sz);
		++ln;
	}
	have_cache = true;
}

bool BMOperator::IsCached() { return have_cache; }

int BMOperator::MyPrio() { return 3; }

void BMOperator::ExeCached(LineMatchStack& lms)
{
	if (have_cache)
		lms.push_back(lm_cache);
	else
		lms.push_back({tb_maybe});
}

void BMOperator::UnCache()
{
	have_cache = false;
	lm_cache = LineMatch{false,{}};
}

// ----------------------------------------------------------------------------

char BM_CIOperator::MyChar()
{
	return 'B';
}

void BM_CIOperator::Create ( std::string str )
{
	assert(!str.empty());
	assert(str[0] == MyChar());
	str = unparan(str);
	sz = str.size();
	bm.emplace(str);
}

void BM_CIOperator::MatchFile ( File& , FileMatchStack& m )
{
	m.push_back(tb_maybe);
}

void BM_CIOperator::MatchLines ( File& f, LineMatchStack& m )
{
	UnCache();
	LinesCache(f);
	ExeCached(m);
}

void BM_CIOperator::LinesCache(File& f)
{
	if (have_cache) return;
	UL ln = 0;
	for (auto&& l : f.lines())
	{
		auto lst = bm->match_all(l);
		for (auto&& p : lst)
			lm_cache.add_full_match(ln, p, p+sz);
		++ln;
	}
	have_cache = true;
}

bool BM_CIOperator::IsCached() { return have_cache; }

int BM_CIOperator::MyPrio() { return 4; }

void BM_CIOperator::ExeCached(LineMatchStack& lms)
{
	if (have_cache)
		lms.push_back(lm_cache);
	else
		lms.push_back({tb_maybe});
}

void BM_CIOperator::UnCache()
{
	have_cache = false;
	lm_cache = LineMatch{false,{}};
}

