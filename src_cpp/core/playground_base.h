#ifndef CORE_PLAYGROUND_BASE_H_
#define CORE_PLAYGROUND_BASE_H_

#include <memory>
#include <thread>

#include "display/window.h"
#include "render/renderer.h"
#include "task/task_manager.h"

namespace playground {

class PlaygroundBase {
 public:
  ~PlaygroundBase();

  void Quit() const;

  static PlaygroundBase* instance();

  void PollEvents();

  std::thread::id main_thread_id_;

  std::shared_ptr<Window> window;
  std::shared_ptr<Renderer> renderer;
  std::shared_ptr<TaskManager> task_manager;

  std::shared_ptr<Task> render_task;
  std::shared_ptr<Task> input_task;

 protected:
  PlaygroundBase();
  
  static PlaygroundBase* instance_ptr_;

};

} // namespace playground

#endif // CORE_PLAYGROUND_BASE_H_