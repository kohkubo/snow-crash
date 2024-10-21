```sh
level13@SnowCrash:~$ ls -la
total 20
dr-x------ 1 level13 level13  120 Mar  5  2016 .
d--x--x--x 1 root    users    340 Aug 30  2015 ..
-r-x------ 1 level13 level13  220 Apr  3  2012 .bash_logout
-r-x------ 1 level13 level13 3518 Aug 30  2015 .bashrc
-rwsr-sr-x 1 flag13  level13 7303 Aug 30  2015 level13
-r-x------ 1 level13 level13  675 Apr  3  2012 .profile
```

```sh
level13@SnowCrash:~$ ltrace ./level13
__libc_start_main(0x804858c, 1, 0xbffff7e4, 0x80485f0, 0x8048660 <unfinished ...>
getuid()                                                                                                                                    = 2013
getuid()                                                                                                                                    = 2013
printf("UID %d started us but we we expe"..., 2013UID 2013 started us but we we expect 4242
)                                                                                         = 42
exit(1 <unfinished ...>
+++ exited (status 1) +++
```


```sh
level13@SnowCrash:~$ gdb ./level13
GNU gdb (Ubuntu/Linaro 7.4-2012.04-0ubuntu2.1) 7.4-2012.04
Copyright (C) 2012 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "i686-linux-gnu".
For bug reporting instructions, please see:
<http://bugs.launchpad.net/gdb-linaro/>...
Reading symbols from /home/user/level13/level13...(no debugging symbols found)...done.
(gdb) break getuid
Breakpoint 1 at 0x8048380
(gdb) run
Starting program: /home/user/level13/level13

Breakpoint 1, 0xb7ee4cc0 in getuid () from /lib/i386-linux-gnu/libc.so.6
(gdb) next
Single stepping until exit from function getuid,
which has no line number information.
0x0804859a in main ()
(gdb) print $eax
$1 = 2013
(gdb) set $eax = 4242
(gdb) continue
Continuing.
your token is 2A31L79asukciNyi8uppkEuSx
[Inferior 1 (process 4081) exited with code 050]
```
