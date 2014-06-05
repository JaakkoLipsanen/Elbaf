#include <string>

namespace Ensure
{
	void True(bool argument);
	void True(bool argument, const std::string& message);

	void False(bool argument);
	void False(bool argument, const std::string& message);

	void NotNull(void* argument);
	void NotNull(void* argument, const std::string& message);
}