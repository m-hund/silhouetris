#include "Score.h"

///////////////////////////////////////////////////////////////
Score::Score() {
	font.loadFont("8bitoperator_jve.ttf", 44);	

	// initialize score table with zeros
	int i = 0;
	while(i < 10) {
		scoreTable.push_back(0);
		i++;
	}

	highscore = 0;
}

Score::~Score() {
}

///////////////////////////////////////////////////////////////
void Score::update(int aValue) {
	highscore += aValue;
}

void Score::draw(int aX, int aY) {
	ofSetColor(39, 40, 32);
	stringstream ss;
	ss << highscore;
	font.drawString(ss.str(), aX, aY);
}

void Score::drawCounter(int aX, int aY, int aValue) {
	ofSetColor(39, 40, 32);
	stringstream ss;
	ss << aValue;
	font.drawString(ss.str(), aX, aY);
}

void Score::drawScoreTable(int aX, int aY) {
	ofSetColor(39, 40, 32);
	for(int i = 0; i < scoreTable.size(); i++) {
		stringstream ss;
		ss << scoreTable.at(i);
		font.drawString(ss.str(), aX, aY + i * 40);
	}
}

int Score::calcScore(Piece* aPiece) {
	complexCalcR0 = 0; // top row
	complexCalcR1 = 0;
	complexCalcR2 = 0;
	complexCalcR3 = 0; // bottom row

	// counting blocks in each row
	for(int i = 0; i < Piece::PIECE_COLUMNS; i++) {
		for(int j = 0; j < Piece::PIECE_ROWS; j++) {
			if(aPiece->isActiveBlock(i, j)) {
				switch (j) {
				case 0: 
					complexCalcR0++; 
					break;
				case 1: 
					complexCalcR1++;
					break;
				case 2: 
					complexCalcR2++; 
					break;				
				case 3: 
					complexCalcR3++; 
					break;
				default:
					break;
				}
			}
		}
	}

	if(complexCalcR3 != 0) {
		complexCalc = (3 * complexCalcR0 + 
			       2 * complexCalcR1 + 
				   complexCalcR2 + 
				   complexCalcR3) / complexCalcR3;
	
	} 
	else {
		complexCalc = 3 * complexCalcR0 + 
			      2 * complexCalcR1 + 
				  complexCalcR2;
	}
	
	if(complexCalc <=3 ) {
		return 1;

	} 
	else if(complexCalc <= 6) {
		return 2;
	} 
	else if(complexCalc <= 9) {
		return 3;
	} 
	else if(complexCalc <= 11) {
		return 4;
	} 
	else if(complexCalc <= 14) {
		return 5;
	} 
	else {
		return 6;
	}
}

void Score::reset() {
	scoreTable.push_back(highscore);
	sort(scoreTable.rbegin(), scoreTable.rend());
	scoreTable.pop_back();
	
	highscore = 0;
}
