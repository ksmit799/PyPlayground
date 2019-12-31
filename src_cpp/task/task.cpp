#include "task/task.h"

#include <assert.h>

#include "pybind11/operators.h"
#include "wrapper.h"
#include "task/task_manager.h"

namespace playground {

namespace py = pybind11;

Task::Task(TaskManager* manager, const std::string& name,
           const std::function<void()>& func, const int& priority,
           const bool& threaded, const int& delay)
  : manager_ptr_(manager), task_name_(name), task_function_(func),
    task_priority_(priority), task_threaded_(threaded), task_delay_(delay) {

  task_state_ = ServiceState::kInactive;
}

Task::~Task() {
  Stop();
}

void Task::Start() {
  if (task_state_ != ServiceState::kInactive) {
    return;
  }

  manager_ptr_->AddTask(shared_from_this());
}

void Task::Stop() {
  if (task_state_ == ServiceState::kInactive) {
    return;
  }

  manager_ptr_->RemoveTask(shared_from_this());
}

void Task::Run() {
  task_function_();
}

bool operator ==(const Task& left, const Task& right) {
  return (left.task_priority_ == right.task_priority_);
}

bool operator !=(const Task& left, const Task& right) {
  return !(left == right);
}

bool operator <(const Task& left, const Task& right) {
  return (left.task_priority_ < right.task_priority_);
}

bool operator >(const Task& left, const Task& right) {
  return (left.task_priority_ > right.task_priority_);
}

void wrap_task_task(py::module& m) {
  py::module task_module = m.def_submodule("task", "");

  py::class_<Task, std::shared_ptr<Task>> task(task_module, "Task");
    // Operators.
    task.def(py::self == py::self)
    .def(py::self != py::self)
    .def(py::self < py::self)
    .def(py::self > py::self)
    // Functions & variables.
    .def("start", &Task::Start, "")
    .def("stop", &Task::Stop, "");

  py::enum_<Task::Priority>(task, "Priority")
    .value("CRITICAL", Task::Priority::kCritical)
    .value("HIGH", Task::Priority::kHigh)
    .value("NORMAL", Task::Priority::kNormal)
    .value("LOW", Task::Priority::kLow)
    .value("VERY_LOW", Task::Priority::kVeryLow)
    .export_values();
}

} // namespace playground