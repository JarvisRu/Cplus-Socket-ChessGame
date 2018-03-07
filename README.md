# Cplus-Socket-ChessGame
Using Cplus to implement socket program as a chess game

#### 1. The chess board is like
<img src="https://user-images.githubusercontent.com/20190523/37088192-85b2aee4-2237-11e8-8a5f-b18ab5d6113a.png" width="300">

#### 2. This is a double game
  * Placing chess one by one
  * After placing three chess, player can move own chess to the neighbor
  * It's win by the first player who place three chesses in a straight line
  
#### 3. Program Steps
 1. Open server.exe first 
   <img src="https://user-images.githubusercontent.com/20190523/37087676-fa21d52c-2235-11e8-9a60-628be47aff99.png" width="750">
 2. Choose using localhost or seting address by yourself (enter 1 or 2) 
   <img src="https://user-images.githubusercontent.com/20190523/37087779-3b6abe22-2236-11e8-966e-657c77df72bf.png" width="750">
 3. Open client.exe, as step (2)<br> 
 4. server waiting / client read the rule then enter the game 
   <img src="https://user-images.githubusercontent.com/20190523/37087987-d0bd4530-2236-11e8-9ee3-0d3795c5311f.png" width="750">
   <img src="https://user-images.githubusercontent.com/20190523/37087942-b70293ca-2236-11e8-93b9-6072adf25295.png" width="750">
 5. Game start !!
  
#### 4. How to placing/moving the chess
  * Chess Type
    * Server : ★
    * Client : ▲
  * Placing
    * Enter : [1~9] 0 0
    * the first number represent the location which you wanna place
     <img src="https://user-images.githubusercontent.com/20190523/37089037-43e35b00-223a-11e8-9ecb-87b43be6f78f.png" width="300">
     
    * ex: placing on (2) → 2 0 0
     <img src="https://user-images.githubusercontent.com/20190523/37088696-33ea9a70-2239-11e8-8506-e7f1996afe0b.png" width="300">
     <img src="https://user-images.githubusercontent.com/20190523/37088727-51c8981c-2239-11e8-87bd-3c9d41f967cb.png" width="300">
  * Moving
    * Enter : [from] 0 [to]
     ex: from location (1) to (5) → 1 0 5
     <img src="https://user-images.githubusercontent.com/20190523/37089189-ad5ddff6-223a-11e8-80f5-abcb4023bf40.png" width="300">
     <img src="https://user-images.githubusercontent.com/20190523/37089233-d6819d00-223a-11e8-8fdd-080112f7133a.png" width="300">
    
