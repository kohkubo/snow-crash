```sh
level02@SnowCrash:~$ file level02.pcap
level02.pcap: tcpdump capture file (little-endian) - version 2.4 (Ethernet, capture length 16777216)
```

## Wiresharkを使用しパケット解析する。

install wire shark
https://qiita.com/y-vectorfield/items/3aaaa98eb2aeca223ecf

### password文字列のパケット以降に送信されたパケットの文字列部分をつなげる。

```
// 16進数
66 74 5f 77 61 66 64 72 7f 7f 7f 4e 44 52 65 6c 7f 4c 30 4c
// １６進数から文字列に変換
ft_wafdr<del><del><del>NDRel<del>L0L
7fはdelだから直前の文字を一文字消す。
ft_waNDReL0L
```

```sh
level02@SnowCrash:~$ su flag02
Password:
Don't forget to launch getflag !
flag02@SnowCrash:~$ getflag
Check flag.Here is your token : kooda2puivaav1idi4f57q8iq
```