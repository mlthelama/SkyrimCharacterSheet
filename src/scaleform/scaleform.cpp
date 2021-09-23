#include "scaleform/scaleform.h"
#include "scaleform/statsmenu.h"

namespace Scaleform {
	void Register() {
		StatsMenu::Register();
		logger::info("Registered all forms");
	}
}