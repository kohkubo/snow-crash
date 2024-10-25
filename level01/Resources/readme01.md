```sh
level01@SnowCrash:~$ cat /etc/passwd | grep flag01
flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash
```

## John the Ripperを使って解析

```sh
echo "42hDRfypTqqnw" > hash.txt
john hash.txt
```
