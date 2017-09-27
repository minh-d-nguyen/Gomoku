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

	def make_move(self):
		max_score = -100
		max_row = -1
		max_col = -1

		if self.board.is_empty():
			mid = self.board.size/2
			self.board.place(self.player_num, mid, mid)
			return

		for i in range(self.board.size):
			for j in range(self.board.size):
				if self.in_range(i, j):
					curr_score = self.minimax(self.player_num, i, j, True)
					if curr_score > max_score:
						max_score = curr_score
						max_row = i
						max_col = j


		print("Max score: %d Row: %d Col: %d" % (max_score, max_row, max_col))
		if not self.board.is_full():
			self.board.place(self.player_num, max_row, max_col)

	def minimax(self, player_num, row, col, is_maximizing):
		self.board.place(player_num, row, col)
		if self.board.check_win() == self.player_num:
			self.board.erase(row, col)
			return 10
		if self.board.check_win() == -self.player_num:
			self.board.erase(row, col)
			return -10
		if self.board.is_full():
			self.board.erase(row, col)
			return 0

		if is_maximizing:
			best_score = -100
			for i in range(self.board.size):
				for j in range(self.board.size):
					if self.in_range(i, j):
						score = self.minimax(-player_num, i, j, False)
						best_score = max(best_score, score)

		else:
			best_score = 100
			for i in range(self.board.size):
				for j in range(self.board.size):
					if self.in_range(i, j):
						score = self.minimax(-player_num, i, j, True)
						best_score = min(best_score, score)

		self.board.erase(row, col)
		return best_score

	def in_range(self, row, col):
		if self.board.cell_value(row, col) != 0:
			return False

		if ((self.board.cell_value(row - 1, col) != 0 and 
			 self.board.cell_value(row - 1, col) != -10) or
			(self.board.cell_value(row + 1, col) != 0 and 
			 self.board.cell_value(row + 1, col) != -10) or
			(self.board.cell_value(row - 1, col - 1) != 0 and 
			 self.board.cell_value(row - 1, col - 1) != -10) or
			(self.board.cell_value(row - 1, col + 1) != 0 and 
			 self.board.cell_value(row - 1, col + 1) != -10) or
			(self.board.cell_value(row + 1, col - 1) != 0 and 
			 self.board.cell_value(row + 1, col - 1) != -10) or
			(self.board.cell_value(row + 1, col + 1) != 0 and 
			 self.board.cell_value(row + 1, col + 1) != -10) or
			(self.board.cell_value(row, col - 1) != 0 and 
			 self.board.cell_value(row, col - 1) != -10) or
			(self.board.cell_value(row, col + 1) != 0 and 
			 self.board.cell_value(row, col + 1) != -10)):
			# (self.board.cell_value(row - 2, col) != 0 and 
			#  self.board.cell_value(row - 2, col) != -10) or
			# (self.board.cell_value(row + 2, col) != 0 and 
			#  self.board.cell_value(row + 2, col) != -10) or
			# (self.board.cell_value(row - 2, col - 2) != 0 and 
			#  self.board.cell_value(row - 2, col - 2) != -10) or
			# (self.board.cell_value(row - 2, col + 2) != 0 and 
			#  self.board.cell_value(row - 2, col + 2) != -10) or
			# (self.board.cell_value(row + 2, col - 2) != 0 and 
			#  self.board.cell_value(row + 2, col - 2) != -10) or
			# (self.board.cell_value(row + 2, col + 2) != 0 and 
			#  self.board.cell_value(row + 2, col + 2) != -10) or
			# (self.board.cell_value(row, col - 2) != 0 and 
			#  self.board.cell_value(row, col - 2) != -10) or
			# (self.board.cell_value(row, col + 2) != 0 and 
			#  self.board.cell_value(row, col + 2) != -10)):
			return True

		return False
