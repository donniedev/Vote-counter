#include "stdafx.h"
#include "BallotPaper.h"
#include <iostream>

BallotPaper::BallotPaper()
{

}

BallotPaper::~BallotPaper()
{

}

void BallotPaper::setPreference(std::string name, int pref)
{
	ballotMap.insert(std::pair<std::string, int>(name, pref));
}


std::string BallotPaper::getPreference(int pref)
{
	std::string temp;
	for (auto j = ballotMap.begin(); j != ballotMap.end(); ++j) {

		if (j->second == pref) {
			temp = j->first;
		}
	}
	return temp;
}
