# m5Janken: M5Stack Janken 猜拳 Examples by Wataru KUNINO

M5Stack用のジャンケン（ジャイケン）・プログラム集です。  
Let's learn Janken Programing with IoT ready M5Stack.  

1. janken01_pict：本体LCD面のボタンを押すと、ボタンに応じたジャンケンの手を表示します
2. janken02_rnd：ESP32マイコンがランダムで手を表示し、ジャンケン対戦が出来ます
3. janken03_game：ジャンケン対戦の勝敗および得点を表示することで、ゲームらしさを増やします
4. janken04_lan：同じWi-Fiアクセスポイントに接続した2台のM5Stackで通信対決します
5. janken05_net：クラウド・サーバのジャンケン・アルゴリズムとの対戦が出来ます

### Janken

Janken (or Rock Paper Scissors) is a pupluer game in Japan:
- Three hand's elements, ROCK, PAPER, SCISSORS are shaped by fingers.
- A player throws one of the elements.
- Simultaneously, the other player (or Janken Server) also throws.
- Throwed ROCK will win from SCISSORS hand, but it will lose PAPER hand.

## 対応 M5Stack

- M5Stack BASIC  
- M5Stack GLAY  
- M5Stack Core2 (core2フォルダに収録)  

## M5Stack Janken 猜拳 Examples の使い方

- プログラムは Arduino IDE でコンパイルしてください
- 「janken_pict」フォルダ内の画像ファイルをMicro SDカードの直下ディレクトリにコピーしてください

## Arduino IDE 用 M5Stack 開発環境
Arduino IDE用のM5Stackの開発環境をセットアップする方法は、下記のM5Stack公式サイトをご覧ください。  

- イントール方法：  
	（日本語）https://github.com/m5stack/M5Stack/blob/master/docs/getting_started_ja.md  
	（最新版・英語）https://docs.m5stack.com/#/en/related_documents/Arduino_IDE  
	1. Arduino IDE  
	2. USB/UARTシリアル変換ドライバ  
	3. ESP32ボードマネージ  
	4. M5Stackライブラリ  
  
Arduino IDEの[ツール］メニュー内の［ボード］で、［M5Srack-Core-ESP32］を選択してください。

### Usage of Janken Server
下記のサイトのジャンケン・サーバを使用します。

	Usage: https://bokunimo.com/janken/?user=YOURNAME&throw=X (X = G or C or P)  

- 説明, Usage：  
	https://bokunimo.com/janken/  

- グー(throw=G), ROCK：  
	https://bokunimo.com/janken/?throw=G  

- チョキ(throw=C), SCISSORS：  
	https://bokunimo.com/janken/?throw=C  

- パー(throw=P), PAPER：  
	https://bokunimo.com/janken/?throw=P  

## ご注意
- janken05_netは、クラウド・サーバへSSIDの一部(後部4文字)またはニックネームを送信します
（詳細についてはソースコード内の説明をお読みください）
- 自由に利用できますが、無保証です。詳細はソースコード、README、[LICENSE](https://github.com/bokunimowakaru/m5Janken/blob/master/LICENSE)をご覧ください

### MIT License
- Free to use, but keep some conditions: [LICENSE](https://github.com/bokunimowakaru/m5Janken/blob/master/LICENSE)

### Copyright (c) 2019-2020 [Wataru KUNINO @ bokunimo.net](https://bokunimo.net)
