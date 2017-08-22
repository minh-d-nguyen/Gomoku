from __future__ import print_function
import gomokuBoard

class gomokuMinimaxAI:
	def __init__(self, player_num, board):

		self.cell_score = []
		self.player_num = player_num
		self.board = board

		for i in range(board.size):
			column = []
			for j in range(board.size):
				column.append(0)
			self.cell_score.append(column)
