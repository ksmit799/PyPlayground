#include "task/TaskCollection.h"

namespace playground
{

TaskCollection::TaskCollection(const int &rate) : rate(rate)
{} 

void TaskCollection::bind(const Task &f)
{
	this->tasks.push_back(f);
}

void TaskCollection::tick()
{
	for (auto task : this->tasks)
	{}
}

} // namespace playground