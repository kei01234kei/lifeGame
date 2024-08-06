# lifeGame
大学の課題でライフゲームというシミュレーションゲームをC言語で作ったため公開します。

## コードの動かし方
LinuxかMacユーザの方は以下のコマンドをターミナルで実行してください。Windowsユーザーの方は頑張って調べてください。

```bash
$ git clone https://github.com/Kei01234/lifeGame.git
$ cd lifeGame
$ gcc lifeGame.c
$ ./a.out 生存範囲の幅 生存範囲の高さ 世代数 乱数のシード
```
生存範囲の幅、生存範囲の高さ、世代数、乱数のシードは任意の数値に変えてください。
