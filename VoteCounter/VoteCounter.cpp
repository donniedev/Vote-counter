// Daniel Duda C002008007 Joint DSA & Programming Assignment 2018 VoteCounter

#include "stdafx.h"
#include <iostream>
#include <string>
#include <map>
#include "BallotPaper.h"
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int findLowest(std::map<std::string, int> map) {

	int min = 0;
	min = map.begin()->second;
	for (auto i = map.begin(); i != map.end(); ++i) {

		if (i->second < min) {
			min = i->second;
		}
	}
	return min;
}

int findLowestCount(std::map<std::string, int> map, int min, std::vector < std::string> &vec) {

	int count = 0;
	for (auto i = map.begin(); i != map.end(); ++i) {

		if (i->second == min) {
			count++;
			vec.push_back(i->first);
		}
	}
	return count;
}

std::map<std::string, int>  distribute(std::vector <BallotPaper> ballots, int pref, std::string name, std::vector < std::string> eliminatedCandidates) {

	int preference = pref;
	bool found = false;
	std::map<std::string, int> map;

	for (int i = 0; i < ballots.size(); i++) {

		for (auto j = ballots[i].ballotMap.begin(); j != ballots[i].ballotMap.end(); ++j) {// auto j1


			if (j->first == name && j->second == preference) {

				while (found == false) {

					for (auto j = ballots[i].ballotMap.begin(); j != ballots[i].ballotMap.end(); ++j) { // auto j2

						if (j->second == preference + 1) {

							//check if candidate  who is going to recive voice is not eliminated
							auto it = std::find(eliminatedCandidates.begin(), eliminatedCandidates.end(), j->first);
							if (it != eliminatedCandidates.end())
							{
								preference++;
							}
							else
							{
								map[j->first] += 1;
								found = true;
							}
							//end check
						}
					}//end for auto j 2

				}//end while
				preference = pref;
				found = false;
			}//end if j-first && j->second
		}//end for auto j 1
	}//end for int i
	return map;
}

void printMap(std::map<std::string, int> map) {

	for (auto j = map.begin(); j != map.end(); ++j) {

		std::cout << j->first << " : " << j->second << " | ";
	}
	std::cout << '\n';
}

int main()
{
	int lowest = 0;
	int lowestCount = 0;
	std::vector < std::string> lowestNames;

	int randomNumber = 0;
	std::string nameToEliminate;
	int preference = 1;
	bool wehaveWinner = false;
	int roundNumberDisplay = 0;

	std::string nameWhoRecive;
	std::vector<std::string> eliminatedCandidates;
	std::map<std::string, int> roundMap;
	std::map<std::string, int> reciveMap;

	std::vector<Candidate> candidatesV;
	std::vector<BallotPaper> ballotsV;

	//input variables
	std::ifstream myfile("votes.txt");

	std::string InputLine;
	std::string secondSplit[100];  
	std::string temp;
	std::string split;
	//loop variables
	int k = 0;//
	int m = 0;
	int n = 0;

	
	//Handle input
	if (myfile.is_open())
	{
		while (getline(myfile, InputLine))
		{
			ballotsV.push_back(BallotPaper());
			std::stringstream stream(InputLine);
			while (getline(stream, InputLine, ',')) {

				split = InputLine;

				std::stringstream stream2(split);
				while (getline(stream2, temp, '-')) {

					secondSplit[m] = temp;

					m++;
				}
			}

			for (int i = 0; i < m / 3; i++) {//Candidates size length of  array secondSplit / 3 == how many candidates

				if (k == 0) {//create candidates only from first ballot
							 //secondSplit[n] = candidate name, secondSplit[n+1] = candidate party
					candidatesV.push_back(Candidate(secondSplit[n], secondSplit[n + 1]));
				}
				//secondSplit[n] = candidate name, secondSplit[n+2] = candidate preference
				ballotsV[k].setPreference(secondSplit[n], atoi(secondSplit[n + 2].c_str()));
				n += 3;
			}
			m = 0;
			n = 0;
			k++;
		}
		myfile.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}
	//end handling input
	std::cout << '\n';

	for (int i = 0; i < ballotsV.size(); i++) {

		for (auto j = ballotsV[i].ballotMap.begin(); j != ballotsV[i].ballotMap.end(); ++j) {//start auto j


			if (j->second == preference) {

				roundMap[j->first] += 1; //insert or update candidate
			}

		}//end for auto j 
	}//end for

	 // check if candidate did not had any voices and add it to eliminated list
	for (int i = 0; i < candidatesV.size(); i++) {

		std::map<std::string, int>::iterator it;
		it = roundMap.find(candidatesV[i].getName());

		if (it != roundMap.end()) {

		}
		else {

			eliminatedCandidates.push_back(candidatesV[i].getName());
			std::cout << candidatesV[i].getName() << " Candidate eliminated no votes on this candidate " << '\n';
		}
	}

	//start rounds
	while (wehaveWinner == false) {
		std::cout << "Round nr " << roundNumberDisplay + 1 << '\n';
		printMap(roundMap);
	
		lowest = findLowest(roundMap);
		lowestCount = findLowestCount(roundMap, lowest, lowestNames);

		if (lowestCount > 1) {

			// initialize random seed: 
			srand(time(NULL));

			// generate random number(candidate to eliminate random index position)
			randomNumber = rand() % lowestNames.size();
			std::cout << lowestNames[randomNumber] << " is randomly eliminated candidate" << '\n';
			nameToEliminate = lowestNames[randomNumber];
		}
		else {//there is only one to eliminate
			nameToEliminate = lowestNames[0];
			std::cout << lowestNames[0] << " is eliminated candidate" << '\n';
		}

		eliminatedCandidates.push_back(nameToEliminate);
		roundMap.erase(nameToEliminate);

		//find candidates who receive voices
		reciveMap = distribute(ballotsV, 1, nameToEliminate, eliminatedCandidates);

		//distribute voices
		for (auto j = reciveMap.begin(); j != reciveMap.end(); ++j) {

			std::map<std::string, int>::iterator it;
			it = roundMap.find(j->first);
			if (it != roundMap.end()) {

				it->second += j->second;
				std::cout << j->first << " gets + " << j->second << '\n';
			}
		}

		std::cout << "End round nr " << roundNumberDisplay + 1 << '\n' << '\n';
		roundNumberDisplay++;
		if (roundMap.size() == 1) {

			//find candidate object to get party
			for (int i = 0; i < candidatesV.size(); i++) {

				if (candidatesV[i].getName() == roundMap.begin()->first) {

					std::cout << roundMap.begin()->first << " from " << candidatesV[i].getParty() << " is a winner with  " << roundMap.begin()->second << " voices." << '\n';
				}
			}
			wehaveWinner = true;
		}
		if (roundNumberDisplay > 100) {

			std::cout << "We have winner > 100 Something went wrong " << '\n';
			wehaveWinner = true;
		}
		// end rounds
		lowestNames.clear();
		reciveMap.clear();
	}//end while winner
	 	
	system("pause");
	return 0;
}

