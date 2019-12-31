#ifndef TASK_TASK_MANAGER_H_
#define TASK_TASK_MANAGER_H_

#include <stdint.h>

#include <atomic>
#include <memory>
#include <deque>
#include <vector>
#include <thread>

#include "pybind11/functional.h" // std::function
#include "task/task.h"

namespace playground {

class PlaygroundBase;

class TaskManager {
 public:
  TaskManager(PlaygroundBase* playground);
  ~TaskManager();

  void Shutdown();
  void Run();
  std::shared_ptr<Task> CreateTask(const std::string& name,
                                   const std::function<void()>& func,
                                   const int& priority = Task::kNormal,
                                   const bool& threaded = false,
                                   const int& delay = 0);

  void AddTask(std::shared_ptr<Task> task);
  void RemoveTask(std::shared_ptr<Task> task);
  
 protected:
  typedef std::deque<std::shared_ptr<Task>> TaskQueue;

  void ThreadedRun();

  uint16_t num_task_threads_;
  std::atomic<bool> running_;

  TaskQueue active_default_queue_;
  TaskQueue pending_default_queue_;

  TaskQueue active_threaded_queue_;
  TaskQueue pending_threaded_queue_;

  std::vector<std::thread> task_threads_;

 private:
  PlaygroundBase* playground_ptr_;
};

} // namespace playground

#endif // TASK_TASK_MANAGER_H_