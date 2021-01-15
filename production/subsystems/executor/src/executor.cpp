#include <executor/executor.h>
#include <executor/options.h>
#include <executor/version.h>
#include <executor/configurator.h>
#include <executor/application.h>

#include <lyra/lyra.hpp>

#include <numeric>
#include <iostream>

namespace
{
	lyra::cli get_all_options()
	{
		auto cli = lyra::cli();
		executor::setup_options(cli);
		
		return cli;
	}

	lyra::parse_result setup_options(int argc, char** argv, lyra::cli& cli)
	{
	    return cli.parse({argc, argv } );
	}

	lyra::parse_result setup_parameters(int argc, char** argv, lyra::cli& cli)
	{
        return cli.parse( { argc, argv });
	}
}

namespace executor
{
    int executor::execute(int argc, char** argv)
	{
        auto cli = get_all_options();
        auto params = setup_parameters(argc, argv, cli);

        configurator(std::move(params)).get_application().run();

        return 0;
    }
}
