Gomoku Project
by: Minh D. Nguyen

I. Description
- This project seeks to utilize multiple approaches to implement an AI for the game Gomoku. The AIs of different approaches will then be compared

II. List of AIs:
1. Defensive move score (in "DefAIPython"):
- Description: For each turn, calculate the move score of each cell (the higher the score, the
better the move reflect the implementer's strategy). The move score calculation rule is set by
the implementer.
- Performance:
  Good:
  +) Very fast.
  +) With good move score rule, the AI can be very hard to beat.
  Bad:
  +) Cannot learn from former mistake, which means if we discover a way to win against the AI,
  we can win against it every time using the same sequence of move.
  +) Very hard to improve. In situation that requires the score calculation rule to be improved,
  it's not obvious how we can improve it.

2. Minimax AI (in "MinimaxAIPython"):
- Description: For each turn, figure out the most optimal move by using the Minimax Algorithm.
- Performance:
  Good:
  +) Very smart. Does not need to "learn".
  +) In theory, if it goes first, it can at least force the game to a draw.
  Bad:
  +) Dreadfully slow. Almost impractical for Gomoku without a lot of optimizations.