from __future__ import print_function

class GomokuBoard():
	def __init__(self, size):
		self.size = size
		self.board = []

		for i in range(size):
			column = []
			for j in range(size):
				column.append(0)
			self.board.append(column)

	def is_empty(self):
		for i in range(self.size):
			for j in range(self.size):
				if self.cell_value(i, j) != 0:
					return False

		return True

	def check_win(self):

		def check_cell(board, size, row, col):

			# Check the row
			if (col <= size - 5):
				if (board[row][col + 1] == board[row][col] and
					board[row][col + 2] == board[row][col] and
					board[row][col + 3] == board[row][col] and
					board[row][col + 4] == board[row][col]):
					return board[row][col];

			# Check the column
			if (row <= size - 5):
				if (board[row + 1][col] == board[row][col] and
					board[row + 2][col] == board[row][col] and
					board[row + 3][col] == board[row][col] and
					board[row + 4][col] == board[row][col]):
					return board[row][col]

			# Check the diagonals
			if (row <= size - 5 and col <= size - 5):
				if (board[row + 1][col + 1] == board[row][col] and
					board[row + 2][col + 2] == board[row][col] and
					board[row + 3][col + 3] == board[row][col] and
					board[row + 4][col + 4] == board[row][col]):
					return board[row][col]

			if (row <= size - 5 and col >= 4):
				if (board[row + 1][col - 1] == board[row][col] and
					board[row + 2][col - 2] == board[row][col] and
					board[row + 3][col - 3] == board[row][col] and
					board[row + 4][col - 4] == board[row][col]):
					return board[row][col]

			return 0	

		for i in range(self.size):
			for j in range(self.size):
				cell_result = check_cell(self.board, self.size, i, j)
				if cell_result != 0:
					return cell_result

		return 0


	def print_board(self):

		board = self.board

		for i in range(self.size):
			for j in range(self.size):
				if board[i][j] == 0:
					print('.', end='')
				elif board[i][j] == -1:
					print('x', end='')
				else:
					print('o', end='')
			print('\n', end='')

	def get_size(self):
		return self.size

	def cell_value(self, row, col):
		if (row >= self.size or col >= self.size or row < 0 or col < 0):
			return -10

		return self.board[row][col]

	def place(self, player_num, row, col):
		self.board[row][col] = player_num

	def erase(self, row, col):
		self.board[row][col] = 0

	def is_full(self):
		for i in range(self.size):
			for j in range(self.size):
				if self.board[i][j] == 0:
					return False

		return True

