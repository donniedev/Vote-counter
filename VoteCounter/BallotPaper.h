#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>
#include <map>
#include <list>
#include "Candidate.h"

class BallotPaper
{
private:

public:
	std::map<std::string, int> ballotMap;

	BallotPaper();
	~BallotPaper();

	void setPreference(std::string, int);

	std::string getPreference(int);

};

