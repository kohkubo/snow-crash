# Level00

基本的な方針は`ls -la`でファイルがなければ、いろいろヒントが無いか調べる。

なかったので、以下で探索

```sh
level00@SnowCrash:~$ find / -user flag00 2>/dev/null
/usr/sbin/john
/rofs/usr/sbin/john
```

見つかったので、中身を確認。

```sh
level00@SnowCrash:~$ cat /usr/sbin/john
cdiiddwpgswtgt
```

シーザー暗号なので解読するスクリプトをやる

```sh
for i in {1..25}; do
echo -n "ROT$i: "
echo "cdiiddwpgswtgt" | tr 'A-Za-z' $(printf '%s' {A..Z} | cut -c$i-26)$(printf '%s' {A..Z} | cut -c1-$((i-1)))$(printf '%s' {a..z} | cut -c$i-26)$(printf '%s' {a..z} | cut -c1-$((i-1)))
done
```

各コマンド解説

tr: 文字列の変換を行うコマンド

`tr 'A-Za-z' $(printf '%s' {A..Z} | cut -c$i-26)`
`tr 'A-Za-z'`でA-Zとa-zの文字列を指定している。
`$(printf '%s' {A..Z} | cut -c$i-26)`でA-Zの文字列を取得している。
`$(printf '%s' {A..Z} | cut -c1-$((i-1)))`でA-Zの文字列を取得している。


printf: 書式付きで文字列を出力するコマンド
cut: 文字列を切り取るコマンド

## getflag

```sh
su flag01
getflag
```
