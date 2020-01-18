#ifndef EVENT_EVENT_EMITTER_H_
#define EVENT_EVENT_EMITTER_H_

#include <map>
#include <memory>

#include "pybind11/pybind11.h"
#include "pybind11/functional.h" // std::function
#include "event/event.h"

namespace playground {

namespace py = pybind11;

class EventEmitter {
 public:
  EventEmitter();
  ~EventEmitter();

  typedef std::function<void(py::args)> EventListener;

  void Destroy();

  void On(const std::string& event_name,
          const EventListener& listener);
  void Off(const std::string& event_name,
           const EventListener& listener);
  void Once(const std::string& event_name,
            const EventListener& listener);

  void AddListener(const std::string& event_name,
                   const EventListener& listener);
  void RemoveListener(const std::string& event_name,
                      const EventListener& listener);
  void RemoveAllListeners(const std::string& event_name);

  void Emit(const std::string& event_name,
            const py::args& args);
  void EmitNow(const std::string& event_name,
               const py::args& args);

 protected:
  typedef std::multimap<std::string, std::shared_ptr<Event>> EventMap;

  EventMap event_map_;
};

} // namespace playground

#endif // EVENT_EVENT_EMITTER_H_