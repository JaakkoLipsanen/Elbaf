
#include "Ensure.h"

namespace Ensure
{
	void True(bool argument)
	{
		if (!argument)
			throw std::invalid_argument("Argument is false");
	}

	void True(bool argument, const std::string& message)
	{
		if (!argument)
			throw std::invalid_argument(message);
	}

	void False(bool argument)
	{
		if (argument)
			throw std::invalid_argument("Argument is true");
	}

	void False(bool argument, const std::string& message)
	{
		if (argument)
			throw std::invalid_argument(message);
	}

	void NotNull(void* argument)
	{
		if (argument == nullptr)
		{
			throw std::invalid_argument("Argument is null");
		}
	}

	void NotNull(void* argument, const std::string& message)
	{
		if (argument == nullptr)
		{
			throw std::invalid_argument(message);
		}
	}
}