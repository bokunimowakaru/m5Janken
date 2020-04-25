/*******************************************************************************
Janken 01 pict for M5Stack ～SDカード内の画像を表示してみよう～

・Micro SDカードに保存したJPEG画像を液晶ディスプレイに表示します。
・本体LCD面のボタンを押すと、ボタンに応じて読み込むファイル名を変更します。

・「janken_pict」フォルダ内の画像ファイルをMicro SDカードの直下ディレクトリに
　コピーしておくと、ボタンに応じたジャンケンの手を表示します。

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

void setup(){                                   // 起動時に一度だけ実行する関数
    M5.begin();                                 // M5Stack用ライブラリの起動
    M5.Lcd.drawJpgFile(SD, "/janken8.jpg");     // 背景を表示
    M5.Lcd.setTextColor(TFT_BLACK);             // テキスト文字を黒に設定
    M5.Lcd.println("Example 01 Janken");        // LCDにタイトルを表示
}

void loop(){                                    // 繰り返し実行する関数
    M5.update();                                // ボタン情報を更新
    if( M5.BtnA.wasPressed() ){                 // ボタンAが押されていた時
        M5.Lcd.drawJpgFile(SD, "/janken0.jpg"); // LCDにJPEGファイルを表示する
    }
    if( M5.BtnB.wasPressed() ){                 // ボタンBが押されていた時
        M5.Lcd.drawJpgFile(SD, "/janken2.jpg"); // LCDにJPEGファイルを表示する
    }
    if( M5.BtnC.wasPressed() ){                 // ボタンCが押されていた時
        M5.Lcd.drawJpgFile(SD, "/janken5.jpg"); // LCDにJPEGファイルを表示する
    }
}
