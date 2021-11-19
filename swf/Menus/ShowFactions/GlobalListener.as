import gfx.controls.Button;
import gfx.events.EventTypes;
import gfx.io.GameDelegate;

class GlobalListener extends MovieClip {
	/* PRIVATE VARIABLES */
	private var _close: Button;
    private var _prev: Button;


	/* INITIALIZATION */
	public function GlobalListener() {
		super();
        log("Running Listener ...");
	}


	public function onLoad(): Void {
		_close = _root.rootObj.menuClose;
		if (_close != undefined) {
            log("Register on Close Press ...");
			_close.addEventListener(EventTypes.PRESS, this, "handleClosePress");
		} else {
			log("Could not get Close Button");
		}
        
        _prev = _root.rootObj.factionPrevScreen;
        if (_prev != undefined) {
            log("Register on PrevScreen Press ...");
            _prev.addEventListener(EventTypes.PRESS, this, "handlePrevPress");
        } else {
            log("Could not get Prev Button");
        }
	}


	/* PRIVATE FUNCTIONS */
	private function handleClosePress(a_event: Object): Void {
        log("Delegate CloseMenu ...");
		GameDelegate.call("CloseMenu", []);
	}
    
    private function handlePrevPress(a_event: Object): Void {
        log("Delegate PrevMenu ...");
        GameDelegate.call("PrevMenu", []);
    }


	private function log(a_message: String): Void {
		GameDelegate.call("Log", [a_message]);
	}
}
