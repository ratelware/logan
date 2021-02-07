#include <memory>
#include <executor/configurator.h>
#include <executor/application.h>

namespace executor
{
	executor::application& configurator::get_application() const
	{
		return *app;
	}
}
