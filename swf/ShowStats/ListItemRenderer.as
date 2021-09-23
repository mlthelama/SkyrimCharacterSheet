class ShowStats.ListItemRenderer extends gfx.controls.ListItemRenderer
{
	/* PRIVATE VARIABLES */


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
	 */
	public function setData(a_data: Object): Void
	{
		super.setData(a_data);

		if (data != null) {
			/* maybe remove not needed  vars*/
			var displayName: String = data.displayName != null ? data.displayName : "";
	
			label = displayName;
		}
	}
}