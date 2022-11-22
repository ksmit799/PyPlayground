#ifndef TASK_TASK_H_
#define TASK_TASK_H_

#include <string>
#include <memory>

#include "pybind11/pybind11.h"
#include "pybind11/functional.h" // std::function

namespace playground {

class TaskManager;

class Task : public std::enable_shared_from_this<Task> {
 public:
  Task(TaskManager* manager, std::string  name,
       std::function<void()>  func, const int& priority = Task::kNormal,
       const bool& threaded = false, const int& delay = 0);
  ~Task();

  void Start();
  void Stop();
  void Run() const;

  enum Priority {
    kCritical = 50,
    kHigh = 25,
    kNormal = 0,
    kLow = -25,
    kVeryLow = -50,
  };

  enum ServiceState {
    kInactive, // Inactive (no queue).
    kActive,   // Active (in active/pending queue).
    kRunning,  // Currently running.
  };

  std::string task_name_;
  std::function<void()> task_function_;
  int task_priority_;
  bool task_threaded_;
  int task_delay_;
  ServiceState task_state_;

 private:
  TaskManager* manager_ptr_;
};

bool operator ==(const Task& left, const Task& right);
bool operator !=(const Task& left, const Task& right);
bool operator <(const Task& left, const Task& right);
bool operator >(const Task& left, const Task& right);

} // namespace playground

#endif // TASK_TASK_H_