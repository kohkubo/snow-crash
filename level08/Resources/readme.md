```sh
level08@SnowCrash:~$ ls -l
total 16
-rwsr-s---+ 1 flag08 level08 8617 Mar  5  2016 level08
-rw-------  1 flag08 flag08    26 Mar  5  2016 token
```

ghidraで逆アセンブルする。
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

argv[1]をopen、readしwriteしているが、`token` 文字列を`strstr`で部分一致チェックしているため、`token` 文字列含めないようにして`token file`を渡す必要がある。

```sh
level08@SnowCrash:~$  ln -s /home/user/level08/token /tmp/hoge
level08@SnowCrash:~$  ./level08 /tmp/hoge
quif5eloekouj29ke0vouxean
```