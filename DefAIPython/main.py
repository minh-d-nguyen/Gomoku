import sys
from gomokuBoard import GomokuBoard
from gomokuDefAI import gomokuDefAI
from PyQt5 import QtGui, QtCore
from PyQt5.QtWidgets import (
	QApplication,
	QMainWindow,
	QMessageBox,
	QAction,
	QPushButton,
	QInputDialog
)

class GomokuUI(QMainWindow):

    def __init__(self):
        super(GomokuUI,self).__init__()
        self.setWindowTitle('Gomoku')
        self.btns = []
        self.board_dim = 25
        self.setGeometry(50,50,20*self.board_dim,20*self.board_dim)
        self.board = GomokuBoard(self.board_dim)
        self.AI = None
        self.player_num = 0

        self.winner = ''
        self.new_game()
        self.board_init()

    def board_init(self):

        new_action = QAction('&New game', self)
        new_action.setShortcut('Ctrl+N')
        new_action.setStatusTip('Make a new game')
        new_action.triggered.connect(self.new_game)

        exit_action = QAction('&Leave', self)
        exit_action.setShortcut('Ctrl+Q')
        exit_action.setStatusTip('Leave the app')
        exit_action.triggered.connect(self.close_application)

        self.statusBar()

        mainMenu = self.menuBar()
        fileMenu = mainMenu.addMenu('&File')

        fileMenu.addAction(new_action)

        fileMenu.addAction(exit_action)

        for i in range(self.board_dim):
        	self.btns.append([])
        	for j in range(self.board_dim):
        		new_btn = QPushButton('', self)
        		new_btn.resize(25,25)
        		new_btn.move(20*i,20*j)
        		self.btns[i].append(new_btn)
        		self.btns[i][j].clicked.connect(self.clicked)

       	self.show()

    def clicked(self):
    	button = self.sender()
    	r = -1
    	c = -1
    	for i in range(self.board_dim):
    		for j in range(self.board_dim):
    			if self.btns[i][j] == button:
    				r = i
    				c = j

    	if self.board.cell_value(r, c) == 0:
            self.board.place(self.player_num, r, c)
            self.btns[r][c].setText(self.playerChar)
            self.btns[r][c].setFont(QtGui.QFont('Times', 20))

            self.show()
            self.test_winner()
            self.AI_move()

    def new_game(self):
        item, ok = QInputDialog.getItem(self, "Choose X or O", 
                                              "Would you like to play as X or O?", ('X','O'), 0, False)
        if ok and item:
            self.playerChar = item

            if self.playerChar == 'X':
               	self.player_num = -1
               	self.AI_num = 1
                self.AIChar = 'O'
            else:
	        	self.player_num = 1
	        	self.AI_num = -1
	        	self.AIChar = 'X'

        self.AI = gomokuDefAI(self.AI_num, self.board)

    def AI_move(self):
        r, c = self.AI.make_move()
        self.btns[r][c].setText(self.AIChar)
    	self.btns[r][c].setFont(QtGui.QFont('Times', 20))
        self.show()
        self.test_winner()

    def test_winner(self):
    	self.winner = self.board.check_win()
    	winner = None
    	if self.winner == 1:
    		winner = 'O'
    	elif self.winner == -1:
    		winner = 'X'

        # if there is a winner, report it and end the game        
        if self.winner == 1 or self.winner == -1:
            msg = '{} won the game!  Would you like to play again?'.format(winner)
            choice = QMessageBox.question(self,'Game Over!', msg,
                                            QMessageBox.Yes | QMessageBox.No)

            if choice == QMessageBox.Yes:
                self.close()
                self.__init__()
            else:
                sys.exit()

        # if there's a draw, handle it here
        if self.board.is_full():
            msg = 'It was a draw!  Would you like to play again?'
            choice = QMessageBox.question(self,'Game Over!', msg,
                                            QtGui.QMessageBox.Yes | QtGui.QMessageBox.No)

            if choice == QMessageBox.Yes:
                self.close()
                self.__init__()
            else:
                sys.exit()

    def close_application(self):
        choice = QtGui.QMessageBox.question(self,'Exit','Are you sure you want to exit?',
                                            QtGui.QMessageBox.Yes | QtGui.QMessageBox.No)

        if choice == QtGui.QMessageBox.Yes:
            sys.exit()

def main(): 
    app = QApplication(sys.argv)
    GUI = GomokuUI()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()