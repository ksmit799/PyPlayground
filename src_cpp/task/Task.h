#ifndef TASK_TASK_H
#define TASK_TASK_H

#include <pybind11/functional.h>

#include <vector>

namespace playground
{

class Task
{

public:
	Task(const int &rate);

	void bind(std::function<void()> &f);
	void tick();

private:
	int rate;
	std::vector<std::function<void()>> functions;

};

} // namespace playground

#endif // TASK_TASK_H