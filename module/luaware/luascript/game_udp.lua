local socket = require "socket"
local structlib = require("struct")

 stringstr = "abcdefghik"
 print(string.sub(stringstr,1,10))


local port = 8003
local udpsocket = socket.udp()
-- udpsocket.settimeout(0)
udpsocket:setsockname('*', port)


local running = true

while running do
    data, msg_or_ip, port_or_nil = udpsocket:receivefrom()
    if data then
         print(string.len(data))
         print(structlib.unpack("!1<c2HHBBH",string.sub(data,1,10)))
    end
end
