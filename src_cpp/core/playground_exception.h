#ifndef CORE_PLAYGROUND_EXCEPTION_H_
#define CORE_PLAYGROUND_EXCEPTION_H_

#include <exception>
#include <string>

namespace playground {

class PlaygroundException : public std::exception {
 public:
  PlaygroundException();
  PlaygroundException(const std::string& desc);
  ~PlaygroundException() throw() {}
  
  const char* what() const noexcept { return description.c_str(); }

 protected:
  std::string description;
};

} // namespace playground

#endif // CORE_PLAYGROUND_EXCEPTION_H_