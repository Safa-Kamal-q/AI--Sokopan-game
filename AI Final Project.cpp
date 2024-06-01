// Sokoban Game Implementation
// Students: Safa Qasrawi & Nouran Masalmah

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;
using states7x7 = array<array<int, 7>, 7>;

const int row = 7;
const int col = 7;
const int empty = 0;
const int wall = 1;
const int box = 2;
const int storage = 3;
const int boxStorage = 4;
const int player = 5;
const int playerInStorage = 6;

struct playerPosition {
	int row, col;
};


int playerRow, playerCol;
states7x7 initialState = { 0 };

void init(states7x7& sokoBoard, playerPosition& playerPos) {

	initialState = { {
		{1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 1, 1, 1},
		{1, 0, 2, 0, 1, 1, 1},
		{1, 1, 1, 0, 1, 1, 1},
		{1, 3, 2, 0, 1, 1, 1},
		{1, 0, 0, 3, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1},
	} };

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			sokoBoard[i][j] = initialState[i][j];
		}
	}
	if (sokoBoard[playerPos.row][playerPos.col] == storage)
		sokoBoard[playerRow][playerCol] = playerInStorage;
	else
		sokoBoard[playerRow][playerCol] = player;
	playerPos = { playerRow, playerCol };
}


bool isGoal(const states7x7 board) {

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (board[i][j] == box) {
				return false;
			}
		}
	}

	return true;
}


bool isDeadlock(const states7x7 board) {

	for (int i = 1; i < row - 1; ++i) {
		for (int j = 1; j < col - 1; ++j) {
			if (board[i][j] == box) {
				if (((board[i - 1][j] == wall) && (board[i][j - 1] == wall) ||
					((board[i - 1][j] == wall) && (board[i][j + 1] == wall)) ||
					((board[i + 1][j] == wall) && (board[i][j - 1] == wall) ||
						((board[i + 1][j] == wall) && (board[i][j + 1] == wall)))))
					return true;
			}
		}
	}

	return false;
}


void display(const states7x7 board) {

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}


enum Action { Up, Down, Left, Right };

vector<Action> generateChildren(const playerPosition playerPos, const states7x7 board) {

	vector<Action> actions;
	int x = playerPos.row;
	int y = playerPos.col;

	bool isMovingUpValid = x > 0 && (board[x - 1][y] != wall && (board[x - 1][y] != box || (x > 1 && (board[x - 2][y] != wall && board[x - 2][y] != box))));
	if (isMovingUpValid) actions.push_back(Up);

	bool isMovingDownValid = x < row - 1 && (board[x + 1][y] != wall && (board[x + 1][y] != box || (x < row - 2 && (board[x + 2][y] != wall && board[x + 2][y] != box))));
	if (isMovingDownValid) actions.push_back(Down);

	bool isMovingLeftValid = y > 0 && (board[x][y - 1] != wall && (board[x][y - 1] != box || (y > 1 && (board[x][y - 2] != wall && board[x][y - 2] != box))));
	if (isMovingLeftValid) actions.push_back(Left);

	bool isMovingRightValid = y < col - 1 && (board[x][y + 1] != wall && (board[x][y + 1] != box || (y < col - 2 && (board[x][y + 2] != wall && board[x][y + 2] != box))));
	if (isMovingRightValid) actions.push_back(Right);

	return actions;
}


void applyAction(playerPosition& playerPos, Action action, states7x7& board) {

	int x = playerPos.row;
	int y = playerPos.col;
	int nextX = x, nextY = y;


	switch (action) {
	case Up:
		nextX = x - 1;
		if (board[nextX][nextY] == box) {
			if (board[nextX - 1][nextY] == storage) {
				board[nextX - 1][nextY] = boxStorage;
				board[nextX][nextY] = player;

			}
			else {
				board[nextX - 1][nextY] = box;
				board[nextX][nextY] = player;

			}
		}
		else if (board[nextX][nextY] == storage) {
			board[nextX][nextY] = playerInStorage;
		}
		else {
			board[nextX][nextY] = player;
		}
		break;
	case Down:
		nextX = x + 1;
		if (board[nextX][nextY] == box) {
			if (board[nextX + 1][nextY] == storage) {
				board[nextX + 1][nextY] = boxStorage;
				board[nextX][nextY] = player;

			}
			else {
				board[nextX + 1][nextY] = box;
				board[nextX][nextY] = player;

			}
		}
		else if (board[nextX][nextY] == storage) {
			board[nextX][nextY] = playerInStorage;
		}
		else {
			board[nextX][nextY] = player;
		}
		break;
	case Left:
		nextY = y - 1;
		if (board[nextX][nextY] == box) {
			if (board[nextX][nextY - 1] == storage) {
				board[nextX][nextY - 1] = boxStorage;
				board[nextX][nextY] = player;

			}
			else {
				board[nextX][nextY - 1] = box;
				board[nextX][nextY] = player;

			}
		}
		else if (board[nextX][nextY] == storage) {
			board[nextX][nextY] = playerInStorage;
		}
		else {
			board[nextX][nextY] = player;
		}
		break;
	case Right:
		nextY = y + 1;
		if (board[nextX][nextY] == box) {
			if (board[nextX][nextY + 1] == storage) {
				board[nextX][nextY + 1] = boxStorage;
				board[nextX][nextY] = player;

			}
			else {
				board[nextX][nextY + 1] = box;
				board[nextX][nextY] = player;

			}
		}
		else if (board[nextX][nextY] == storage) {
			board[nextX][nextY] = playerInStorage;
		}
		else {
			board[nextX][nextY] = player;
		}
		break;
	}

	if (board[x][y] == playerInStorage)
	{
		board[x][y] = storage;
	}
	else board[x][y] = 0;

	playerPos.row = nextX;
	playerPos.col = nextY;
}



int findStateIndex(const vector<states7x7> stateVec, const states7x7 state) {
	auto it = find(stateVec.begin(), stateVec.end(), state);
	if (it != stateVec.end()) {
		return distance(stateVec.begin(), it);
	}
	else {
		return -1;
	}
}


vector<vector<double>> qTable;

int insertState(vector<states7x7>& stateVec, const states7x7 state) {

	int index = findStateIndex(stateVec, state);
	const int numActions = 4;
	if (index == -1) {
		stateVec.push_back(state);
		vector<double> newRow(numActions, 0);
		qTable.push_back(newRow);
		return stateVec.size() - 1;
	}
	else {
		return index;
	}
}


int rewardFunction(const states7x7 state) {
	int counBoxesInStorage = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			if (state[i][j] == 4)
				counBoxesInStorage++;

	}
	return (counBoxesInStorage + 1) * 100;
}


void qLearningAlgorithm(states7x7& sokobaBoard, playerPosition& playerPos, vector<states7x7>& stateVec) {

	for (int i = 0; i < 10000; ++i) {

		init(sokobaBoard, playerPos);
		int s = 0;

		while ((!isGoal(sokobaBoard) && s < 100 && !isDeadlock(sokobaBoard))) {

			vector<Action> possibleActions = generateChildren(playerPos, sokobaBoard);
			Action selectedAction = possibleActions[rand() % possibleActions.size()];

			states7x7 nextState = sokobaBoard;

			playerPosition nextPlayerPos = playerPos;
			applyAction(nextPlayerPos, selectedAction, nextState);

			int rewardValue = rewardFunction(nextState);
			int stateIndex = insertState(stateVec, sokobaBoard);
			int nextStateIndex = insertState(stateVec, nextState);

			int maximumQ = 0;
			for (int i = 0; i < 4; i++) {
				maximumQ = qTable[nextStateIndex][i] > maximumQ ? qTable[nextStateIndex][i] : maximumQ;
			}
			qTable[stateIndex][selectedAction] = rewardValue + 0.8 * maximumQ;

			sokobaBoard = nextState;
			playerPos = nextPlayerPos;
			s++;
		}
	}
}


Action selectBestAction(int stateIndex, vector<Action> possibleActions) {

	vector<states7x7> stateVec;
	int bestActionIndex = 0;
	int counter = 1;
	int firstValue = qTable[stateIndex][possibleActions[0]];

	for (int i = 0; i < possibleActions.size(); ++i) {
		if (i >= 1) {
			if (firstValue == qTable[stateIndex][possibleActions[i]])
				counter++;
		}
		if (qTable[stateIndex][possibleActions[i]] > qTable[stateIndex][bestActionIndex]) {

			bestActionIndex = possibleActions[i];
		}
	}
	cout << bestActionIndex << " before rand" << endl;
	cout << stateIndex << " State Index " << endl;

	cout << counter << " number of similler" << endl;
	if (bestActionIndex == 0) bestActionIndex = possibleActions[rand() % possibleActions.size()];
	if (counter == possibleActions.size()) bestActionIndex = possibleActions[rand() % possibleActions.size()];

	return static_cast<Action>(bestActionIndex);
}

string convertActionToString(Action action) {

	switch (action) {
	case Up: return "Up";
	case Down: return "Down";
	case Left: return "Left";
	case Right: return "Right";
	default: return "Unknown";
	}
}


void displaySolution(states7x7& sokobanBoard, playerPosition& playerPos, vector<states7x7> stateVec) {

	int stateIndex = 0;
	int numberOfState = 0;
	cout << "##Intial State##" << endl;
	display(sokobanBoard);
	while (!isGoal(sokobanBoard)) {
		if (isDeadlock(sokobanBoard)) {
			display(sokobanBoard);
			cout << "The state is deadlock" << endl;
			break;
		}
		vector<Action> possibleActions = generateChildren(playerPos, sokobanBoard);
		cout << "The possiple actions are: ";
		for (int i = 0; i < possibleActions.size(); i++) {
			cout << convertActionToString(possibleActions[i]);
			cout << "  ";
		}
		cout << endl;
		Action bestAction = selectBestAction(stateIndex, possibleActions);
		cout << "Selected Action is : " << convertActionToString(bestAction) << endl;

		applyAction(playerPos, bestAction, sokobanBoard);
		stateIndex = findStateIndex(stateVec, sokobanBoard);
		cout << "Sokoban board after applying the selected action :" << endl << endl;

		if (isGoal(sokobanBoard))
			cout << "##THE GOAL###" << endl;
		display(sokobanBoard);
		cout << "------------------------------------------" << endl;
		numberOfState++;
	}

	cout << endl << "The number of states is " << numberOfState << endl;
}


int main() {
	cout << "********************* AI Sokoban Game *********************" << endl;
	cout << "Based on the initial state, you can choose the player's position to be on any empty (0) space.\n";
	cout << "To start the AI solution, please enter the player's initial position.\n" << endl;

	states7x7 sokobaBoard = { 0 };
	playerPosition playerPos;

	playerPos = { playerRow, playerCol };
	init(sokobaBoard, playerPos);
	display(initialState);

	cout << "Enter player's initial row: ";
	cin >> playerRow;
	cout << "Enter player's initial column: ";
	cin >> playerCol;

	playerPos = { playerRow, playerCol };

	vector<states7x7> stateVec;

	qLearningAlgorithm(sokobaBoard, playerPos, stateVec);
	init(sokobaBoard, playerPos);
	displaySolution(sokobaBoard, playerPos, stateVec);

	return 0;
}
