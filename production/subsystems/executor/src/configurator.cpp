#include <executor/configurator.h>
#include <executor/application.h>

#include <boost/program_options/variables_map.hpp>

namespace executor
{
	configurator::configurator(const boost::program_options::variables_map&)
	{
		app = std::make_unique<executor::whole_application>();
	}

	configurator::~configurator()
	{}

	executor::application& configurator::application() const
	{
		return *app;
	}
}