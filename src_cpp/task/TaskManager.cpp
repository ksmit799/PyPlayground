#include "core/_Wrapper.h"
#include "task/TaskManager.h"

#include "core/PlaygroundBase.h"

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>

namespace playground
{

namespace py = pybind11;

TaskManager::TaskManager()
{}

void TaskManager::createTask(const std::string &name, int sort, int rate)
{
	if (this->nameToTask.count(name))
	{
		PlaygroundBase::instance()->notify->warning("Attempted to create duplicate task: " + name);
		return;
	}

	if (sort < 1)
	{
		if (!this->taskOrder.empty())
			sort = (--this->taskOrder.end())->first + 1; // EOM offset by 1.
		else
			sort = 5; // Default to a high-ish value.
	}

	this->taskOrder.insert(std::make_pair(sort, name));
	this->nameToTask[name] = std::unique_ptr<TaskCollection>(new TaskCollection(rate));
}

void TaskManager::bindTask(const std::string &name, const Task &f)
{
	if (!this->nameToTask.count(name))
	{
		PlaygroundBase::instance()->notify->warning("Attempted to bind to non-existent task: " + name);
		return;
	}

	this->nameToTask[name]->bind(f);
}

void TaskManager::tick()
{
	this->tickMutex.lock();

	for (auto task = this->taskOrder.cbegin(); task != this->taskOrder.cend(); ++task)
	{
		this->nameToTask[task->second]->tick();
	}

	this->tickMutex.unlock();
}

void wrap_task_taskmanager(py::module &m)
{	
	py::class_<TaskManager>(m, "TaskManager")

		// __init__
		.def(py::init<>())

		.def("createTask", &TaskManager::createTask, "",
			py::arg("name"), py::arg("sort") = 0, py::arg("rate") = 0)

		.def("bindTask", &TaskManager::bindTask, "")
		.def("tick", &TaskManager::tick, "");
}


} // namespace playground