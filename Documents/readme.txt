U22プログラミングコンテストに提出した作品です。

使用ツール：DirectX11
開発期間：2020年7月～2020年8月 (2か月)
動作環境：Windows、DirectX11

苦労した点：C++を学び始めたばかりだったのでクラスを理解するのに苦労しました。
工夫した点：初めてのグループ制作（2人）だったので密に連絡を取り合いコードの衝突が起きないように
	　　注意を払いながら制作しました。

落ちているリンゴを拾ってキャラ固有の能力を発動してギミックを攻略し、
ステージをクリアしていくゲームです。

キャラクターの性能やギミックについて：
Hit or Away.mp4のご視聴お願いします。

操作方法
十字キー：移動
A：能力発動（発動条件はキャラによりことなる）
S：キャラ切り替え（ステージによってはできない）
Q：ポーズ

作成箇所
Enemyに関する処理全般
{
	AttackState.cpp,h
	AttackWaitState.cpp,h
	ChaseState.cpp,h
	DiscoveryState.cpp,h
	Enemy.cpp,h
	HierarchyState.h
	MoveState.cpp,h
	PatrolState.cpp,h
	State.h
	WaitState.cpp.h
}
csv読み込みに関する処理・設計（stage.cpp,h ,フォルダ(database)）
エフェクトに関する処理(Effect.cpp,h , effectList.cpp,h)
Timer.cpp,h
Camera.cpp.h

参考にしたもの
・新・標準プログラマーズライブラリ C++ クラスと継承 完全制覇
https://www.yttm-work.jp/game_ai/game_ai_0003.html

アピールポイント：
■ゲーム部分
・チュートリアル的なステージから始まり徐々に難易度が上がるように制作しました。
・キャラクラーの能力発動を拾ったリンゴ分しかできないようにして、リソース管理とパズル要素を融合させて
　単調なゲームではないようにしました。

■プログラム部分
・データベースを作成してステージごとにゲームルールやオブジェクトの配置を
　CSVファイルの値をいじるだけで反映できるように作りました。
　これによって短時間で複数ステージが作成できるようになりました。
