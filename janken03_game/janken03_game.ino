/*******************************************************************************
Janken 03 game for M5Stack ～ジャンケン対戦の勝敗を表示してみよう～

・前サンプルに、勝敗判定、得点をカウントする機能を追加しました。

・本体LCD面のボタンを押すと、ボタンに応じたジャンケンの手を表示します。
・ESP32マイコンがランダムで手を表示します。
・勝ち負けを表示します。

                                          Copyright (c) 2019-2020 Wataru KUNINO
*******************************************************************************/

#include <M5Stack.h>                            // M5Stack用ライブラリの組み込み

int score = 0;                                  // 勝ち得点
int debts = 0;                                  // 負け得点

void disp(String filename, String msg=""){      // LCDにJPEGファイルを表示する
    filename = "/" + filename + ".jpg";         // 先頭に/、後に拡張子jpgを追加
    M5.Lcd.drawJpgFile(SD, filename.c_str());   // 配列型文字列変数sの画像を表示
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
    delay(10);    // 誤作動防止(参考文献 github.com/m5stack/M5Stack/issues/52 )
    if(M5.BtnA.wasPressed()) jan = 0;           // ボタンAのときはグー(0本指)
    if(M5.BtnB.wasPressed()) jan = 2;           // ボタンBのときはチョキ(2本指)
    if(M5.BtnC.wasPressed()) jan = 5;           // ボタンCのときはパー(5本指)
    if(jan < 0) return;                         // ボタンが押されてなければ戻る
    
    disp("janken" + String(jan), "Shoot!");     // 変数janに応じた表示
    delay(500);                                 // 0.5秒の待ち時間
    disp("janken" + String(jan) + String(ken)); // 変数janと変数kenに応じた表示
    delay(500);                                 // 0.5秒の待ち時間
    
    String msg = "Draw";                        // 変数msgに「引き分け」を代入
    if((jan / 2 + 1) % 3 == (ken / 2)){         // ユーザの方が強い手のとき
        msg = "You Win";                        // 「勝ち」
        score += 1;                             // スコアに1点を追加
    }else if(jan != ken){                       // 勝ちでも引き分けでも無いとき
        msg = "You Lose";                       // 「負け」
        debts += 1;                             // 負け回数に1回を追加
    }
    M5.Lcd.drawCentreString(msg, 160, 88, 4);   // 勝敗を表示
    M5.Lcd.drawCentreString(String(score)+":"+String(debts), 160, 112, 4);
}

