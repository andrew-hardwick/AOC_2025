#include "commonAlg.h"


namespace advent { namespace utility { namespace commonAlg
{
	typedef std::pair<std::size_t, std::size_t> backpackEntry_t;

	std::vector<std::size_t> greedyBackpack(
			std::vector<std::pair<std::size_t, std::size_t>> source,
			std::function<std::vector<std::size_t>(std::size_t)> filter)
	{
		std::vector<std::size_t> result;

//		auto fitness = [] (std::pair<std::size_t, std::size_t> e)
//		{
//			return e.second;
//		};
//
//		while (source.size() > 0)
//		{
//			auto best = selectBest<std::pair<std::size_t, std(source, fitness);
//
//		}

		return result;
	}
} } }

