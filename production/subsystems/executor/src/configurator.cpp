#include <memory>
#include <executor/configurator.h>
#include <executor/application.h>

namespace executor
{
	configurator::configurator(lyra::parse_result&& result)
	{
		app = std::make_unique<executor::whole_application>();
	}

	executor::application& configurator::get_application() const
	{
		return *app;
	}
}
