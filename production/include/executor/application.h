#ifndef APPLICATION_H_JFEWUINDVJKNfuifnewufjiwefjoiwekdsmfkjnedgivnerigovrefefdwedwecvdfgvrthbtynbtynytythbythyt
#define APPLICATION_H_JFEWUINDVJKNfuifnewufjiwefjoiwekdsmfkjnedgivnerigovrefefdwedwecvdfgvrthbtynbtynytythbythyt

namespace executor
{
	class application
	{
	public:
		virtual ~application()= default;
		virtual int run() = 0;
	};

	class whole_application : public application
	{
	public:
		int run() override;
	};
}

#endif