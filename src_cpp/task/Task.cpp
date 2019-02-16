#include "task/Task.h"

namespace playground
{

Task::Task(const int &rate)
{
	this->rate = rate;
}

void Task::bind(std::function<void()> &f)
{
	this->functions.push_back(f);
}

void Task::tick()
{
	for (auto function : this->functions)
	{
		function();
	}
}

} // namespace playground