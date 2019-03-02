#ifndef TASK_TASKCOLLECTION_H
#define TASK_TASKCOLLECTION_H

#include "task/Task.h"

#include <vector>

namespace playground
{

class TaskCollection
{

public:
	TaskCollection(const int &rate);

	//void bind(const std::function<void()> &f);
	void bind(const Task &f);
	void tick();

private:
	int rate;
	std::vector<Task> tasks;

};

} // namespace playground

#endif // TASK_TASKCOLLECTION_H