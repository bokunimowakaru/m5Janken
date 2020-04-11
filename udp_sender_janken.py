#!/usr/bin/env python3
# coding: utf-8
# UDPでジャンケンデータを送信する
#
# (1) 1回だけ送信したいときは echo "0"または"2"、"5"を使って実行する
#       echo "0" | ./udp_sender_janken.py
#
# (2) ランダム値を連続で送信したいときは whileを使用し、以下のように実行する
#       while true; do echo ""|./udp_sender_janken.py; sleep 5; done
#
# (3) 手入力値を何度も実行したいときは、プログラムだけを実行し、送信したい
#     数値(0/2/5)＋[Enter]をキーボードから入力する。（数値が無ければ、ランダム）
#       ./udp_sender_janken.py
#
# Copyright (c) 2018-2020 Wataru KUNINO

import sys
import socket
from random import randrange
device = "janke_3,"

argc = len(sys.argv)                                    # 引数の数をargcへ代入
print('UDP Sender janken')
print('Usage: ' + sys.argv[0] + ' [port]')
print('       echo "0 or 2 or 5"|' + sys.argv[0])
print('       while true; do echo ""|./udp_janken.py; sleep 5; done')
if argc == 2:                                           # 入力パラメータ数の確認
    port = sys.argv[1]                                  # ポート番号を設定
    if port < 1 or port > 65535:                        # ポート1未満or65535超の時
        port = 1024                                     # UDPポート番号を1024に
else:
    port = 1024

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # ソケットを作成
sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST,1)
if sock:                                                # 作成に成功したとき
    for line in sys.stdin:                              # 標準入力から変数lineへ
        udp = device                                    # 表示用の文字列変数udp
        for c in line:                                  # 入力行内
            if ord(c) >= ord(' '):                      # 表示可能文字
                udp += c                                # 文字列strへ追加
        if(len(udp) <= 8):
            udp += str((int)(randrange(3) * 2.5))       # 0 or 2 or 5を乱数で生成
        print('send : ' + udp)                          # 受信データを出力
        udp=(udp + '\n').encode()                       # バイト列に変換
        sock.sendto(udp,('255.255.255.255',port))       # UDPブロードキャスト送信
    sock.close()                                        # ソケットの切断
