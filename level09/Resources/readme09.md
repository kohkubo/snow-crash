```sh
level09@SnowCrash:~$ ls -la
total 24
dr-x------ 1 level09 level09  140 Mar  5  2016 .
d--x--x--x 1 root    users    340 Aug 30  2015 ..
-r-x------ 1 level09 level09  220 Apr  3  2012 .bash_logout
-r-x------ 1 level09 level09 3518 Aug 30  2015 .bashrc
-rwsr-sr-x 1 flag09  level09 7640 Mar  5  2016 level09
-r-x------ 1 level09 level09  675 Apr  3  2012 .profile
----r--r-- 1 flag09  level09   26 Mar  5  2016 token
```

```sh
level09@SnowCrash:~$ ./level09
You need to provied only one arg.
```

```sh
level09@SnowCrash:~$ ./level09 aaaa
abcd
```

```sh
level09@SnowCrash:~$ cat token
f4kmm6p|=�p�n��DB�Du{��
```

```sh
level09@SnowCrash:~$ python /tmp/decrypt.py
Decrypted: f3iji1ju5yuevaus41q1afiuq
flag09@SnowCrash:~$ su flag09
Password:
Don't forget to launch getflag !
flag09@SnowCrash:~$ getflag
Check flag.Here is your token : s5cAJpM8ev6XHw998pRWG728z
```
