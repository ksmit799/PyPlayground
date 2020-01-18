#include "event/event.h"

namespace playground {

Event::Event(const EventListener& listener, const bool& once) {
  event_listener_ = listener;
  run_once_ = once;
}

Event::~Event() {

}

void Event::Run() {
  event_listener_(event_args_);
  event_args_ = py::make_tuple();
}

void Event::RunNow(const py::args& args) {
  event_args_ = args;

  // Run immediately.
  Run();
}

void Event::Enqueue(const py::args& args) {
  event_args_ = args;

  Run();
}

} // namespace playground