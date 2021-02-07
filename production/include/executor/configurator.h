#ifndef CONFIGURATOR_H_DMKiwajf9834jfrejfkgfdmkcmskmaodmweuf43n8g5hn4btgfjeuidjwdjsalkdkwejfnjrenvhui43v4rmf
#define CONFIGURATOR_H_DMKiwajf9834jfrejfkgfdmkcmskmaodmweuf43n8g5hn4btgfjeuidjwdjsalkdkwejfnjrenvhui43v4rmf

#include <memory>

namespace executor
{
	class application;

	class configurator
	{
	public:
		application& get_application() const;

	private:
		std::unique_ptr<::executor::application> app;
	};
}

#endif
