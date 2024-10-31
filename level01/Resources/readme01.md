```sh
level01@SnowCrash:~$ cat /etc/passwd | grep flag01
flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash
```

## /etc/passwdの解説

ユーザのアカウント情報が格納されたファイル
https://www.oreilly.com/library/view/practical-unix-and/0596003234/ch04s03.html
https://linuc.org/study/knowledge/509/

## John the Ripperを使って解析

```sh
echo "42hDRfypTqqnw" > hash.txt
john hash.txt
john --show hash.txt
```

## 辞書アタック

```sh
gcc hash.c -o hash
./hash
```
