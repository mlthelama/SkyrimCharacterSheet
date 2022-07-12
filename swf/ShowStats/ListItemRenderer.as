class ShowStats.ListItemRenderer extends gfx.controls.ListItemRenderer
{
	/* PRIVATE VARIABLES */

	/* STAGE ELEMENTS */

	//public var textFieldKey: MovieClip;
	public var textField: TextField;
	public var textFieldValue: TextField;

	public var textIcon: MovieClip;

	/* INITIALIZATION */

	// @override gfx.controls.ListItemRenderer
	public function ListItemRenderer(a_obj: Object)
	{
		super();
		//textField = textFieldKey.textField;
		textFieldValue._visible = false;
		textIcon._visible = false;

		var _loader = new MovieClipLoader();
		_loader.addListener(this);
		_loader.loadClip("skyui/icons_item_psychosteve_merged.swf", textIcon);
	}


	/* PUBLIC FUNCTIONS */

	/**
	 * @override gfx.controls.ListItemRenderer
	 *
	 * @param a_data
	 * 	displayName: String
	 */
	public function setData(a_data: Object): Void
	{
		super.setData(a_data);

		if (data != null) {
			/* maybe remove not needed  vars*/
			var displayName: String = data.displayName != null ? data.displayName : "";
			
			var displayValue: String = data.displayValue != null ? data.displayValue : "";
	
			var iconScale: Number = data.iconScale != null ? data.iconScale : 20;
	
			label = displayName;
			
			if (data.displayValue != null) {
				textFieldValue.text = displayValue;
				textFieldValue._visible = true;
			}

			textFieldValue.autoSize = "right";
			textField.autoSize = "left";

			if (data.iconKey != null) {
				textField._x = textField._x + 30;
				textIcon.gotoAndStop(data.iconKey);
				textIcon._width = iconScale;
				textIcon._height = iconScale;
				textIcon._visible = true;
			}
		}
	}

	public function reset(): Void
	{
		textFieldValue._visible = false;
		textIcon._visible = false;
	}

}