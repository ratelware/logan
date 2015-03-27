#include <executor/options.h>
#include <boost/program_options.hpp>

namespace executor
{
	boost::program_options::options_description setup_options()
	{
		boost::program_options::options_description desc("General options");
		desc.add_options()
			("help,h", "Print this message and exit")
			("version,v", "Print version descriptor and exit")
			("input,i", boost::program_options::value<std::string>()->value_name("INPUT"), "Location of input file")
			("output,o", boost::program_options::value<std::string>()->value_name("OUT")->default_value("out.stp"), "Location of output file")
			("working_directory", boost::program_options::value<std::string>()->value_name("WORKSPACE")->default_value("temp"), "Directory solely dedicated for keeping temporary files")
		    ("config_file", boost::program_options::value<std::string>()->value_name("BASIC_CONFIG")->default_value("config.ini"), "Path to file containing basic configuration options")
			;

		return desc;
	}
}