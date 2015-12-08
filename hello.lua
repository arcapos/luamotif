require "motif"

button = PushButton {
	labelString = "Push here to say hello",
	activateCallback = function ()
		print("Hello yourself!")
	end
}

SetLanguageProc(nil, nil, nil)
app, toplevel = Initialize("XLua")

Realize(toplevel, button)
app:MainLoop()
