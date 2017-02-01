#include "HotelsVector.h"
#include <iostream>
#include <fstream> 
#include <sstream>

using namespace std;

int ToInteger(const string& s)
{
	istringstream in(s);

	int returnValue;
	in >> returnValue;

	return returnValue;
}

HotelsVector* loadFile(string input)
{
	HotelsVector* hotels = new HotelsVector();
	fstream myFile, myFile2;
	int size = 0;
	string line, tmp;
	string del = ";";
	myFile.open(input.c_str());
	if (myFile.is_open())
	{
		getline(myFile, line, '\n');
		size = ToInteger(line.c_str());

		for (int i = 0; i < size; i++)
		{
			hotels->Hotels.push_back(new Hotel());
			getline(myFile, tmp, ';');
			hotels->Hotels[i]->id = atoi(tmp.c_str());
			getline(myFile, tmp, ';');
			hotels->Hotels[i]->name = tmp.c_str();
			getline(myFile, tmp, ';');
			hotels->Hotels[i]->stars = atoi(tmp.c_str());
			getline(myFile, tmp, ';');
			hotels->Hotels[i]->numberOfRooms = atoi(tmp.c_str());

			/*** Reservations ***/
			getline(myFile, line, '\n');
			line.append(del);

			
			ofstream out;
			out.open("out.txt");
			out << line;
			out.close();

			myFile2.open("out.txt");
			if (myFile2.is_open())
			{
				int j = 0;
				while (!myFile2.eof())
				{
					hotels->Hotels[i]->Reservations.push_back(new Reservation());
					getline(myFile2, tmp, ';');
					hotels->Hotels[i]->Reservations[j]->name = tmp.c_str();
					getline(myFile2, tmp, ';');
					hotels->Hotels[i]->Reservations[j]->checkinDate = tmp;
					getline(myFile2, tmp, ';');
					hotels->Hotels[i]->Reservations[j]->stayDurationDays = atoi(tmp.c_str());
					j++;
				}
				hotels->Hotels[i]->Reservations.pop_back();
				
			}
			myFile2.close();
		}
		myFile.close();
		remove("out.txt");
		return hotels;
	}
	else
		cout << "ERROR: Can't open file";
		return NULL;
}



void writeFile(string input, HotelsVector* hotels)
{
	ofstream myFile;
	string tmp;
	myFile.open(input.c_str(), ofstream::trunc);
	if (hotels->Hotels.size() > 0)
		myFile << hotels->Hotels.size() << endl;
	for (int i = 0; i < hotels->Hotels.size(); i++)
	{
		myFile << to_string(hotels->Hotels[i]->id) + ";";
		myFile << hotels->Hotels[i]->name + ";";
		myFile << to_string(hotels->Hotels[i]->stars) + ";";
		myFile << to_string(hotels->Hotels[i]->numberOfRooms) + ";";
		
		for (int j = 0; j < hotels->Hotels[i]->Reservations.size(); j++)
		{
			myFile << hotels->Hotels[i]->Reservations[j]->name + ";";
			myFile << hotels->Hotels[i]->Reservations[j]->checkinDate + ";";
			if (j < hotels->Hotels[i]->Reservations.size() - 1)
				myFile << to_string(hotels->Hotels[i]->Reservations[j]->stayDurationDays) + ";";
			else
				myFile << to_string(hotels->Hotels[i]->Reservations[j]->stayDurationDays);
		}
		myFile << endl;
	}
	myFile.close();
}