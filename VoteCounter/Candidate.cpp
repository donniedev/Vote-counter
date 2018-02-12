#include "stdafx.h"
#include "Candidate.h"
#include <iostream>


Candidate::Candidate()
{
}

Candidate::Candidate(std::string n, std::string p)
{
	name = n;
	party = p;
}

Candidate::~Candidate()
{
}

void Candidate::setName(std::string n)
{
	name = n;
}

void Candidate::setParty(std::string p)
{
	party = p;
}

std::string Candidate::getName() 
{
	return name;
}

std::string Candidate::getParty()
{
	return party;
}