/*******************************************************************************
Janken 02 rnd for M5Stack ～ESP32マイコンとジャンケン対戦してみよう～

・前サンプルに、ジャンケン対戦機能を追加しました。

・本体LCD面のボタンを押すと、ボタンに応じたジャンケンの手を表示します。
・ESP32マイコンがランダムで手を表示します。

                                          Copyright (c) 2019-2020 Wataru KUNINO
********************************************************************************
【参考文献】
Arduino IDE 開発環境イントール方法：
https://docs.m5stack.com/en/quick_start/core2/arduino

M5Stack Arduino Library API 情報：
https://docs.m5stack.com/en/api/core2/system
*******************************************************************************/

#include <M5Core2.h>                            // M5Stack用ライブラリ組み込み

void disp(String filename, String msg=""){      // LCDにJPEGファイルを表示する
    drawJpgHeadFile(filename);                  // filenameに応じた画像をLCD表示
    M5.Lcd.drawCentreString(msg, 160, 96, 4);   // 中央にメッセージ文字列を表示
}

void setup(){                                   // 起動時に一度だけ実行する関数
    M5.begin();                                 // M5Stack用ライブラリの起動
    M5.Lcd.setTextColor(TFT_BLACK);             // テキスト文字を黒に設定
    disp("janken8","Example 02 Janken");        // 背景＋タイトルを表示
}

void loop(){                                    // 繰り返し実行する関数
    int jan = -1;                               // ユーザの手(未入力-1)
    int ken = (int)(random(3) * 2.5);           // ESP32マイコンの手
    
    M5.update();                                // ボタン情報を更新
    if(M5.BtnA.wasPressed()){                   // ボタンAが押されていた時
        jan = 0;                                // グー(0本指)
    }
    if(M5.BtnB.wasPressed()){                   // ボタンBが押されていた時
        jan = 2;                                // チョキ(2本指)
    }
    if(M5.BtnC.wasPressed()){                   // ボタンCが押されていた時
        jan = 5;                                // パー(5本指)
    }
    if(jan >= 0){                                   // ボタンが押された
        disp("janken" + String(jan), "Shoot!");     // 変数janに応じた表示
        delay(500);                                 // 0.5秒の待ち時間
        disp("janken" + String(jan) + String(ken)); // ESP32マイコンの手を表示
    }
}

