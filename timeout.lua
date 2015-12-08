-- Using timeouts in LuaMotif programs

require 'motif'

app = Initialize("TimeOut")

local function interval ()
	print('Tick...')
	app:AddTimeOut(1000, interval)
end
	
app:AddTimeOut(1000, interval)
app:MainLoop()
