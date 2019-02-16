#include "core/_Wrapper.h"
#include "task/TaskManager.h"

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>

namespace playground
{

namespace py = pybind11;

TaskManager::TaskManager()
{

}

void TaskManager::createTask(const std::string &name, int *rate, int *sort)
{
	if (this->nameToTask.count(name))
	{
		py::print("Warning: Attempted to create duplicate task");
		return;
	}

	if (!rate)
		*rate = 0;

	if (!sort)
	{
		if (!this->taskOrder.empty())
			*sort = (--this->taskOrder.end())->first + 1; // EOM offset by 1.
		else
			*sort = 5; // Default to a high-ish value.
	}

	this->taskOrder.insert(std::make_pair(*sort, name));
	this->nameToTask[name] = std::unique_ptr<Task>(new Task(*rate));
}

void TaskManager::bindTask(const std::string &name, std::function<void()> &f)
{
	if (!this->nameToTask.count(name))
	{
		py::print("Warning: Attempted to bind to non-existent task");
		return;
	}

	this->nameToTask[name]->bind(f);
}

void TaskManager::tick()
{
	this->tickLock.lock();

	for (auto task = this->taskOrder.cbegin(); task != this->taskOrder.cend(); ++task)
	{
		this->nameToTask[task->second]->tick();
	}

	this->tickLock.unlock();
}

void wrap_task_taskmanager(py::module &m)
{	
	py::class_<TaskManager>(m, "TaskManager")

		// __init__
		.def(py::init<>())

		.def("createTask", &TaskManager::createTask, "",
			py::arg("name"), py::arg("rate") = nullptr, py::arg("sort") = nullptr)

		.def("bindTask", &TaskManager::bindTask, "")
		.def("tick", &TaskManager::tick, "");
}


} // namespace playground