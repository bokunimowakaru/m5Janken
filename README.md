# m5Janken: M5Stack Janken 猜拳 Examples by Wataru KUNINO

M5Stack用のジャンケン・プログラム集です。  
Let's learn Janken Programing with IoT ready M5Stack.  

1. janken01_pict：本体LCD面のボタンを押すと、ボタンに応じたジャンケンの手を表示します
2. janken02_rnd：ESP32マイコンがランダムで手を表示し、ジャンケン対戦が出来ます
3. janken03_game：ジャンケン対戦の勝敗および得点を表示することで、ゲームらしさを追加します
4. janken04_lan：同じWi-Fiアクセスポイントに接続した2台のM5Stackで通信対決します
5. janken05_net：クラウド・サーバのジャンケン・アルゴリズムとの対戦が出来ます

### Janken

Janken (or Rock Paper Scissors) is a pupluer game in Japan:
- Three hand's elements, ROCK, PAPER, SCISSORS are shaped by fingers.
- A player throw one of the elements.
- Simultaneously, the other player (or Janken Server) also throw.
- Throwed ROCK will win from SCISSORS hand, but it will lose PAPER hand.

## M5Stack Janken 猜拳 Examples の使い方

- プログラムは Arduino IDE でコンパイルしてください
- 「janken_pict」フォルダ内の画像ファイルをMicro SDカードの直下ディレクトリにコピーしてください

### Usage of Janken Server

Usage: https://bokunimo.com/janken/?user=YOURNAME&throw=X (X = G or C or P)

- 説明(Usage)：  
	https://bokunimo.com/janken/  

- グー(code=G),ROCK：  
	https://bokunimo.com/janken/?throw=G  

- チョキ(code=C),SCISSORS：  
	https://bokunimo.com/janken/?throw=C  

- パー(code=P),PAPER：  
	https://bokunimo.com/janken/?throw=P  

## ご注意
- janken05_netは、クラウド・サーバへSSIDの一部(後部4文字)またはニックネームを送信します
- 自由に利用できますが、無保証です。詳細はソースコード、README、[LICENSE](https://github.com/bokunimowakaru/m5Janken/blob/master/LICENSE)をご覧ください

### MIT License
- Free to use, but keep some conditions: [LICENSE](https://github.com/bokunimowakaru/m5Janken/blob/master/LICENSE)

### Copyright (c) 2019-2020 [Wataru KUNINO @ bokunimo.net](https://bokunimo.net)
