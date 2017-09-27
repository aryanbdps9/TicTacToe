#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>
// X is maximalist, O is minimalist

using namespace std;

char opponent = 'X', player = 'O';

struct pos{
	int row, col;
	pos(){
		row = 0;
		col = 0;
	}
	pos(int a, int b){
		row = a;
		col = b;
	}
	bool operator==(pos rt){
		if((rt.row == row) && (rt.col == col)) return true;
		return false;
	}
	void print(){
		cout << "(" << row << ",\t" << col << ")\n";
	}
	void print2(){
		cout << "(" << row << ",\t" << col << ")\t\t";
	}
};


void print_brd(char brd[3][3]){
	cout << "\n\n";
	for (int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; j++){
			cout << brd[i][j] << "\t";
		}
		cout << "\n";
	}
	cout << "\n\n";
	return;
}


bool isMoveLeft(char brd[3][3]){
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(brd[i][j] == '_') return true;
		}
	}
	return false;
}

int evaluate(char brd[3][3]){
	// Checking for row
	for (int i = 0; i < 3; ++i)
	{
		if((brd[i][0] == brd[i][1]) && brd[i][1] == brd[i][2]){
			if (brd[i][0] == opponent)
			{
				return 10;
			}
			else if (brd[i][0] == player)
			{
				return -10;
			}
		}
	}
	//checking for column
	for (int i = 0; i < 3; ++i)
	{
		if((brd[0][i] == brd[1][i]) && brd[1][i] == brd[2][i]){
			if (brd[0][i] == opponent)
			{
				return 10;
			}
			else if (brd[0][i] == player)
			{
				return -10;
			}
		}
	}
	//checking for diagonals
	if((brd[0][0] == brd [1][1]) && (brd[1][1] == brd[2][2])){
		if(brd[1][1] == opponent) return 10;
		else if (brd[1][1] == player) return -10;
	}

	if((brd[0][2] == brd [1][1]) && (brd[1][1] == brd[2][0])){
		if(brd[1][1] == opponent) return 10;
		else if (brd[1][1] == player) return -10;
	}
	return 0;
}

bool compar(bool isMax, int lhs, int rhs){
	if (isMax)
		{return (lhs >= rhs);}
	else
		{return (lhs <= rhs);}
}

int minimax(char brd[3][3], bool isMax, int &depth){
	int score = evaluate(brd);
	if(score != 0) return score;
	else if(!isMoveLeft(brd)){
		return 0;
	}
	depth++;
	int org_depth = depth;
	if (!isMoveLeft(brd)){
		return evaluate(brd);
	}
	int best = -20;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			
			if(brd[i][j] == '_'){
				if(isMax){
					brd[i][j] = opponent;
				}
				else{
					brd[i][j] = player;
				}
				int cur_depth = depth;
				int cur = minimax(brd, (!(isMax)), cur_depth);
				if(best == -20) {
					best = cur;
					org_depth += cur_depth;
				}
				if(compar(isMax, cur, best)){
					if(best == cur){
						if ((isMax && best >= 0) || ((!(isMax)) && best <= 0)){
							if(org_depth > cur_depth){
								org_depth = cur_depth;
							}
						}
						if ((isMax && best < 0) || ((!(isMax)) && best > 0)){
							if(org_depth < cur_depth){
								org_depth = cur_depth;
							}
						}
					}
					best = cur;
				}
				brd[i][j] = '_';
			}

		}
	}
	depth = org_depth;
	return best;
}

pos optimal_move(char brd[3][3], bool isMax){
	std::vector<pos> res(1);
	int win = -2;
	int depth = 0;
	if(!isMoveLeft(brd)){
		return res[1];
	}
	for (int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j){
			if(brd[i][j] == '_'){
				pos dummy = pos(i, j);
				int cur_depth = 0;
				if (isMax) brd[i][j] = opponent;
				else brd[i][j] = player;
				
				int state = 2.0* (isMax - 0.5) * minimax(brd, !(isMax), cur_depth) / 10;
				if(state > win){
					//std::vector<pos> ().swap(res);
					res.clear();

					res.push_back(dummy);
					depth = cur_depth;
					win = state;
				}
				else if(state == win){
					if((state >= 0)){
						if((depth > cur_depth)){
							//std::vector<pos> ().swap(res);
							res.clear();
							res.push_back(dummy);
							depth = cur_depth;
						}
						else if(depth == cur_depth){
							res.push_back(dummy);
						}
					}
					else if((state < 0)){
						if((depth < cur_depth)){
							//std::vector<pos> ().swap(res);
							res.clear();
							res.push_back(dummy);
							depth = cur_depth;
						}
						else if(depth == cur_depth){
							res.push_back(dummy);
						}
					}
				}
				brd[i][j] = '_';
			}
		}
	}


	srand(time(NULL));
	pos fres = res[rand() % (res.size())];
	/*fres.print();
	for (std::vector<pos>::iterator i = res.begin(); i != res.end(); ++i)
	{
		i->print2();
	}*/
	cout << endl;
	return fres;

}



int main(int argc, char const *argv[])
{
	char brd[3][3] = {
		{'_', '_', '_'},
		{'_', '_', '_'},
		{'_', '_', '_'}
	};
	int inp_row, inp_col;
	bool ism = true;
	cout << "X plays first. Do u wanna play first?(y/n):";
	char cmd, cmd2;
	cin >> cmd;
	int Error_limit = 5;
	if(cmd == 'y' || cmd == 'Y'){
		player = 'X';
		opponent = 'O';
		ism = false;
	}
	while(isMoveLeft(brd)){
		print_brd(brd);
		pos cmv;
		if (!ism){
			cout << "Input:";
			cin >> inp_row >> inp_col;
			if((inp_col*inp_col + inp_row * inp_row) > 8){
				continue;
			}
			cmv.row = inp_row;
			cmv.col = inp_col;
		}
		if (ism) cmv = optimal_move(brd, ism);
		if (!(brd[cmv.row][cmv.col] == '_')){
			cout << "Error: cmv: \t(" << cmv.row << ",  " << cmv.col << ").\n";
			print_brd(brd);
			Error_limit--;
			if(Error_limit < 0) return 0;
			continue; 
		}
		if (ism) {
			brd[cmv.row][cmv.col] = opponent;
		}
		else{
			brd[cmv.row][cmv.col] = player;
		}
		ism = !(ism);
		if(evaluate(brd) < 0){
			cout << "O won!";
			break;
		}
		if(evaluate(brd) > 0){
			cout << "X won!";
			break;
		}
	}
	cout << "Game_over!\n";
	print_brd(brd);
	return 0;
}
