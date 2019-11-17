#ifndef CORE_PLAYGROUND_BASE_H_
#define CORE_PLAYGROUND_BASE_H_

#include "display/window.h"
#include "render/renderer.h"

namespace playground {

class PlaygroundBase {
 public:
  ~PlaygroundBase();

  static PlaygroundBase* instance();

  Window* window;
  Renderer* renderer;

 protected:
  PlaygroundBase();
  
  static PlaygroundBase* instance_ptr_;

};

} // namespace playground

#endif // CORE_PLAYGROUND_BASE_H_