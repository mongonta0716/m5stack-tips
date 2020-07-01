# m5stack-tips
 example for m5stack,m5stickc,m5atom

# Description
 動作を確認するためのサンプルです。使い方はソースを見てください。

 Samples for operation check etc.See source for usage.

# Contents
## SPIFFS_Sample
 SPIFFSへの読み書きを確認するサンプル

Sample to check reading and writing to SPIFFS

## M5StickC_AXP192_Test
 M5StickCの電源状態を監視してバッテリー駆動になったらIFTTT→LINE Notifyで通知する仕組みのサンプルです。

This is a sample of the mechanism to monitor the power status of M5StickC and notify by IFTTT → LINE Notify when the battery is driven.
### References
　参考にさせていただいた記事

 M5StickCのクラス仕様は[M5StickC非公式日本語リファレンス-電源管理(AXP192)](https://lang-ship.com/reference/unofficial/M5StickC/Class/AXP192/)[(@tnkmasayuki)](https://twitter.com/tnkmasayuki)

 certificate.hの作成はQiitaの[ESP32からIFTTTを使ってLINE Notifyで通知を送ってみた](https://qiita.com/mascii/items/4c366ad4709469d5fda9)[(@mascii)](https://qiita.com/mascii)

## M5Stack_ATTiny85_I2CTest
　M5StackとATTiny85をI2Cで接続し動作確認をするためのサンプル
　詳しくは[M5StackとATTiny85でI2C通信をする](https://raspberrypi.mongonta.com/howto-connect-m5stack-and-attiny85-via-i2c/)を見てください。

## M5Atom_Aquestalk
  M5AtomEchoで安全にAquesTalkを使うためのサンプル
  AquesTalk for ESP32のインストールが必要です。詳しくは[AquesTalk pico for ESP32
(AquesTalk-ESP)](https://www.a-quest.com/products/aquestalk_pico_esp32.html)を見てください。

## M5StickC_UIFlow_ServoTest
  M5StickCにサーボを取り付けて動作確認するためのプログラムです。

  GND-5Vout-G26にサーボを取り付けると動作します。

  秋月電子通商で購入できる[両端ロングピンヘッダ](https://github.com/mongonta0716/m5stack-tips)を使うとサーボのコネクタをそのまま接続することが可能です。

## M5Core_UIFlow_Servo_Test_faces_encoder
  M5StackCore+Faces+Encoderの組み合わせでサーボ単体をコントロールして動作チェックできます。

  BtnA:0°,BtnB:90°,BtnC:180°

  エンコーダーを回すと5°ずつ変化します。

  GPIO26にサーボのPWMを接続してください。FacesⅡBottomの場合は黒いGroveCポートからGND-5V-G26を取ることができます。
