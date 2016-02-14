-- Using timeouts in LuaMotif programs

local motif = require 'motif'

app = motif.Initialize("TimeOut")

local function interval ()
	print('Tick...')
	app:AddTimeOut(1000, interval)
end

app:AddTimeOut(1000, interval)
app:MainLoop()
