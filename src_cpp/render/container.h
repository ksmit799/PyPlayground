#ifndef RENDER_CONTAINER_H_
#define RENDER_CONTAINER_H_

#include <list>

#include "event/event_emitter.h"

namespace playground {

class Renderer;

class Container : public virtual EventEmitter {
 public:
  Container();
  ~Container();

  void Destroy();

  void RenderPass(Renderer* renderer);
  virtual void Render(Renderer* renderer);

  void SetActive(bool active);

  void AddChild(Container* child);
  void RemoveChild(Container* child);

  bool active_;
  Container* parent_;

 protected:
  std::list<Container*> children_;
};

} // namespace playground

#endif // RENDER_CONTAINER_H_