#pragma once
#include <string>

#include <algorithm> 
#include <functional> 
#include <locale>
#include <cctype>

namespace StringHelper
{
	inline bool StartsWith(const std::string& source, const std::string& compare)
	{
		if (source.size() < compare.size())
		{
			return false;
		}

		for (int i = 0; i < compare.size(); i++)
		{
			if (source[i] != compare[i])
			{
				return false;
			}
		}

		return true;
	}

	// "Hello" -> Hello, "File.png" -> File.png
	inline std::string Unquote(std::string input)
	{
		int start = 0, length = input.size();
		if (input[0] == '"')
		{
			start++;
			length--;
		}

		if (input[input.size() - 1] == '"')
		{
			length--;
		}

		return input.substr(start, length);
	}

	// trim from start
	inline std::string& TrimLeft(std::string& input) 
	{
		input.erase(input.begin(), std::find_if(input.begin(), input.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
		return input;
	}

	// trim from end
	inline std::string& TrimRight(std::string& input)
	{
		input.erase(std::find_if(input.rbegin(), input.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), input.end());
		return input;
	}

	// trim from both ends
	inline std::string& Trim(std::string& input)
	{
		return TrimLeft(TrimRight(input));
	}

}