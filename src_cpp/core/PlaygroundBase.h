#ifndef CORE_PLAYGROUNDBASE_H
#define CORE_PLAYGROUNDBASE_H

#include "notify/Notify.h"
#include "task/TaskManager.h"
#include "messenger/Messenger.h"
#include "render/Renderer.h"

#include <memory>

namespace playground
{

class PlaygroundBase
{

public:
	~PlaygroundBase();
	
	static void init();
	static PlaygroundBase* instance();

	Notify *notify;
	TaskManager *taskManager;
	Messenger *messenger;
	Renderer *renderer;

private:
	PlaygroundBase();

	static bool initialized;
	static PlaygroundBase *playgroundInstance;

};

} // namespace playground

#endif // CORE_PLAYGROUNDBASE_H