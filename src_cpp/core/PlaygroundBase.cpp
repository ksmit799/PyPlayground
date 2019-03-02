#include "core/_Wrapper.h"
#include "core/PlaygroundBase.h"

#include "task/InternalTask.h"

#include <pybind11/pybind11.h>

#include <SDL.h>

namespace playground
{

namespace py = pybind11;

bool PlaygroundBase::initialized = false;
PlaygroundBase* PlaygroundBase::playgroundInstance = nullptr;

void PlaygroundBase::init()
{
	if (initialized)
	{
		py::print("[WARNING]: Attempted to call PlaygroundBase init() more than once!");
		return;
	}

	initialized = true;
	
	// Initialize SDL2.
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		py::print("[ERROR]: Unable to initialize SDL:", SDL_GetError());
		throw std::exception();
	}
}

PlaygroundBase* PlaygroundBase::instance()
{
	if (!initialized)
		init();

	if (!playgroundInstance)
		playgroundInstance = new PlaygroundBase();

	return playgroundInstance;
}

PlaygroundBase::PlaygroundBase()
{
	this->notify = new Notify();
	this->taskManager = new TaskManager();
	this->messenger = new Messenger();
	this->renderer = new Renderer();

	// Create our two core loops (drives renderer and input).
	this->taskManager->createTask("inputLoop", 1);
	this->taskManager->createTask("renderLoop", 4); // Reserve 3/4 for anim/physics.

	// Create our tasks.
	//InternalTask renderTask(std::bind(&Renderer::render, std::ref(this->renderer)));

	// Bind our tasks.
	//this->taskManager->bindTask("inputLoop");
	//this->taskManager->bindTask("renderLoop", renderTask);

	this->renderer->setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

PlaygroundBase::~PlaygroundBase()
{
	this->notify->verbose("Exiting...");

	playgroundInstance = nullptr;

	delete this->notify;
	delete this->taskManager;
	delete this->messenger;
	delete this->renderer;

	SDL_Quit();
}

void wrap_core_playgroundbase(py::module &m)
{	
	py::class_<PlaygroundBase>(m, "PlaygroundBase")

		.def_static("instance", &PlaygroundBase::instance, "")

		.def_readonly("notify", &PlaygroundBase::notify, "")
		.def_readonly("taskManager", &PlaygroundBase::taskManager, "")
		.def_readonly("messenger", &PlaygroundBase::messenger, "")
		.def_readonly("renderer", &PlaygroundBase::renderer, "");
}

} // namespace playground