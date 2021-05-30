#include "hooks.h"

namespace hooks
{
	namespace
	{
		void ButtonPressHook(RE::ButtonEvent::InputEvent* p_this) 
		{
			if (!p_this) {
				return;
			}
		}
		
		void InstallInputHook() {

			logger::trace("Input Hook.");
		}
	}

	void install() {
		InstallInputHook();
		logger::info("Installed hooks.");

	}
}