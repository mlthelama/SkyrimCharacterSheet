class ShowStats.ListItemRenderer extends gfx.controls.ListItemRenderer
{
	/* PRIVATE VARIABLES */

	private static var RED: Number = 0xEF9A9A;
	private static var WHITE: Number = 0xFFFFFF;


	/* STAGE ELEMENTS */

	public var textContainer: MovieClip;


	/* INITIALIZATION */

	// @override gfx.controls.ListItemRenderer
	public function ListItemRenderer(a_obj: Object)
	{
		super();
		textField = textContainer.textField;
	}


	/* PUBLIC FUNCTIONS */

	/**
	 * @override gfx.controls.ListItemRenderer
	 *
	 * @param a_data
	 * 	displayName: String
	 * 	count: Number
	 *	stolen: Boolean
	 */
	public function setData(a_data: Object): Void
	{
		super.setData(a_data);

		if (data != null) {
			/* maybe remove not needed  vars*/
			var displayName: String = data.displayName != null ? data.displayName : "";
			var count: Number = data.count != null ? data.count : 1;
			var stolen: Boolean = data.stolen != null ? data.stolen : false;

			if (count > 1) {
				displayName += " (" + count.toString() + ")";
			}

			label = displayName;
			textField.textColor = stolen ? RED : WHITE;
		}
	}
}