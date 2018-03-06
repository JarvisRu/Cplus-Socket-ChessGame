# Cplus-Socket-ChessGame
Using Cplus to implement socket program as a chess game

#### 1. The chess board is like

&nbsp;&nbsp;&nbsp; o &nbsp;&nbsp; o &nbsp;&nbsp; o<br>
&nbsp;&nbsp;&nbsp; o &nbsp;&nbsp; o &nbsp;&nbsp; o<br>
&nbsp;&nbsp;&nbsp; o &nbsp;&nbsp; o &nbsp;&nbsp; o

#### 2. This is a double game
  * Placing chess one by one
  * After placing three chess, player can move own chess to the neighbor
  * It's win by the first player who place three chesses in a straight line
  
#### 3. Program Steps
  1. Open server.exe first
  2. Choose using localhost or seting address by yourself
  3. Open client.exe
  4. As step (2)
  5. server waiting / client read the rule then enter the game
  6. Game start !!
  
#### 4. How to placing/moving the chess
  * Chess Type
    * Server : ★
    * Client : ▲
  * Placing
    * Enter : [1~9] 0 0
    * the first number represent the location which you wanna place
    
    &nbsp;&nbsp;&nbsp; 0 &nbsp;&nbsp; 0 &nbsp;&nbsp; 0 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 1 &nbsp;&nbsp; 2 &nbsp;&nbsp; 3<br>
    &nbsp;&nbsp;&nbsp; 0 &nbsp;&nbsp; 0 &nbsp;&nbsp; 0 &nbsp;→&nbsp;&nbsp;4 &nbsp;&nbsp; 5 &nbsp;&nbsp; 6<br>
    &nbsp;&nbsp;&nbsp; 0 &nbsp;&nbsp; 0 &nbsp;&nbsp; 0 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 7 &nbsp;&nbsp; 8 &nbsp;&nbsp; 9
    * ex: placing on (2) → 2 0 0
  * Moving
    * Enter : [from] 0 [to]
      * ex: from location (1) to (5) → 1 0 5
    
