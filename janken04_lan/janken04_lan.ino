/*******************************************************************************
Janken 04 lan for M5Stack ～ローカル・ネットワーク・ジャンケン対決～

・同じWi-Fiアクセスポイントに接続した複数のM5Stackで通信対決
　※M5Stackが1台しかない場合は、PCやRaspberry Piを対向機として使用することも可能
　（udp_sender_janken.pyを実行）

                                          Copyright (c) 2020 Wataru KUNINO
*******************************************************************************/

#include <M5Stack.h>                            // M5Stack用ライブラリの組み込み
#include <WiFi.h>                               // ESP32用WiFiライブラリ
#include <WiFiUdp.h>                            // UDP通信を行うライブラリ
#define SSID "1234ABCD"                         // 無線LANアクセスポイントのSSID
#define PASS "password"                         // パスワード
#define PORT 1024                               // UDP送受信ポート番号
#define DEVICE "janke_1,"                       // デバイス名(5字+"_"+番号+",")

WiFiUDP udp;                                    // UDP通信用のインスタンスを定義
int jan = 8;                                    // ユーザの手(保持用)
int ken = 8;                                    // 対戦相手の手(保持用)

void disp(String filename, String msg=""){      // LCDにJPEGファイルを表示する
    filename = "/" + filename + ".jpg";         // 先頭に/、後に拡張子jpgを追加
    M5.Lcd.drawJpgFile(SD, filename.c_str());   // 配列型文字列変数sの画像を表示
    M5.Lcd.drawCentreString(msg, 160, 96, 4);   // 中央にメッセージ文字列を表示
}

void setup(){                                   // 起動時に一度だけ実行する関数
    M5.begin();                                 // M5Stack用ライブラリの起動
    M5.Lcd.setTextColor(TFT_BLACK);             // テキスト文字を黒に設定
    disp("janken","Connecting to Wi-Fi");       // 背景＋接続中表示
    WiFi.mode(WIFI_STA);                        // 無線LANをSTAモードに設定
    WiFi.begin(SSID,PASS);                      // 無線LANアクセスポイントへ接続
    while(WiFi.status() != WL_CONNECTED);       // 接続に成功するまで待つ
    disp("janken88","Example 04 Janken");       // 持ち手＋タイトルを表示
    udp.begin(PORT);                            // UDP通信御開始
}

void loop(){                                    // 繰り返し実行する関数
    int pong = -1;                              // 手(未入力-1)
    M5.update();                                // ボタン情報を更新
    if(M5.BtnA.wasPressed()) pong = 0;          // ボタンAのときはグー(0本指)
    if(M5.BtnB.wasPressed()) pong = 2;          // ボタンBのときはチョキ(2本指)
    if(M5.BtnC.wasPressed()) pong = 5;          // ボタンCのときはチョキ(5本指)
    
    /* ジャンケン送信部 */
    IPAddress IP = WiFi.localIP();              // IPアドレスを取得
    IP[3] = 255;                                // ブロードキャストに(簡易)変換
    if(pong >= 0){                              // ボタンが押された
        udp.beginPacket(IP, PORT);              // UDP送信先を設定
        udp.print(DEVICE);                      // 「Janke,」を送信
        udp.println(pong);                      // 手を送信
        udp.endPacket();                        // UDP送信の終了(実際に送信する
        disp("janken" + String(pong) + String(ken),"Shoot!");   // 液晶へ表示
        jan = pong;                             // 出した手を保持する
    }

    /* ジャンケン受信部 */
    int len = udp.parsePacket();                // 受信パケット長を変数lenに代入
    String ip_S = String(udp.remoteIP()[3]);    // 送信者IPアドレスの末尾を代入
    if(len == 0) return;                        // 未受信のときはloop()の先頭へ
    char s[11];                                 // 受信データ用変数(10文字まで)
    memset(s, 0, 11);                           // 文字列変数sの初期化
    udp.read(s, 10);                            // 受信データを文字列変数lcdへ
    udp.flush();                                // UDP受信バッファを破棄する
    if(strncmp(s,DEVICE,8)) return;             // 先頭8字が不一致時に先頭へ戻る
    pong = atoi(&s[8]);                         // 受信した数値を変数pongへ代入
    if(pong == 0 || pong == 2 || pong == 5){    // pongが0または2、5のときに
        disp("janken" + String(jan) + String(pong), "Recieved from " + ip_S);
        ken = pong;                             // kenを更新
    }
}
