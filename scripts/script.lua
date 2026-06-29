window = createWindow(800, 450, "Example Window")

setWinPos(window, 200, 200)
setVertSync(0)

memoryAllocation = mAlloc(1000)

while not windowShouldClose(window) do
	setBackColor(42.0, 42.0, 53.0, 1.0)

	if getKey(window, 256) then
		mDealloc(memoryAllocation)
		closeWindow(window)
	end

	swapBuffers(window)
	pollEvents()
end

mForceDealloc()
closeWindow(window)