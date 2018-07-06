#pragma once
#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include <algorithm>

bool comp_second(const std::pair<std::string, std::string> previous, const std::pair<std::string, std::string> current);
bool comp_second_int(const std::pair<int, std::string> previous, const std::pair<int, std::string> current);

static void HardySort
(	const std::string source,
	const std::string target	)
{
	// Declaration of Lists as substitution of Files for sake of simplicity
	std::list<std::pair<std::string, std::string>> Original;
	std::list<std::pair<std::string, std::string>> F;
	std::list<std::pair<int, std::string>> G;
	std::list<std::pair<std::string, std::string>> H;
	std::list<std::pair<std::string, std::string>> DevF;
	std::list<std::pair<int, std::string>> DevG;

	int N;
	int t;

	// Take the source in and load into 
	std::ifstream sosFile;
	sosFile.open(source);

	// Insert file data into list Original
	std::string line;
	while (std::getline(sosFile, line))
	{
		std::istringstream iss(line);
		std::string delimiter = ",";

		std::string left = line.substr(0, line.find(delimiter));
		line.erase(0, line.find(delimiter) + delimiter.length());
		std::string right = line;

		Original.push_back(std::make_pair(left, right));
	}

	// Get the value of N from size of Original list
	N = Original.size();

	// Prepare file F
	std::list<std::pair<std::string, std::string>>::iterator
		itrOri1 = Original.begin();
	std::list<std::pair<std::string, std::string>>::iterator
		itrOri2 = Original.begin();

	for (auto a : Original)
	{
		while (true)
		{
			if (itrOri1 != Original.end() && itrOri2 != Original.end()
				&& itrOri1->second == itrOri2->first)
			{
				F.push_back(std::make_pair(itrOri1->first, itrOri2->second));
				break;
			}

			else if (itrOri2 != Original.end()) ++itrOri2;

			else
			{
				G.push_back(std::make_pair(N - 1, itrOri1->first));
				G.push_back(std::make_pair(N, itrOri1->second));
				break;
			}
		}

		// Successfully end this 
		if (itrOri1 != Original.end())
		{
			++itrOri1; // increment iterator
			itrOri2 = Original.begin();
		}
	}

	// Prepare file G, sort by second component
	G.sort(comp_second_int);
	
	// Prepare file H, copy from file F, then sort by first component
	H = F;
	H.sort();

	// Now sort file F by second component
	F.sort(comp_second);

	// Start of loop of algorithm
	for (t = 2; t < N; t *= 2)
	{
		// Algorithm
		std::list<std::pair<std::string, std::string>>::iterator
			itrF = F.begin();
		std::list<std::pair<int, std::string>>::iterator
			itrG = G.begin();
		std::list<std::pair<std::string, std::string>>::iterator
			itrH = H.begin();

		while (itrF != F.end()) // When F is not empty or exhausted
		{
			// Case 1
			if (itrF != F.end() && itrH != H.end() && itrF->second == itrH->first)
			{
				DevF.push_back(std::make_pair(itrF->first, itrH->second));
				itrF++;
				itrH++;
			}

			// Case 2
			if (itrF != F.end() && itrG != G.end() && itrF->second == itrG->second)
			{
				DevG.push_back(std::make_pair((itrG->first) - t, itrF->first));
				itrF++;
				itrG++;
			}

			// Case 3
			if (itrF != F.end() && itrG != G.end() && itrF->second > itrG->second)
			{
				itrG++;
			}

			// Case 4
			if (itrF != F.end() && itrH != H.end() && itrF->second > itrH->first)
			{
				itrH++;
			}
		}

		//// After F is exhausted, sort DevG by second component
		DevG.sort(comp_second_int);

		//// Merge G with DevG
		DevG.merge(G, comp_second_int);

		//// Replace t by 2t, F by DevF, G by DevG
		G = DevG;
		F = DevF;
		DevG.clear();
		DevF.clear();

		//// Repeat preprocessing steps
		H = F;
		F.sort(comp_second);
		H.sort();
	}

	// Write into a file...?
	std::ofstream tgtFile;
	tgtFile.open(target);

	while(!G.empty())
	{
		std::list<std::pair<int, std::string>>::iterator tmpG = G.begin();
		std::string name = tmpG->second;
		G.pop_front();
		tgtFile << name << std::endl;
	}
}

// Comparator to compare value instead of key
bool comp_second(const std::pair<std::string, std::string> previous, const std::pair<std::string, std::string> current)
{
	return (previous.second < current.second);
}

// Comparator to compare value in G
bool comp_second_int(const std::pair<int, std::string> previous, const std::pair<int, std::string> current)
{
	return (previous.second < current.second);
}