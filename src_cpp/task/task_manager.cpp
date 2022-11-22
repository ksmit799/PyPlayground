#include "task/task_manager.h"

#include <cassert>
#include <algorithm>
#include <string>

#include "pybind11/pybind11.h"
#include "core/playground_base.h"

namespace playground {

namespace py = pybind11;

TaskManager::TaskManager(PlaygroundBase* playground) : running_(true) {
  playground_ptr_ = playground;

  // The amount of task threads should always be between 1 and (N - 1)
  // where N is the number of CPU cores.
  num_task_threads_ = std::max(std::thread::hardware_concurrency(), 2u) - 1;

  // The default task queue runs tasks on the main thread. By default, all new
  // tasks run on this main thread to simplify programming. However, it's
  // recommended to make use of concurrent tasks.
  for (uint16_t i = 0; i < num_task_threads_; ++i) {
    task_threads_.emplace_back(&TaskManager::ThreadedRun, this);
  }
}

TaskManager::~TaskManager() {
  Shutdown();
}

void TaskManager::Shutdown() {
  running_ = false;

  for (std::thread& thread : task_threads_) {
    if (thread.joinable()) {
      thread.join();
    } 
  }
}

void TaskManager::Run() {
  // Make sure we're still running.
  if (!running_) {
    return;
  }

  // Should be running on the main thread.
  assert(std::this_thread::get_id() == playground_ptr_->main_thread_id_);
  // The active queue should be empty for swapping.
  assert(active_default_queue_.empty());

  // Swap the contents of the pending queue with the active queue.
  active_default_queue_.swap(pending_default_queue_);
  std::sort(active_default_queue_.begin(), active_default_queue_.end(), std::greater<>());

  // Run each task in the active queue until it's empty.
  while (!active_default_queue_.empty() && running_) {
    // Get the first task in queue.
    std::shared_ptr<Task> active_task = active_default_queue_.front();
    active_default_queue_.pop_front();

    assert(active_task->task_threaded_ == false);
    assert(active_task->task_state_ == Task::kActive);

    // Run the task.
    active_task->task_state_ = Task::kRunning;
    active_task->Run();

    // If the task was stopped while running,
    // don't add it back to the pending queue.
    if (active_task->task_state_ != Task::kInactive) {
      // Push the task to the back of the pending queue.
      // This should keep everything mostly in order when sorting.
      active_task->task_state_ = Task::kActive;
      pending_default_queue_.push_back(active_task);
    } 
  }
}

void TaskManager::ThreadedRun() {

}

std::shared_ptr<Task> TaskManager::CreateTask(const std::string& name,
                                              const std::function<void()>& func,
                                              const int& priority,
                                              const bool& threaded,
                                              const int& delay) {
  // Create a new task object.
  std::shared_ptr<Task> task = std::make_shared<Task>(this, name, func, priority, threaded, delay);
  task->Start();

  return task;
}

void TaskManager::AddTask(std::shared_ptr<Task> task) {
  if (!task->task_threaded_) {
    assert(task->task_threaded_ == false);
    assert(task->task_state_ == Task::kInactive);

    task->task_state_ = Task::kActive;
    pending_default_queue_.push_back(task);
  } else {
    // TODO(Ksmit799): Threaded tasks.
  }
}

void TaskManager::RemoveTask(std::shared_ptr<Task> task) {
  if (!task->task_threaded_) {
    assert(task->task_threaded_ == false);
    assert(task->task_state_ != Task::kInactive);

    if (task->task_state_ == Task::kRunning) {
      // Task is already executing.
      // Just mark it as inactive (won't be added back to queue).
      task->task_state_ = Task::kInactive;
    } else if (task->task_state_ == Task::kActive) {
      // Task is currently active but not running.
      // Mark it as inactive and remove it.
      task->task_state_ = Task::kInactive;

      // Active queue first.
      TaskQueue::iterator active_index = std::find(active_default_queue_.begin(), active_default_queue_.end(), task);
      if (active_index != active_default_queue_.end()) {
        active_default_queue_.erase(active_index);
        return;
      }

      // Pending queue second.
      TaskQueue::iterator pending_index = std::find(pending_default_queue_.begin(), pending_default_queue_.end(), task);
      if (pending_index != pending_default_queue_.end()) {
        pending_default_queue_.erase(active_index);
        return;
      }

      py::print("[PLAYGROUND]: Failed to locate task '" + task->task_name_ + "' on queue");
      assert(active_index == active_default_queue_.end() &&
             pending_index == pending_default_queue_.end());
    }
  } else {
    // TODO(Ksmit799): Threaded tasks.
  }
}

void wrap_task_task_manager(py::module& m) {
  py::module task_manager = m.def_submodule("task_manager", "");

  py::class_<TaskManager>(task_manager, "TaskManager")
    .def("run", &TaskManager::Run, "")
    .def("create_task", &TaskManager::CreateTask, "", 
         py::arg("name"), py::arg("function"),
         py::arg("priority") = 0,
         py::arg("threaded") = false,
         py::arg("delay") = 0);
}

} // namespace playground