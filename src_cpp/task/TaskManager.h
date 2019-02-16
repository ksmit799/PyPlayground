#ifndef TASK_TASKMANAGER_H
#define TASK_TASKMANAGER_H

#include "task/Task.h"

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

	void createTask(const std::string &name, int *rate = nullptr, int *sort = nullptr);
	void bindTask(const std::string &name, std::function<void()> &f);
	void tick();

private:
	std::mutex tickLock;

	std::multimap<int, std::string> taskOrder;
	std::unordered_map<std::string, std::unique_ptr<Task>> nameToTask;

};

} // namespace playground

#endif // TASK_TASKMANAGER_H