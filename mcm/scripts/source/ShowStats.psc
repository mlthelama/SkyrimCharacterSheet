ScriptName ShowStats

; @brief Returns the currently bound key.
; @return - Returns -1 if unbound, else returns the current key binding.
Int Function GetKey() Global Native


; @brief Sets the current key binding.
; @param a_key - The key to bind.
Function SetKey(Int a_key) Global Native