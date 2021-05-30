ScriptName ShowStats_MCM Extends SKI_ConfigBase


; Called when the config menu is initialized.
Event OnConfigInit()
	ModName = "$ShowStats"
EndEvent


; Called when the config menu is closed.
Event OnConfigClose()
EndEvent


; Called when a version update of this script has been detected.
; a_version - The new version.
Event OnVersionUpdate(Int a_version)
EndEvent


; Called when a new page is selected, including the initial empty page.
; a_page - The name of the the current page, or "" if no page is selected.
Event OnPageReset(String a_page)
	If (a_page == "")
		SetCursorFillMode(TOP_TO_BOTTOM)
		AddKeyMapOptionST("Key_K", "$ShowStats_Key_OptionText", ShowStats.GetKey())
	EndIf
EndEvent

State Key_K
	Event OnKeyMapChangeST(Int a_newKeyCode, String a_conflictControl, String a_conflictName)
		If (HandleKeyConflict(a_conflictControl, a_conflictName))
			ShowStats.SetKey(a_newKeyCode)
			SetKeymapOptionValueST(a_newKeyCode)
		EndIf
	EndEvent

	Event OnDefaultST()
		ShowStats.SetKey(-1)
		SetKeymapOptionValueST(-1)
	EndEvent

	Event OnHighlightST()
		SetInfoText("$ShowStats_Key_InfoText")
	EndEvent
EndState


Bool Function HandleKeyConflict(String a_conflictControl, String a_conflictName)
	If (a_conflictControl != "")
		String msg
		If (a_conflictName != "")
			msg = "$ShowStats_KeyConflict_Control{" + a_conflictControl + "}_Name{" + a_conflictName + "}"
		Else
			msg = "$ShowStats_KeyConflict_Control{" + a_conflictControl + "}"
		EndIf
		Return ShowMessage(msg, True, "$Yes", "$No")
	EndIf
	Return True
EndFunction