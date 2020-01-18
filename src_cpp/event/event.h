#ifndef EVENT_EVENT_H_
#define EVENT_EVENT_H_

#include <memory>

#include "pybind11/pybind11.h"
#include "pybind11/functional.h" // std::function

namespace playground {

namespace py = pybind11;

class Event : public std::enable_shared_from_this<Event> {
 public:
  typedef std::function<void(py::args)> EventListener;

  Event(const EventListener& listener,
        const bool& once = false);
  ~Event();

  void Run();

  void RunNow(const py::args& args);
  void Enqueue(const py::args& args);

  EventListener event_listener_;
  py::args event_args_;
  bool run_once_;
};

} // namespace playground

#endif // EVENT_EVENT_H_