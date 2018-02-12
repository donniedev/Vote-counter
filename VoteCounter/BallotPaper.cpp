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


int BallotPaper::getPreference()
{
	return 0;
}
