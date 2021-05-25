#include <executor/executor.h>

#include <executor/main.h>

namespace executor
{
    int executor::execute(int argc, char** argv)
	{
        return runLogan(argc, argv);
    }
}
