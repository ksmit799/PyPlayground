"""
"""

__all__ = ["PlaygroundApp"]

import builtins

from pyplayground.core.playground_base import PlaygroundBase
from pyplayground.core.playground_exception import PlaygroundException


class PlaygroundApp:
    def __init__(self):
        # Is the main app loop running?
        # Mangle to avoid potential conflicts in inheritors.
        self.__running = False

        self.instance = PlaygroundBase.instance()

        self.window = self.instance.window
        self.renderer = self.instance.renderer
        self.task_manager = self.instance.task_manager

        # Make sure we're not instantiating more then one PlaygroundApp.
        if hasattr(builtins, "playground_app"):
            raise PlaygroundException(
                "Attempted to create multiple PlaygroundApp instances!"
            )

        # TODO(Ksmit799): Currently, we make playground_app a builtin singleton pointer.
        # This is mainly for ease of use (especially for new programmers), however in the
        # future we may want to make this a global variable.
        builtins.playground_app = self

    def add_child(self, child):
        """"""
        self.renderer.add_child(child)

    def remove_child(self, child):
        """"""
        self.renderer.remove_child(child)

    def loop(self):
        """Run once through the PyPlayground app loop."""
        self.task_manager.run()

    def run(self):
        """Start running the blocking app loop."""
        self.__running = True

        while self.__running:
            self.loop()

    def quit(self):
        """Stop running the app loop and cleanup."""
        self.__running = False
        del builtins.playground_app
        self.instance.quit()
