/*******************************************************************************
Janken 03 msg for M5Stack ～ジャンケン対戦の勝敗を表示してみよう～

・本体LCD面のボタンを押すと、ボタンに応じたジャンケンの手を表示します。
・ESP32マイコンがランダムで手を表示します。
・勝ち負けを表示します。

                                          Copyright (c) 2019-2020 Wataru KUNINO
********************************************************************************
【参考文献】
Arduino IDE 開発環境イントール方法：
https://github.com/m5stack/M5Stack/blob/master/docs/getting_started_ja.md
https://docs.m5stack.com/#/en/related_documents/Arduino_IDE

M5Stack Arduino Library API 情報：
https://docs.m5stack.com/#/ja/api
https://docs.m5stack.com/#/en/arduino/arduino_api
*******************************************************************************/

#include <M5Stack.h>                            // M5Stack用ライブラリの組み込み

void disp(String filename, String msg=""){      // LCDにJPEGファイルを表示する
    char s[14] = "/";                           // 13文字収容可能な文字列変数
    filename.toCharArray(s + strlen(s),9);      // ファイル名を配列変数sへ変換
    strncat(s, ".jpg", 5);                      // 配列型文字列変数sに.jpgを追加
    M5.Lcd.drawJpgFile(SD, s);                  // 配列型文字列変数sの画像を表示
    M5.Lcd.drawCentreString(msg, 160, 96, 4);   // 中央にメッセージ文字列を表示
}

void setup(){                                   // 起動時に一度だけ実行する関数
    M5.begin();                                 // M5Stack用ライブラリの起動
    M5.Lcd.setTextColor(TFT_BLACK);             // テキスト文字を黒に設定
    disp("janken8","Example 03 Janken");        // 背景＋タイトルを表示
}

void loop(){                                    // 繰り返し実行する関数
    int jan = -1;                               // ユーザの手(未入力-1)
    int ken = (int)(random(3) * 2.5);           // ESP32マイコンの手
    
    M5.update();                                // ボタン情報を更新
    if(M5.BtnA.wasPressed()) jan = 0;           // ボタンAのときはグー(0本指)
    if(M5.BtnB.wasPressed()) jan = 2;           // ボタンBのときはチョキ(2本指)
    if(M5.BtnC.wasPressed()) jan = 5;           // ボタンCのときはチョキ(5本指)
    if(jan < 0) return;                         // ボタンが押されてなければ戻る
    
    disp("janken" + String(jan), "Shoot!");     // 変数janに応じた表示
    delay(500);                                 // 0.5秒の待ち時間
    disp("janken" + String(jan) + String(ken)); // 変数janと変数kenに応じた表示
    delay(500);                                 // 0.5秒の待ち時間
    
    String msg = "Draw";                        // 変数msgに「引き分け」を代入
    if((jan / 2 + 1) % 3 == (ken / 2) ){        // ユーザの方が強い手のとき
        msg = "You Win";                        // 「勝ち」
    }else if(jan != ken){                       // 勝ちでも引き分けでも無いとき
        msg = "You Lose";                       // 「負け」
    }
    M5.Lcd.drawCentreString(msg, 160, 96, 4);   // 勝敗を表示
}

