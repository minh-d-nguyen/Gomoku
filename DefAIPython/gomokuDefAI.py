from __future__ import print_function
import gomokuBoard

class gomokuDefAI:
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

		max_score = 0
		max_row = -1
		max_col = -1

		if self.board.is_empty():
			mid = self.board.size/2
			self.board.place(self.player_num, mid, mid)
			return

		for i in range(self.board.size):
			for j in range(self.board.size):
				current_score = self.move_score(i, j)
				if current_score > max_score:
					max_score = current_score
					max_row = i
					max_col = j

		print("Max score: %d Row: %d Col: %d" % (max_score, max_row, max_col))
		self.board.place(self.player_num, max_row, max_col)

	def move_score(self, row, col):
		player_num = self.player_num
		if self.board.cell_value(row, col) != 0:
			return -1

		curr_score = 0

		curr_score += self.check_border(row, col)
		curr_score += self.check_defense(row, col)
		curr_score += self.check_offense(row, col)

		self.cell_score[row][col] = curr_score

		return curr_score

	def check_defense(self, row, col):

		player_num = self.player_num
		board = self.board
		size = board.size

		curr_score = 0
		def_one = 1
		def_one_bonus = 7
		def_two = 20
		def_two_bonus = 30
		def_three = 40
		def_three_bonus = 70
		def_four = 240
		def_mid = 25
		def_mid_bonus = 25
		def_four_mid = 60
		def_four_mid_bonus = 70

		opp_num = -1
		if player_num == -1:
			opp_num = 1

		if board.cell_value(row - 1, col) == opp_num:
			curr_score += def_one
			if board.cell_value(row - 2, col) == 0:
				curr_score += def_one_bonus

		if board.cell_value(row + 1, col) == opp_num:
			curr_score += def_one
			if board.cell_value(row + 2, col) == 0:
				curr_score += def_one_bonus

		if board.cell_value(row, col - 1) == opp_num:
			curr_score += def_one
			if board.cell_value(row, col - 2) == 0:
				curr_score += def_one_bonus

		if board.cell_value(row, col + 1) == opp_num:
			curr_score += def_one
			if board.cell_value(row, col + 2) == 0:
				curr_score += def_one_bonus

		if board.cell_value(row - 1, col - 1) == opp_num:
			curr_score += def_one
			if board.cell_value(row - 2, col - 2) == 0:
				curr_score += def_one_bonus

		if board.cell_value(row - 1, col + 1) == opp_num:
			curr_score += def_one
			if board.cell_value(row - 2, col + 2) == 0:
				curr_score += def_one_bonus

		if board.cell_value(row + 1, col - 1) == opp_num:
			curr_score += def_one
			if board.cell_value(row + 2, col + 2) == 0:
				curr_score += def_one_bonus

		if board.cell_value(row + 1, col + 1) == opp_num:
			curr_score += def_one
			if board.cell_value(row + 2, col + 2) == 0:
				curr_score += def_one_bonus


		# Defense two
		if (row > 1):
			if (board.cell_value(row - 1, col) == opp_num 
				and board.cell_value(row - 2, col) == opp_num):
				curr_score += def_two
				if (row > 2 and board.cell_value(row - 3, col) == 0): 
					curr_score += def_two_bonus

		if (row < size - 2):
			if (board.cell_value(row + 1, col) == opp_num and 
				board.cell_value(row + 2, col) == opp_num):
				curr_score += def_two
				if (row < size - 3 and board.cell_value(row + 3, col) == 0):
					curr_score += def_two_bonus

		if (col > 1):
			if (board.cell_value(row, col - 1) == opp_num and 
				board.cell_value(row, col - 2) == opp_num):
				curr_score += def_two
				if (col > 2 and board.cell_value(row, col - 3) == 0):
					curr_score += def_two_bonus

		if (col < size - 2):
			if (board.cell_value(row, col + 1) == opp_num and 
				board.cell_value(row, col + 2) == opp_num):
				curr_score += def_two
				if (col < size - 3 and board.cell_value(row, col + 3) == 0):
					curr_score += def_two_bonus

		if (row > 1 and col > 1):
			if (board.cell_value(row - 1, col - 1) == opp_num and 
				board.cell_value(row - 2, col - 2) == opp_num):
				curr_score += def_two
				if (row > 2 and col > 2 and board.cell_value(row - 3, col - 3) == 0):
					curr_score += def_two_bonus

		if (row > 1 and col < size - 2):
			if (board.cell_value(row - 1, col + 1) == opp_num and 
				board.cell_value(row - 2, col + 2) == opp_num):
				curr_score += def_two
				if (row > 2 and col < size - 3 and board.cell_value(row - 3, col + 3) == 0):
					curr_score += def_two_bonus

		if (row < size - 2 and col < size - 2):
			if (board.cell_value(row + 1, col + 1) == opp_num and 
				board.cell_value(row + 2, col + 2) == opp_num):
				curr_score += def_two
				if (row < size - 3 and col < size - 3 and board.cell_value(row + 3, col + 3) == 0):
					curr_score += def_two_bonus

		if (row < size - 2 and col > 1):
			if (board.cell_value(row + 1, col - 1) == opp_num and 
				board.cell_value(row + 2, col - 2) == opp_num):
				curr_score += def_two
				if (row < size - 3 and col > 2 and board.cell_value(row + 3, col - 3) == 0):
					curr_score += def_two_bonus

		# Defense three
		if (row > 2):
			if (board.cell_value(row - 1, col) == opp_num and 
				board.cell_value(row - 2, col) == opp_num and
				board.cell_value(row - 3, col) == opp_num):
				curr_score += def_three
				if (row > 3 and board.cell_value(row - 4, col) == 0):
					curr_score += def_three_bonus

		if (row < size - 3):
			if (board.cell_value(row + 1, col) == opp_num and 
				board.cell_value(row + 2, col) == opp_num and
				board.cell_value(row + 3, col) == opp_num):
				curr_score += def_three
				if (row < size - 4 and board.cell_value(row + 4, col) == 0):
					curr_score += def_three_bonus

		if (col > 2):
			if (board.cell_value(row, col - 1) == opp_num and 
				board.cell_value(row, col - 2) == opp_num and
				board.cell_value(row, col - 3) == opp_num):
				curr_score += def_three
				if (col > 3 and board.cell_value(row, col - 4) == 0):
					curr_score += def_three_bonus
		
		if (col < size - 3):
			if (board.cell_value(row, col + 1) == opp_num and 
				board.cell_value(row, col + 2) == opp_num and
				board.cell_value(row, col + 3) == opp_num):
				curr_score += def_three
				if (col < size - 4 and board.cell_value(row, col + 4) == 0):
					curr_score += def_three_bonus

		if (row > 2 and col > 2):
			if (board.cell_value(row - 1, col - 1) == opp_num and 
				board.cell_value(row - 2, col - 2) == opp_num and
				board.cell_value(row - 3, col - 3) == opp_num):
				curr_score += def_three
				if (row > 3 and col > 3 and board.cell_value(row - 4, col - 4) == 0):
					curr_score += def_three_bonus

		if (row > 2 and col < size - 3):
			if (board.cell_value(row - 1, col + 1) == opp_num and 
				board.cell_value(row - 2, col + 2) == opp_num and
				board.cell_value(row - 3, col + 3) == opp_num):
				curr_score += def_three
				if (row > 3 and col < size - 4 and board.cell_value(row - 4, col + 4) == 0):
					curr_score += def_three_bonus

		if (row < size - 3 and col > 2):
			if (board.cell_value(row + 1, col - 1) == opp_num and 
				board.cell_value(row + 2, col - 2) == opp_num and
				board.cell_value(row + 3, col - 3) == opp_num):
				curr_score += def_three
				if (row < size - 4 and col > 3 and board.cell_value(row + 4, col - 4) == 0):
					curr_score += def_three_bonus

		if (row < size - 3 and col < size - 3):
			if (board.cell_value(row + 1, col + 1) == opp_num and 
				board.cell_value(row + 2, col + 2) == opp_num and
				board.cell_value(row + 3, col + 3) == opp_num):
				curr_score += def_three
				if (row < size - 4 and col < size - 4 and board.cell_value(row + 4, col + 4) == 0):
					curr_score += def_three_bonus

		# Defense four
		if (row > 3):
			if (board.cell_value(row - 1, col) == opp_num and 
				board.cell_value(row - 2, col) == opp_num and
				board.cell_value(row - 3, col) == opp_num and
				board.cell_value(row - 4, col) == opp_num):
				curr_score += def_four
			
		if (row < size - 4):
			if (board.cell_value(row + 1, col) == opp_num and 
				board.cell_value(row + 2, col) == opp_num and
				board.cell_value(row + 3, col) == opp_num and
				board.cell_value(row + 4, col) == opp_num):
				curr_score += def_four

		if (col > 3):
			if (board.cell_value(row, col - 1) == opp_num and 
				board.cell_value(row, col - 2) == opp_num and
				board.cell_value(row, col - 3) == opp_num and
				board.cell_value(row, col - 4) == opp_num):
				curr_score += def_four

		if (col < size - 4):
			if (board.cell_value(row, col + 1) == opp_num and 
				board.cell_value(row, col + 2) == opp_num and
				board.cell_value(row, col + 3) == opp_num and
				board.cell_value(row, col + 4) == opp_num):
				curr_score += def_four

		if (row < size - 4 and col < size - 4):
			if (board.cell_value(row + 1, col + 1) == opp_num and 
				board.cell_value(row + 2, col + 2) == opp_num and
				board.cell_value(row + 3, col + 3) == opp_num and
				board.cell_value(row + 4, col + 4) == opp_num):
				curr_score += def_four

		if (row > 3 and col < size - 4):
			if (board.cell_value(row - 1, col + 1) == opp_num and 
				board.cell_value(row - 2, col + 2) == opp_num and
				board.cell_value(row - 3, col + 3) == opp_num and
				board.cell_value(row - 4, col + 4) == opp_num):
				curr_score += def_four

		if (row < size - 4 and col > 3):
			if (board.cell_value(row + 1, col - 1) == opp_num and 
				board.cell_value(row + 2, col - 2) == opp_num and
				board.cell_value(row + 3, col - 3) == opp_num and
				board.cell_value(row + 4, col - 4) == opp_num):
				curr_score += def_four

		if (row > 3 and col > 3):
			if (board.cell_value(row - 1, col - 1) == opp_num and 
				board.cell_value(row - 2, col - 2) == opp_num and
				board.cell_value(row - 3, col - 3) == opp_num and
				board.cell_value(row - 4, col - 4) == opp_num):
				curr_score += def_four

		# Defense Mid 3
		if (row < size - 1 and row > 0):
			if (board.cell_value(row - 1, col) == opp_num and 
				board.cell_value(row + 1, col) == opp_num):
				if (row > 1 and board.cell_value(row - 2, col) == 0):
					curr_score += def_mid
					if (row < size - 2 and board.cell_value(row + 2, col) == 0):
						curr_score += def_mid_bonus

		if (col < size - 1 and col > 0):
			if (board.cell_value(row, col - 1) == opp_num and 
				board.cell_value(row, col + 1) == opp_num):
				if (col > 1 and board.cell_value(row, col - 2) == 0):
					curr_score += def_mid
					if (col < size - 2 and board.cell_value(row, col + 2) == 0):
						curr_score += def_mid_bonus

		if (col < size - 1 and col > 0 and row < size - 1 and row > 0):
			if (board.cell_value(row - 1, col - 1) == opp_num and 
				board.cell_value(row + 1, col + 1) == opp_num):
				if (col > 1 and row > 1 and board.cell_value(row - 2, col - 2) == 0):
					curr_score += def_mid
					if (col < size - 2 and row < size - 2 and board.cell_value(row + 2, col + 2) == 0):
						curr_score += def_mid_bonus

			if (board.cell_value(row - 1, col + 1) == opp_num and 
				board.cell_value(row + 1, col - 1) == opp_num):
				if (col > 1 and row < size - 2 and board.cell_value(row + 2, col - 2) == 0):
					curr_score += def_mid
					if (col < size - 2 and row > 1 and board.cell_value(row - 2, col + 2) == 0):
						curr_score += def_mid_bonus

		# Defense Mid 4
		if (row > 0 and row < size - 2):
			if (board.cell_value(row - 1, col) == opp_num and 
				board.cell_value(row + 1, col) == opp_num and
				board.cell_value(row + 2, col) == opp_num):
				if (row > 1 and board.cell_value(row - 2, col) != player_num):
					curr_score += def_four_mid
					if (row < size - 3 and board.cell_value(row + 3, col) != player_num):
						curr_score += def_four_mid_bonus

				elif (row < size - 3 and board.cell_value(row + 3, col) != player_num):
					curr_score += def_four_mid
					if (row > 1 and board.cell_value(row - 2, col) != player_num):
						curr_score += def_four_mid_bonus

		if (row > 1 and row < size - 1):
			if (board.cell_value(row - 1, col) == opp_num and 
				board.cell_value(row + 1, col) == opp_num and
				board.cell_value(row - 2, col) == opp_num):
				if (row < size - 2 and board.cell_value(row + 2, col) != player_num):
					curr_score += def_four_mid
					if (row > 2 and board.cell_value(row - 3, col) != player_num):
						curr_score += def_four_mid_bonus

				elif (row > 2 and board.cell_value(row - 3, col) != player_num):
					curr_score += def_four_mid
					if (row < size - 2 and board.cell_value(row + 2, col) != player_num):
						curr_score += def_four_mid_bonus

		if (row > 0 and row < size - 2):
			if (board.cell_value(row - 1, col) == opp_num and 
				board.cell_value(row + 1, col) == opp_num and
				board.cell_value(row + 2, col) == opp_num):
				if (row > 1 and board.cell_value(row - 2, col) != player_num):
					curr_score += def_four_mid
					if (row < size - 3 and board.cell_value(row + 3, col) != player_num):
						curr_score += def_four_mid_bonus

				elif (row < size - 3 and board.cell_value(row + 3, col) != player_num):
					curr_score += def_four_mid
					if (row > 1 and board.cell_value(row - 2, col) != player_num):
						curr_score += def_four_mid_bonus

		if (col > 1 and col < size - 1):
			if (board.cell_value(row - 1, col - 1) == opp_num and 
				board.cell_value(row + 1, col + 1) == opp_num and
				board.cell_value(row - 2, col - 2) == opp_num):
				if (col < size - 2 and board.cell_value(row, col + 2) != player_num):
					curr_score += def_four_mid
					if (col > 2 and board.cell_value(row, col - 3) != player_num):
						curr_score += def_four_mid_bonus

				elif (col > 2 and board.cell_value(row, col - 3) != player_num):
					curr_score += def_four_mid
					if (col < size - 2 and board.cell_value(row, col + 2) != player_num):
						curr_score += def_four_mid_bonus

		if (col > 0 and col < size - 2):
			if (board.cell_value(row, col - 1) == opp_num and 
				board.cell_value(row, col + 1) == opp_num and
				board.cell_value(row, col + 2) == opp_num):
				if (col > 1 and board.cell_value(row, col - 2) != player_num):
					curr_score += def_four_mid
					if (col < size - 3 and board.cell_value(row, col + 3) != player_num):
						curr_score += def_four_mid_bonus

				elif (col < size - 3 and board.cell_value(row, col + 3) != player_num):
					curr_score += def_four_mid
					if (col > 1 and board.cell_value(row, col - 2) != player_num):
						curr_score += def_four_mid_bonus

		if (col > 0 and row > 0 and col < size - 2 and row < size - 2):
			if (board.cell_value(row - 1, col - 1) == opp_num and 
				board.cell_value(row + 1, col + 1) == opp_num and
				board.cell_value(row + 2, col + 2) == opp_num):
				if (col > 1 and row > 1 and board.cell_value(row - 2, col - 2) != player_num):
					curr_score += def_four_mid
					if (col < size - 3 and row < size - 3 and 
						board.cell_value(row + 3, col + 3) != player_num):
						curr_score += def_four_mid_bonus

				elif (col < size - 3 and row < size - 3 and 
						 board.cell_value(row + 3, col + 3) != player_num):
					curr_score += def_four_mid
					if (col > 1 and row > 1 and board.cell_value(row - 2, col - 2) != player_num):
						curr_score += def_four_mid_bonus

		if (col > 1 and row > 1 and col < size - 1 and row < size - 1):
			if (board.cell_value(row - 1, col - 1) == opp_num and 
				board.cell_value(row + 1, col + 1) == opp_num and
				board.cell_value(row - 2, col - 2) == opp_num):
				if (col > 2 and row > 2 and board.cell_value(row - 3, col - 3) != player_num):
					curr_score += def_four_mid
					if (col < size - 2 and row < size - 2 and 
						board.cell_value(row + 2, col + 2) != player_num):
						curr_score += def_four_mid_bonus

				elif (col < size - 2 and row < size - 2 and 
						 board.cell_value(row + 2, col + 2) != player_num):
					curr_score += def_four_mid
					if (col > 2 and row > 2 and board.cell_value(row - 3, col - 3) != player_num):
						curr_score += def_four_mid_bonus

		if (col > 1 and row > 0 and col < size - 1 and row < size - 2):
			if (board.cell_value(row - 1, col + 1) == opp_num and 
				board.cell_value(row + 1, col - 1) == opp_num and
				board.cell_value(row + 2, col - 2) == opp_num):
				if (col > 2 and row < size - 3 and 
					board.cell_value(row + 3, col - 3) != player_num):
					curr_score += def_four_mid
					if (col < size - 2 and row > 1 and 
						board.cell_value(row - 2, col + 2) != player_num):
						curr_score += def_four_mid_bonus

				elif (col < size - 2 and row > 1 and 
						 board.cell_value(row - 2, col + 2) != player_num):
					curr_score += def_four_mid
					if (col > 2 and row < size - 3 and 
						board.cell_value(row + 3, col - 3) != player_num):
						curr_score += def_four_mid_bonus

		if (row > 1 and col > 0 and row < size - 1 and col < size - 2):
			if (board.cell_value(row + 1, col - 1) == opp_num and 
				board.cell_value(row - 1, col + 1) == opp_num and
				board.cell_value(row - 2, col + 2) == opp_num):
				if (row > 2 and col < size - 3 and 
					board.cell_value(row - 3, col + 3) != player_num):
					curr_score += def_four_mid
					if (row < size - 2 and col > 1 and 
						board.cell_value(row + 2, col - 2) != player_num):
						curr_score += def_four_mid_bonus

				elif (row < size - 2 and col > 1 and 
						 board.cell_value(row + 2, col - 2) != player_num):
					curr_score += def_four_mid
					if (row > 2 and col < size - 3 and 
						board.cell_value(row - 3, col + 3) != player_num):
						curr_score += def_four_mid_bonus

		return curr_score

	def check_offense(self, row, col):

		player_num = self.player_num
		board = self.board
		size = board.size

		curr_score = 0
		off_one = 4
		off_one_bonus = 5
		off_two = 16
		off_two_bonus = 26
		off_three = 46
		off_three_bonus = 90
		off_four = 300
		off_mid = 5
		off_mid_bonus = 25
		off_four_mid = 60
		off_four_mid_bonus = 90

		opp_num = -1
		if player_num == -1:
			opp_num = 1

		if board.cell_value(row - 1, col) == player_num:
			curr_score += off_one
			if board.cell_value(row - 2, col) == 0:
				curr_score += off_one_bonus

		if board.cell_value(row + 1, col) == player_num:
			curr_score += off_one
			if board.cell_value(row + 2, col) == 0:
				curr_score += off_one_bonus

		if board.cell_value(row, col - 1) == player_num:
			curr_score += off_one
			if board.cell_value(row, col - 2) == 0:
				curr_score += off_one_bonus

		if board.cell_value(row, col + 1) == player_num:
			curr_score += off_one
			if board.cell_value(row, col + 2) == 0:
				curr_score += off_one_bonus

		if board.cell_value(row - 1, col - 1) == player_num:
			curr_score += off_one
			if board.cell_value(row - 2, col - 2) == 0:
				curr_score += off_one_bonus

		if board.cell_value(row - 1, col + 1) == player_num:
			curr_score += off_one
			if board.cell_value(row - 2, col + 2) == 0:
				curr_score += off_one_bonus

		if board.cell_value(row + 1, col - 1) == player_num:
			curr_score += off_one
			if board.cell_value(row + 2, col + 2) == 0:
				curr_score += off_one_bonus

		if board.cell_value(row + 1, col + 1) == player_num:
			curr_score += off_one
			if board.cell_value(row + 2, col + 2) == 0:
				curr_score += off_one_bonus

		# Offense two
		if (row > 1):
			if (board.cell_value(row - 1, col) == player_num 
				and board.cell_value(row - 2, col) == player_num):
				curr_score += off_two
				if (row > 2 and board.cell_value(row - 3, col) == 0): 
					curr_score += off_two_bonus

		if (row < size - 2):
			if (board.cell_value(row + 1, col) == player_num and 
				board.cell_value(row + 2, col) == player_num):
				curr_score += off_two
				if (row < size - 3 and board.cell_value(row + 3, col) == 0):
					curr_score += off_two_bonus

		if (col > 1):
			if (board.cell_value(row, col - 1) == player_num and 
				board.cell_value(row, col - 2) == player_num):
				curr_score += off_two
				if (col > 2 and board.cell_value(row, col - 3) == 0):
					curr_score += off_two_bonus

		if (col < size - 2):
			if (board.cell_value(row, col + 1) == player_num and 
				board.cell_value(row, col + 2) == player_num):
				curr_score += off_two
				if (col < size - 3 and board.cell_value(row, col + 3) == 0):
					curr_score += off_two_bonus

		if (row > 1 and col > 1):
			if (board.cell_value(row - 1, col - 1) == player_num and 
				board.cell_value(row - 2, col - 2) == player_num):
				curr_score += off_two
				if (row > 2 and col > 2 and board.cell_value(row - 3, col - 3) == 0):
					curr_score += off_two_bonus

		if (row > 1 and col < size - 2):
			if (board.cell_value(row - 1, col + 1) == player_num and 
				board.cell_value(row - 2, col + 2) == player_num):
				curr_score += off_two
				if (row > 2 and col < size - 3 and board.cell_value(row - 3, col + 3) == 0):
					curr_score += off_two_bonus

		if (row < size - 2 and col < size - 2):
			if (board.cell_value(row + 1, col + 1) == player_num and 
				board.cell_value(row + 2, col + 2) == player_num):
				curr_score += off_two
				if (row < size - 3 and col < size - 3 and board.cell_value(row + 3, col + 3) == 0):
					curr_score += off_two_bonus

		if (row < size - 2 and col > 1):
			if (board.cell_value(row + 1, col - 1) == player_num and 
				board.cell_value(row + 2, col - 2) == player_num):
				curr_score += off_two
				if (row < size - 3 and col > 2 and board.cell_value(row + 3, col - 3) == 0):
					curr_score += off_two_bonus

		# offense three
		if (row > 2):
			if (board.cell_value(row - 1, col) == player_num and 
				board.cell_value(row - 2, col) == player_num and
				board.cell_value(row - 3, col) == player_num and
				(board.cell_value(row - 4, col) == 0 or
				 board.cell_value(row + 1, col) == 0)
				):
				curr_score += off_three
				if (board.cell_value(row - 4, col) == 0 and
					board.cell_value(row + 1, col) == 0):
					curr_score += off_three_bonus

		if (row < size - 3):
			if (board.cell_value(row + 1, col) == player_num and 
				board.cell_value(row + 2, col) == player_num and
				board.cell_value(row + 3, col) == player_num and
				(board.cell_value(row + 4, col) == 0 or	
				 board.cell_value(row - 1, col) == 0)):
				curr_score += off_three
				if (board.cell_value(row + 4, col) == 0 and
					board.cell_value(row - 1, col) == 0):
					curr_score += off_three_bonus

		if (col > 2):
			if (board.cell_value(row, col - 1) == player_num and 
				board.cell_value(row, col - 2) == player_num and
				board.cell_value(row, col - 3) == player_num and
				(board.cell_value(row, col - 4) == 0 or
				 board.cell_value(row, col + 1) == 0)):
				curr_score += off_three
				if (board.cell_value(row, col - 4) == 0 and
					board.cell_value(row, col + 1) == 0):
					curr_score += off_three_bonus

		if (col < size - 3):
			if (board.cell_value(row, col + 1) == player_num and 
				board.cell_value(row, col + 2) == player_num and
				board.cell_value(row, col + 3) == player_num and
				(board.cell_value(row, col + 4) == 0 or
				 board.cell_value(row, col - 1) == 0)):
				curr_score += off_three
				if (board.cell_value(row, col + 4) == 0 and
					board.cell_value(row, col - 1) == 0):
					curr_score += off_three_bonus

		if (row > 2 and col > 2):
			if (board.cell_value(row - 1, col - 1) == player_num and 
				board.cell_value(row - 2, col - 2) == player_num and
				board.cell_value(row - 3, col - 3) == player_num and
				(board.cell_value(row - 4, col - 4) == 0 or
				 board.cell_value(row + 1, col + 1) == 0)):
				curr_score += off_three
				if (board.cell_value(row - 4, col - 4) == 0 and
					board.cell_value(row + 1, col + 1) == 0):
					curr_score += off_three_bonus

		if (row > 2 and col < size - 3):
			if (board.cell_value(row - 1, col + 1) == player_num and 
				board.cell_value(row - 2, col + 2) == player_num and
				board.cell_value(row - 3, col + 3) == player_num and
				(board.cell_value(row - 4, col + 4) == 0 or
				 board.cell_value(row + 1, col - 1) == 0)):
				curr_score += off_three
				if (board.cell_value(row - 4, col + 4) == 0 and
					board.cell_value(row + 1, col - 1) == 0):
					curr_score += off_three_bonus

		if (row < size - 3 and col > 2):
			if (board.cell_value(row + 1, col - 1) == player_num and 
				board.cell_value(row + 2, col - 2) == player_num and
				board.cell_value(row + 3, col - 3) == player_num and
				(board.cell_value(row + 4, col - 4) == 0 or
				 board.cell_value(row - 1, col + 1) == 0)):
				curr_score += off_three
				if (board.cell_value(row + 4, col - 4) == 0 and
					board.cell_value(row - 1, col + 1) == 0):
					curr_score += off_three_bonus

		if (row < size - 3 and col < size - 3):
			if (board.cell_value(row + 1, col + 1) == player_num and 
				board.cell_value(row + 2, col + 2) == player_num and
				board.cell_value(row + 3, col + 3) == player_num and
				(board.cell_value(row + 4, col + 4) == 0 or
				 board.cell_value(row - 1, col - 1) == 0)):
				curr_score += off_three
				if (board.cell_value(row + 4, col + 4) == 0 and
					board.cell_value(row - 1, col - 1) == 0):
					curr_score += off_three_bonus

		# offense four
		if (row > 3):
			if (board.cell_value(row - 1, col) == player_num and 
				board.cell_value(row - 2, col) == player_num and
				board.cell_value(row - 3, col) == player_num and
				board.cell_value(row - 4, col) == player_num):
				curr_score += off_four

		if (row < size - 4):
			if (board.cell_value(row + 1, col) == player_num and 
				board.cell_value(row + 2, col) == player_num and
				board.cell_value(row + 3, col) == player_num and
				board.cell_value(row + 4, col) == player_num):
				curr_score += off_four

		if (col > 3):
			if (board.cell_value(row, col - 1) == player_num and 
				board.cell_value(row, col - 2) == player_num and
				board.cell_value(row, col - 3) == player_num and
				board.cell_value(row, col - 4) == player_num):
				curr_score += off_four

		if (col < size - 4):
			if (board.cell_value(row, col + 1) == player_num and 
				board.cell_value(row, col + 2) == player_num and
				board.cell_value(row, col + 3) == player_num and
				board.cell_value(row, col + 4) == player_num):
				curr_score += off_four

		if (row < size - 4 and col < size - 4):
			if (board.cell_value(row + 1, col + 1) == player_num and 
				board.cell_value(row + 2, col + 2) == player_num and
				board.cell_value(row + 3, col + 3) == player_num and
				board.cell_value(row + 4, col + 4) == player_num):
				curr_score += off_four

		if (row > 3 and col < size - 4):
			if (board.cell_value(row - 1, col + 1) == player_num and 
				board.cell_value(row - 2, col + 2) == player_num and
				board.cell_value(row - 3, col + 3) == player_num and
				board.cell_value(row - 4, col + 4) == player_num):
				curr_score += off_four

		if (row < size - 4 and col > 3):
			if (board.cell_value(row + 1, col - 1) == player_num and 
				board.cell_value(row + 2, col - 2) == player_num and
				board.cell_value(row + 3, col - 3) == player_num and
				board.cell_value(row + 4, col - 4) == player_num):
				curr_score += off_four

		if (row > 3 and col > 3):
			if (board.cell_value(row - 1, col - 1) == player_num and 
				board.cell_value(row - 2, col - 2) == player_num and
				board.cell_value(row - 3, col - 3) == player_num and
				board.cell_value(row - 4, col - 4) == player_num):
				curr_score += off_four

		# Offense Mid 3
		if (row < size - 1 and row > 0):
			if (board.cell_value(row - 1, col) == player_num and 
				board.cell_value(row + 1, col) == player_num):
				if (row > 1 and board.cell_value(row - 2, col) == 0):
					curr_score += off_mid
					if (row < size - 2 and board.cell_value(row + 2, col) == 0):
						curr_score += off_mid_bonus

		if (col < size - 1 and col > 0):
			if (board.cell_value(row, col - 1) == player_num and 
				board.cell_value(row, col + 1) == player_num):
				if (col > 1 and board.cell_value(row, col - 2) == 0):
					curr_score += off_mid
					if (col < size - 2 and board.cell_value(row, col + 2) == 0):
						curr_score += off_mid_bonus

		if (col < size - 1 and col > 0 and row < size - 1 and row > 0):
			if (board.cell_value(row - 1, col - 1) == player_num and 
				board.cell_value(row + 1, col + 1) == player_num):
				if (col > 1 and row > 1 and board.cell_value(row - 2, col - 2) == 0):
					curr_score += off_mid
					if (col < size - 2 and row < size - 2 and board.cell_value(row + 2, col + 2) == 0):
						curr_score += off_mid_bonus

			if (board.cell_value(row - 1, col + 1) == player_num and 
				board.cell_value(row + 1, col - 1) == player_num):
				if (col > 1 and row < size - 2 and board.cell_value(row + 2, col - 2) == 0):
					curr_score += off_mid
					if (col < size - 2 and row > 1 and board.cell_value(row - 2, col + 2) == 0):
						curr_score += off_mid_bonus

		# Offense Mid 4
		if (row > 0 and row < size - 2):
			if (board.cell_value(row - 1, col) == player_num and 
				board.cell_value(row + 1, col) == player_num and
				board.cell_value(row + 2, col) == player_num):
				if (row > 1 and board.cell_value(row - 2, col) != opp_num):
					curr_score += off_four_mid
					if (row < size - 3 and board.cell_value(row + 3, col) != opp_num):
						curr_score += off_four_mid_bonus

				elif (row < size - 3 and board.cell_value(row + 3, col) != opp_num):
					curr_score += off_four_mid
					if (row > 1 and board.cell_value(row - 2, col) != opp_num):
						curr_score += off_four_mid_bonus

		if (row > 1 and row < size - 1):
			if (board.cell_value(row - 1, col) == player_num and 
				board.cell_value(row + 1, col) == player_num and
				board.cell_value(row - 2, col) == player_num):
				if (row < size - 2 and board.cell_value(row + 2, col) != opp_num):
					curr_score += off_four_mid
					if (row > 2 and board.cell_value(row - 3, col) != opp_num):
						curr_score += off_four_mid_bonus

				elif (row > 2 and board.cell_value(row - 3, col) != opp_num):
					curr_score += off_four_mid
					if (row < size - 2 and board.cell_value(row + 2, col) != opp_num):
						curr_score += off_four_mid_bonus

		if (row > 0 and row < size - 2):
			if (board.cell_value(row - 1, col) == player_num and 
				board.cell_value(row + 1, col) == player_num and
				board.cell_value(row + 2, col) == player_num):
				if (row > 1 and board.cell_value(row - 2, col) != opp_num):
					curr_score += off_four_mid
					if (row < size - 3 and board.cell_value(row + 3, col) != opp_num):
						curr_score += off_four_mid_bonus

				elif (row < size - 3 and board.cell_value(row + 3, col) != opp_num):
					curr_score += off_four_mid
					if (row > 1 and board.cell_value(row - 2, col) != opp_num):
						curr_score += off_four_mid_bonus

		if (col > 1 and col < size - 1):
			if (board.cell_value(row, col - 1) == player_num and 
				board.cell_value(row + 1, col + 1) == player_num and
				board.cell_value(row - 2, col - 2) == player_num):
				if (col < size - 2 and board.cell_value(row, col + 2) != opp_num):
					curr_score += off_four_mid
					if (col > 2 and board.cell_value(row, col - 3) != opp_num):
						curr_score += off_four_mid_bonus

				elif (col > 2 and board.cell_value(row, col - 3) != opp_num):
					curr_score += off_four_mid
					if (col < size - 2 and board.cell_value(row, col + 2) != opp_num):
						curr_score += off_four_mid_bonus

		if (col > 0 and col < size - 2):
			if (board.cell_value(row, col - 1) == player_num and 
				board.cell_value(row, col + 1) == player_num and
				board.cell_value(row, col + 2) == player_num):
				if (col > 1 and board.cell_value(row, col - 2) != opp_num):
					curr_score += off_four_mid
					if (col < size - 3 and board.cell_value(row, col + 3) != opp_num):
						curr_score += off_four_mid_bonus

				elif (col < size - 3 and board.cell_value(row, col + 3) != opp_num):
					curr_score += off_four_mid
					if (col > 1 and board.cell_value(row, col - 2) != opp_num):
						curr_score += off_four_mid_bonus

		if (col > 0 and row > 0 and col < size - 2 and row < size - 2):
			if (board.cell_value(row - 1, col - 1) == player_num and 
				board.cell_value(row + 1, col + 1) == player_num and
				board.cell_value(row + 2, col + 2) == player_num):
				if (col > 1 and row > 1 and board.cell_value(row - 2, col - 2) != opp_num):
					curr_score += off_four_mid
					if (col < size - 3 and row < size - 3 and 
						board.cell_value(row + 3, col + 3) != opp_num):
						curr_score += off_four_mid_bonus

				elif (col < size - 3 and row < size - 3 and 
						 board.cell_value(row + 3, col + 3) != opp_num):
					curr_score += off_four_mid
					if (col > 1 and row > 1 and board.cell_value(row - 2, col - 2) != opp_num):
						curr_score += off_four_mid_bonus

		if (col > 1 and row > 1 and col < size - 1 and row < size - 1):
			if (board.cell_value(row - 1, col - 1) == player_num and 
				board.cell_value(row + 1, col + 1) == player_num and
				board.cell_value(row - 2, col - 2) == player_num):
				if (col > 2 and row > 2 and board.cell_value(row - 3, col - 3) != opp_num):
					curr_score += off_four_mid
					if (col < size - 2 and row < size - 2 and 
						board.cell_value(row + 2, col + 2) != opp_num):
						curr_score += off_four_mid_bonus

				elif (col < size - 2 and row < size - 2 and 
						 board.cell_value(row + 2, col + 2) != opp_num):
					curr_score += off_four_mid
					if (col > 2 and row > 2 and board.cell_value(row - 3, col - 3) != opp_num):
						curr_score += off_four_mid_bonus

		if (col > 1 and row > 0 and col < size - 1 and row < size - 2):
			if (board.cell_value(row - 1, col + 1) == player_num and 
				board.cell_value(row + 1, col - 1) == player_num and
				board.cell_value(row + 2, col - 2) == player_num):
				if (col > 2 and row < size - 3 and 
					board.cell_value(row + 3, col - 3) != opp_num):
					curr_score += off_four_mid
					if (col < size - 2 and row > 1 and 
						board.cell_value(row - 2, col + 2) != opp_num):
						curr_score += off_four_mid_bonus

				elif (col < size - 2 and row > 1 and 
						 board.cell_value(row - 2, col + 2) != opp_num):
					curr_score += off_four_mid
					if (col > 2 and row < size - 3 and 
						board.cell_value(row + 3, col - 3) != opp_num):
						curr_score += off_four_mid_bonus

		if (row > 1 and col > 0 and row < size - 1 and col < size - 2):
			if (board.cell_value(row + 1, col - 1) == player_num and 
				board.cell_value(row - 1, col + 1) == player_num and
				board.cell_value(row - 2, col + 2) == player_num):
				if (row > 2 and col < size - 3 and 
					board.cell_value(row - 3, col + 3) != opp_num):
					curr_score += off_four_mid
					if (row < size - 2 and col > 1 and 
						board.cell_value(row + 2, col - 2) != opp_num):
						curr_score += off_four_mid_bonus

				elif (row < size - 2 and col > 1 and 
						 board.cell_value(row + 2, col - 2) != opp_num):
					curr_score += off_four_mid
					if (row > 2 and col < size - 3 and 
						board.cell_value(row - 3, col + 3) != opp_num):
						curr_score += off_four_mid_bonus

		return curr_score

	def check_border(self, row, col):
		curr_score = 0
		size = self.board.size
		board = self.board
		if (row > 0):
			if (board.cell_value(row - 1, col) != 0):
				curr_score += 1;		

		if (col > 0):
			if (board.cell_value(row, col - 1) != 0):
				curr_score += 1;

		if (col < size - 1):
			if (board.cell_value(row, col + 1) != 0):
				curr_score += 1;

		if (row < size - 1):
			if (board.cell_value(row + 1, col) != 0):
				curr_score += 1;

		if (row > 0 and col > 0):
			if (board.cell_value(row - 1, col - 1) != 0):
				curr_score += 2;	

		if (row > 0 and col < size - 1):
			if (board.cell_value(row - 1, col + 1) != 0):
				curr_score += 2;

		if (row < size - 1 and col > 0):
			if (board.cell_value(row + 1, col - 1) != 0):
				curr_score += 2;

		if (row < size - 1 and col < size - 1):
			if (board.cell_value(row + 1, col + 1) != 0):
				curr_score += 2;

		return curr_score;

	def print_score(self):
		for i in range(self.board.size):
			for j in range(self.board.size):
				print(self.cell_score[i][j], end='')
			print('\n')

	
