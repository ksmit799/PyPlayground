#ifndef TASK_TASKMANAGER_H
#define TASK_TASKMANAGER_H

#include "task/Task.h"
#include "task/TaskCollection.h"

#include <mutex>
#include <map>
#include <string>
#include <memory>
#include <unordered_map> 

namespace playground
{

class TaskManager
{

public:
	TaskManager();

	void createTask(const std::string &name, int sort = 0, int rate = 0);
	void bindTask(const std::string &name, const Task &f);
	void tick();

private:
	std::mutex tickMutex;

	std::multimap<int, std::string> taskOrder;
	std::unordered_map<std::string, std::unique_ptr<TaskCollection>> nameToTask;

};

} // namespace playground

#endif // TASK_TASKMANAGER_H