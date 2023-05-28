請使用小黑窗來開啟exe檔，而啟動踩地雷分為兩種模式。

1.指令檔模式 : 輸入指令檔，將所有輸出寫入輸出檔
格式 : MineSweeper.exe CommandFile <輸入指令檔> <輸出檔>
EX : MineSweeper.exe CommandFile command.txt output.txt

2.輸入指令模式 : 用cin輸入指令，cout輸出結果
格式 : MineSweeper.exe CommandInput

指令有以下幾種：
1. Load 
載入盤面檔
Load BoardFile <盤面檔相對路徑>
EX : Load BoardFile board.txt
指定地雷數量
Load RandomCount <M> <N> <炸彈數量>
EX : Load RandomCount 9 9 7
指定地雷生成機率
Load RandomRate <M> <N> <炸彈生成機率>
EX : Load RandomRate 9 9 0.3

2.Print
有七種資訊可顯示
Print GameBoard
Print GameState
Print GameAnswer
Print BombCount
Print FlagCount
Print OpenBlankCount
Print RemainBlankCount

3.Left/RightClick
開啟格子
格式 : LeftClick <row> <col>
EX : LeftClick 2 3
標註旗幟/問號，若被標註為旗幟，則不能被開啟
第一次右鍵標註旗幟，第二次右鍵標註問號，第三次右鍵回復無標註
格式 : RightClick <row> <col>
EX : RightClick 2 3

4.Replay
在遊戲結束後，重新進行新一輪的遊戲

5.Quit
在遊戲結束後，關閉整個程式


