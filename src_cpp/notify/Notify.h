#ifndef NOTIFY_NOTIFY_H
#define NOTIFY_NOTIFY_H

#include <string>

namespace playground
{

class Notify
{

public:
	Notify();

	void verbose(const std::string &message);
	void info(const std::string &message);
	void warning(const std::string &message);
	void error(const std::string &message);

private:
	std::string getTime();

};

} // namespace playground

#endif // NOTIFY_NOTIFY_H