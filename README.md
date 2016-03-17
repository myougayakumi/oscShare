# oscShare
very simple osc sharing app using openFrameworks

##これは何
ローカル内にある複数のpc同士でoscを送りたい時、全てのPCがosc receiveして、全てのPCが他のPCの数だけsender用意しなきゃいけなくて、ip固定とかめんどいし、puredataで接続するとき毎回やってると何かと面倒。  
このアプリ内で、PC間のOSCを簡単に繋げられる。

##どううごくのか
各PCのlocalhost 3000 に送られたoscメッセージが、自分含む全てのPCのport 3001 にそのまま伝えられる。
space押すと他PCからipアドレスとport番号要求する

##原理
ブロードキャスト経由で、自分自身のipアドレスとポート番号を伝えたり、要求したりして、相手のipとport保存しておいて、ofxOscでうまくやってる

##他
だるいので3000,3001でやってる。PCは10台までにしといた。必要があれば起動後に番号とか選べるようにするかも

# macのみ
windows版→[https://github.com/myougayakumi/oscShare](https://github.com/myougayakumi/oscShare)
