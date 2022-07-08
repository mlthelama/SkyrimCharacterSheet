class ShowStats.ListItemRenderer extends gfx.controls.ListItemRenderer
{
	/* PRIVATE VARIABLES */


	/* STAGE ELEMENTS */

	//public var textFieldKey: MovieClip;
	public var textField: TextField;
	public var textFieldValue: TextField;


	/* INITIALIZATION */

	// @override gfx.controls.ListItemRenderer
	public function ListItemRenderer(a_obj: Object)
	{
		super();
		//textField = textFieldKey.textField;
		textFieldValue._visible = false;
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
	
			label = displayName;
			
			if (data.displayValue != null) {
				textFieldValue.text = displayValue;
				textFieldValue._visible = true;
			}

			textFieldValue.autoSize = "right";
			textField.autoSize = "left";
		}
	}
}