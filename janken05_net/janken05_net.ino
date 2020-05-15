/*******************************************************************************
Janken 05 net for M5Stack ～クラウド・サーバとジャンケン対決～

・クラウド・サーバ bokunimo.com に、Webインタフェース HTTP GET 接続

                                          Copyright (c) 2020 Wataru KUNINO
*******************************************************************************/

#include <M5Stack.h>                            // M5Stack用ライブラリの組み込み
#include <WiFi.h>                               // ESP32用WiFiライブラリ
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include "root_ca.h"

#define SSID "1234ABCD"                         // 無線LANアクセスポイントのSSID
#define PASS "password"                         // パスワード
#define URL  "https://bokunimo.com/janken/"     // クラウドサービスのURL


/*******************************************************************************
SSIDを送信したくない場合は、下記の USER にニックネームなどを入力してください。
*******************************************************************************/

String USER = "";                               // クラウドへ送信するユーザ名

/*******************************************************************************
ユーザ名 USER は、半角英文字と数字、8文字までを、"と"の中に入力してください。
例） String USER = "wataru";
********************************************************************************
ユーザ名 USER は下記の目的でアクセス元の端末を特定するために使用します。
なるべく実名を避け、ニックネームなどを使用してください。
（デフォルトでは、SSIDの一部(後部4文字)をユーザ名として利用します）
クラウド・サーバとの通信にはHTTPSを使用し、ユーザ名などの情報は

【利用目的・用途】
・ジャンケンの手の学習用
・ジャンケン・アルゴリズムの改良
・ランキング表示や対戦時の表示用
・その他、ネット・サービスの開発用

【ご注意】
・当方の過失による流出については責任を負いません
・データ消失については責任を負いません（誤った削除依頼で消失する場合もあります）
・削除依頼については対応しますが、適正な依頼かどうかは当方の判断に基づきます

同意いただけない場合は、当該クエリ（user=）を削除してください。
*******************************************************************************/

int score = 0;                                  // 勝ち得点
int debts = 0;                                  // 負け得点
int rate  = 0;                                  // 勝率

void disp(String filename, String msg=""){      // LCDにJPEGファイルを表示する
    filename = "/" + filename + ".jpg";         // 先頭に/、後に拡張子jpgを追加
    M5.Lcd.drawJpgFile(SD, filename.c_str());   // 配列型文字列変数sの画像を表示
    M5.Lcd.drawCentreString(msg, 160, 96, 4);   // 中央にメッセージ文字列を表示
}

void setup() {
    M5.begin();                                 // M5Stack用ライブラリの起動
    M5.Lcd.setTextColor(TFT_BLACK);             // テキスト文字を黒に設定
    disp("janken","Connecting to Wi-Fi");       // 背景＋接続中表示
    WiFi.mode(WIFI_STA);                        // 無線LANをSTAモードに設定
    WiFi.begin(SSID,PASS);                      // 無線LANアクセスポイントへ接続
    while(WiFi.status() != WL_CONNECTED);       // 接続に成功するまで待つ
    disp("janken88","Example 05 Janken");       // 持ち手＋タイトルを表示
    if(USER == "") USER = String(SSID).substring(String(SSID).length()-4);
}

void loop(){                                    // 繰り返し実行する関数
    int jan = -1;                               // ユーザの手(未入力-1)
    int ken=8;
    
    M5.update();                                // ボタン情報を更新
    if(M5.BtnA.wasPressed()) jan = 0;           // ボタンAのときはグー(0本指)
    if(M5.BtnB.wasPressed()) jan = 2;           // ボタンBのときはチョキ(2本指)
    if(M5.BtnC.wasPressed()) jan = 5;           // ボタンCのときはパー(5本指)
    if(jan < 0) return;                         // ボタン押下無し時に戻る
    disp("janken" + String(jan), "Shoot!");     // 変数janに応じた表示
    
    /* クラウドへの接続処理 */
    String S = String(URL);                     // HTTPリクエスト用の変数
    S += "?user=" + USER;                       // ユーザ名のクエリを追加
    S += "&throw="+ String(jan);                // ジャンケンの手を追加
    Serial.println("HTTP GET " + S);            // シリアルへリクエストを出力
    WiFiClientSecure client;                    // TLS/TCP/IP接続部の実体を生成
    client.setCACert(rootCACertificate);        // ルートCA証明書を設定
    HTTPClient https;                           // HTTP接続部の実体を生成
    https.begin(client, S);                     // 初期化と接続情報の設定
    int httpCode = https.GET();                 // HTTP接続の開始
    S = "HTTP Status " + String(httpCode);      // HTTPステータスを変数Sへ代入
    S += "\n" + https.getString();              // 改行と受信結果を変数Sへ追加
    Serial.println(S);                          // シリアルへ出力
    if(httpCode == 200){                        // HTTP接続に成功したとき
        ken = S.substring(S.indexOf("\"net\":")+12).toInt();
        rate = S.substring(S.indexOf("\"win rate\":")+12).toInt();
    }                                           // 受信結果Sの手と勝率を各変数へ
    https.end();                                // HTTPクライアントの処理を終了
    client.stop();                              // WiFi
    
    /* 勝敗判定・表示処理 */
    String msg = "Draw";                        // 変数msgに「引き分け」を代入
    if((jan / 2 + 1) % 3 == (ken / 2)){         // ユーザの方が強い手のとき
        msg = "You Win";                        // 「勝ち」
        score += 1;                             // スコアに1点を追加
    }else if(jan != ken){                       // 勝ちでも引き分けでも無いとき
        msg = "You Lose";                       // 「負け」
        debts += 1;                             // 負け回数に1回を追加
    }
    if(rate) msg += ", rate=" + String(rate);   // 勝率をmsgへ追加
    disp("janken"+String(jan)+String(ken),msg); // 画像と勝敗表示を更新
}
