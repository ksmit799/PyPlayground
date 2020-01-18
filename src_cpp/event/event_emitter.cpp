#include "event/event_emitter.h"

#include "wrapper.h"

namespace playground {

EventEmitter::EventEmitter() {

}

EventEmitter::~EventEmitter() {
  Destroy();
}

void EventEmitter::Destroy() {

}

void EventEmitter::On(const std::string& event_name,
                      const EventListener& listener) {
  AddListener(event_name, listener);
}

void EventEmitter::Off(const std::string& event_name,
                       const EventListener& listener) {
  RemoveListener(event_name, listener);
}

void EventEmitter::Once(const std::string& event_name,
                        const EventListener& listener) {
  std::shared_ptr<Event> event = std::make_shared<Event>(listener, true);

  event_map_.emplace(event_name, event);
}

void EventEmitter::AddListener(const std::string& event_name,
                               const EventListener& listener) {
  std::shared_ptr<Event> event = std::make_shared<Event>(listener);

  event_map_.emplace(event_name, event);
}

void EventEmitter::RemoveListener(const std::string& event_name,
                                  const EventListener& listener) {
  EventMap::iterator event_index;

  void (*const* remove_target)(py::args) = listener.target<void(*)(py::args)>();

  for (event_index = event_map_.begin(); event_index != event_map_.end(); event_index++) {
    if (event_index->first == event_name) {
      void (*const* curr_target)(py::args) = event_index->second->event_listener_.target<void(*)(py::args)>();

      if (curr_target == remove_target && *curr_target == *remove_target) {
        event_map_.erase(event_index);
        break;
      }
    }
  }
}

void EventEmitter::RemoveAllListeners(const std::string& event_name) {
  event_map_.erase(event_name);
}

void EventEmitter::Emit(const std::string& event_name,
                        const py::args& args) {
  EventMap::iterator event_index;

  for (event_index = event_map_.begin(); event_index != event_map_.end(); event_index++) {
    if (event_index->first == event_name) {
      // Run the event on a deferred task queue (async).
      event_index->second->Enqueue(args);
    }
  }
}

void EventEmitter::EmitNow(const std::string& event_name,
                           const py::args& args) {
  EventMap::iterator event_index;

  for (event_index = event_map_.begin(); event_index != event_map_.end(); event_index++) {
    if (event_index->first == event_name) {
      // Run the event immediately (blocking).
      event_index->second->RunNow(args);
    }
  }
}

void wrap_event_event_emitter(py::module& m) {
  py::module event_emitter = m.def_submodule("event_emitter", "");

  py::class_<EventEmitter>(event_emitter, "EventEmitter")
    // Constructors.
    .def(py::init<>())
    // Functions & variables.
    .def("on", &EventEmitter::On, "")
    .def("off", &EventEmitter::Off, "")
    .def("once", &EventEmitter::Once, "")
    .def("add_listener", &EventEmitter::AddListener, "")
    .def("remove_listener", &EventEmitter::RemoveListener, "")
    .def("remove_all_listeners", &EventEmitter::RemoveAllListeners, "")
    .def("emit", &EventEmitter::Emit, "")
    .def("emit_now", &EventEmitter::EmitNow, "");
}

} // namespace playground