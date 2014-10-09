#include <executor/os_proxy.h>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

namespace executor
{
	int os_proxy::call(const std::string& application, const std::vector<std::string>& arguments)
	{
		std::string invocation = application + " " +boost::join(arguments, " ");
		return std::system(invocation.c_str());
	}

	std::string os_proxy::get_current_working_directory()
	{
		return boost::filesystem::current_path().string();
	}
}