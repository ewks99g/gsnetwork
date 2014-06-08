-------------------------------------------------
--test the coroutine's usage

co = coroutine.create(function() print("first coroutine") end)
print(co,type(co),coroutine.status(co))

coroutine.resume(co)
print(co,type(co),coroutine.status(co))

co = coroutine.create(function() for i = 1,100 do print("coroutine circle int "..i) coroutine.yield(co) end end)
coroutine.resume(co)
coroutine.resume(co)
coroutine.resume(co)
coroutine.resume(co)
