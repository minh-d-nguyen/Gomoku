from __future__ import print_function
from gomokuBoard import GomokuBoard
from gomokuDefAI import gomokuDefAI

board = GomokuBoard(30)

x = gomokuDefAI(-1, board)
y = gomokuDefAI(1, board)
num_round = 0

while (board.check_win() == 0 and not board.is_full()):
	player_num = num_round % 2
	if player_num == 0:
		x.make_move()
		raw_input()
		# r, c = raw_input().strip().split(' ')
		# r, c = [int(r), int(c)]
		# board.place(-1, r, c)

	else:
		# raw_input()
		# y.make_move()
		r, c = raw_input().strip().split(' ')
		r, c = [int(r), int(c)]
		board.place(1, r, c)

	print("Round: %s" % (num_round + 1))
	board.print_board()
	num_round += 1
