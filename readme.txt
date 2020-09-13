総合学園ヒューマンアカデミー仙台校 
ゲームカレッジ・プログラマー専攻　2年　佐藤　雄希
作成日：2020/09/12

●タイトル　『MECHA SLAYER（メカスレイヤー）』

●バージョン　1.2

●動作環境
　 ・最低動作PCスペック
　	　　・Windows10での動作確認済
　　　　　　　ディスプレイ解像度:1280×720以上 
	      Core 2 Duo 4GB
　 ・推奨スペック
　	      OS:Windows10
              ディスプレイ解像度:1280×720以上
              CPU : Intel Core i7 2.20 GHz
　　　　　　　メモリ： 8.00 GB RAM

●開発環境
　DirectX9.0c

●使用エディター
　VisualStudio2019(C++)

●ファイル構成
　　　EXE
      MyClass
　　　MECHASLAYER_操作マニュアル.png
　　　readme.txt
      アピールポイント動画.mp4
　　　クラス図.png
      


●起動方法
　　・ 「EXE」 フォルダの「MECHA SLAYER.exe」ファイルを起動してください。
       フルスクリーン機能はありません（ゲーム画面は1280×720固定です）

    ・ YouTubeの下記のURLからもデモムービー（高画質）を見ることもできます。
       https://youtu.be/7Vq2XatXECE

●ゲーム概要
　　・制限時間内に闘技場に出現する敵をプレイヤーを操作し倒すTPS視点の3Dアクションゲームです。。
　　　　　
●簡単なルール、操作方法

【ルール】
    ・主人公のプレーヤーを操作して、フィールドに出現する敵を全て倒したらゲームクリアとなります。

　　・制限時間は２分です。

　　・敵の攻撃に当たるとプレーヤーのHPが減少し、HPゲージが空になった場合ゲームオーバーになります。
　　
　　・敵の攻撃をダッシュや回避アクションを用いて避けながら、敵にダメージを与えます。

    ・敵はプレーヤーの攻撃を複数回当てると倒すことができます。
　
　　・必殺技を当てると敵のHPに関係なく、1回で倒すことができますが、SPゲージが満タンの時のみ使用可能です。
   


【操作方法】

　◆ゲームパッド操作（Xboxのコントローラーを想定）
　　　　　　　　　　　　　　
　　	Bボタン　 ………　攻撃

        LBボタン　 ……… 回避

        LTボタン　 ……… ダッシュ（長押し）　　※RTボタンも押しているとダッシュ状態が解除されます。

　　　　左アナログスティック　………　プレイヤー移動

　　　　右アナログスティック　………　カメラの移動

●担当箇所
  プログラム全般
  エフェクトの作成
　一部UIの作成（操作説明画面）

●製作者に関する情報

　ゲームカレッジ２年
	○プログラマー  佐藤　雄希
　　　　〇デザイナー    吉田　太一
　　　　　　　　　　    吉崎　龍哉

●プログラミングした際に注力した点
 
  ・プレイヤーや敵の動ぎ、カメラの挙動については、既存のゲームを研究しプログラムに落とし込みました。

　・ダッシュ攻撃は通常攻撃より使いやすいですが、攻撃後の隙が大きくなるリスクも伴うなどの、プレイヤーが
　　プレイしながら考える要素も取り入れました。

　・デザインパターン
　　オブジェクト指向の考えで作られたデザインパターンを使用して、柔軟かつ再利用できる設計にしたいと
　　考えデザインパターンを使用しました。今回はsingleton,Observerを使用しました。
　　又、現在も他のデザインパターンも導入してソースコードを改良中です。

●プログラミングで苦労した点
　・壁ズリプログラム
　　壁や敵に近づいた際に、距離を測定するためのレイを複数出し、プレイヤーを壁ズリするようにプログラムしました。
　　また、実際に見える背景とは別にローポリゴンの判定用壁にレイを飛ばすことで、処理の負担を軽減するようにしました。

●作成ファイル
　「MyClass」に入っているプログラムは全て自分で作成しました。
　それ以外のファイルデータは学校で用意されたものです。
　ファイル名一覧　　
  BaseScene.h
  CameraMain.cpp
  CameraMain.h
  CollisionEnemy.cpp
  CollisionEnemy.h
  EffeksserManager.cpp
  EffeksserManager.h
  Enemy.cpp
  Enemy.h
  EnemyManager.cpp
  EnemyManager.h
  Enum.h
  GameMain.cpp
  GameMain.h
  Ground.cpp
  Ground.h
  MainScene.cpp
  MainScene.h
  MyLight.cpp
  MyLight.h
  Observer.h
  Player.cpp
  Player.h
  ResultManager.cpp
  ResultManager.h
  SceneManager.cpp
  SceneManager.h
  SeManager.cpp
  SeManager.h
  TimeManager.cpp
  TimeManage.h
  TitleScene.cpp
  TitleScene.h
  UiManager.cpp
  UiManager.h

●既知の不具合

　・無し