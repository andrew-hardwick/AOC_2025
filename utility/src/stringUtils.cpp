#include "stringUtils.h"

#include <iostream>
#include <sstream>


namespace advent { namespace utility { namespace string
{
	std::vector<std::string> split(
			std::string source,
			const std::string& delimiter)
	{
		std::vector<std::string> result;

		std::size_t delimiterLength = delimiter.size();

		auto loc = source.find(delimiter);

		while (loc != std::string::npos)
		{
			auto entry = source.substr(0, loc);

			if (entry.size() > 0)
			{
				result.push_back(entry);
			}

			source = source.substr(loc + delimiterLength);
			loc = source.find(delimiter);
		}

		if (source.size() > 0)
		{
			result.push_back(source);
		}

		return result;
	}

	std::vector<std::string> split(
			const std::string& source,
			char delimiter)
	{
		std::string strDelimiter { delimiter };

		return split(source, strDelimiter);
	}

	std::vector<int> convertToIntArray(
			const std::vector<std::string>& source)
	{
		std::vector<int> result;

		for (const auto& entry : source)
		{
			result.push_back(std::stoi(entry));
		}

		return result;
	}

	std::vector<int> parseToIntArray(
			const std::string& source,
			const std::string& delimiter)
	{
		auto splitSource = split(source, delimiter);

		return convertToIntArray(splitSource);
	}

	bool leadCharMatches(
			const std::string& target,
			char c,
			std::size_t count)
	{
		if (target.size() < count)
			return false;

		for (std::size_t i = 0;i < count; i++)
		{
			if (target[i] != c)
				return false;
		}

		return true;
	}

	std::string replace(
			const std::string& source,
			const std::string& target,
			const std::string& replacement)
	{
		auto splitSource = split(source, target);

		std::stringstream builder;

		auto it = splitSource.cbegin();
		while (it != splitSource.cend() - 1)
		{
			builder << *it << replacement;

			it++;
		}

		builder << *it;

		return builder.str();
	}

	std::string replace(
			const std::string& source,
			const std::vector<std::string>& targets,
			const std::vector<std::string>& replacements)
	{
		if (targets.size() != replacements.size())
		{
			throw std::invalid_argument("target and replacement length must match");
		}

		auto working = source;

		for (std::size_t i = 0; i < targets.size(); i++)
		{
			working = replace(working, targets.at(i), replacements.at(i));
		}

		return working;
	}
} } }

