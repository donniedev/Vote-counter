#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>

class Candidate
{
private:
	std::string name;
	std::string party;
public:

	Candidate();

	Candidate(std::string, std::string);
	~Candidate();
	void setName(std::string);
	void setParty(std::string);

	std::string getName();
	std::string getParty();

};
