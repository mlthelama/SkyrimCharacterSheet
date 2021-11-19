import gfx.controls.Button;
import gfx.events.EventTypes;
import gfx.io.GameDelegate;

class GlobalListener extends MovieClip {
	/* PRIVATE VARIABLES */
	private var _close: Button;


	/* INITIALIZATION */
	public function GlobalListener() {
		super();
        log("Running Listener ...");
	}


	public function onLoad(): Void {
		_close = _root.rootObj.menuClose;
		if (_close != undefined) {
            log("Register on Press ...");
			_close.addEventListener(EventTypes.PRESS, this, "handleClosePress");
		} else {
			log("Could not get close Button");
		}
	}


	/* PRIVATE FUNCTIONS */
	private function handleClosePress(a_event: Object): Void {
        log("Delegate CloseMenu ...");
		GameDelegate.call("CloseMenu", []);
	}


	private function log(a_message: String): Void {
		GameDelegate.call("Log", [a_message]);
	}
}
