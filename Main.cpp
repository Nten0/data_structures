#include "File Actions.h"
#include "Searching Methods.h"
#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
	int choice, id, val, val2, size, cond = 1;
	string input, answer;
	bool found;
	HotelsVector* hotels = new HotelsVector();
	Trie* DTree = new Trie();
	RBtree* RB = new RBtree();

	do
	{
		cout << "1. Load Hotels and Reservations from file\n";
		cout << "2. Save Hotels and Reservations to file\n";
		cout << "3. Add a Hotel (with it's reservations)\n";
		cout << "4. Search and Display a Hotel by id\n";
		cout << "5. Display all Hotels of specific stars category and number of reservations\n";
		cout << "6. Display Reservations by surname search\n";
		cout << "7. Exit\n";
		cin >> choice;

		switch (choice)
		{
		case 1:
			cout << "Insert the filename you want to load with the .csv extension\n";
			cin >> input;
			hotels = loadFile(input);
			if (hotels != NULL)
			{
				for (int i = 0; i < hotels->Hotels.size(); i++)
				{
					RB->insert(hotels->Hotels[i]);
					for (int j = 0; j < hotels->Hotels[i]->Reservations.size(); j++)
					{
						string tmp = hotels->Hotels[i]->Reservations[j]->name;
						DTree->insert(hotels->Hotels[i]->Reservations[j], tmp);
					}
				}
				cout << "Hotels and Reservations are sucessfully loaded\n";
			}
			else
				cout << " so it's impossible to load it! Please try again\n";
			break;
		case 2:
			cout << "Insert the filename you want to save with the .csv extension\n";
			cin >> input;
			sort(hotels->Hotels.begin(), hotels->Hotels.end(), compByID);
			writeFile(input, hotels);
			cout << "File saved\n";
			break;
		case 3:
			size = hotels->Hotels.size();
			hotels->Hotels.push_back(new Hotel());
			val = 0;
			do {
				found = false;
				if (val == 0)
					cout << "Insert the id\n";
				else
					cout << "Not available id. Try again\n";

				cin >> hotels->Hotels[size]->id;
				for (int i = 0; i < size; i++)
				{
					if (hotels->Hotels[size]->id == hotels->Hotels[i]->id)
					{
						found = true;
						val++;
						break;
					}
				}
			} while (found == true);
			if (found == false)
			{
				cout << "Insert name \n";
				cin >> hotels->Hotels[size]->name;
				cout << "Insert stars \n";
				cin >> hotels->Hotels[size]->stars;
				cout << "Insert number of rooms\n";
				cin >> hotels->Hotels[size]->numberOfRooms;
				
				int i = 0;
				cout << "Do you want to add a reservation [y/n]: ";
				cin >> answer;
				while (answer == "y")
				{
					hotels->Hotels[size]->Reservations.push_back(new Reservation());
					cout << "Insert client name\n";
					cin >> hotels->Hotels[size]->Reservations[i]->name;
					cout << "Insert client check-in date\n";
					cin >> hotels->Hotels[size]->Reservations[i]->checkinDate;
					cout << "Insert client stay duration days\n";
					cin >> hotels->Hotels[size]->Reservations[i]->stayDurationDays;

					DTree->insert(hotels->Hotels[size]->Reservations[i], hotels->Hotels[size]->Reservations[i]->name);
					RB->insert(hotels->Hotels[i]);

					cout << "Do you want to add another reservation [y/n]: ";
					cin >> answer;
					i++;
				}
			}
			break;
		case 4:
			cout << "Choose the type of search:\n";
			cout << "1.Linear search\n";
			cout << "2.Binary search\n";
			cout << "3.Interpolation search\n";
			cout << "4.RED-BLACK Tree Search\n";
			cin >> choice;
			cout << "Enter the ID\n";
			cin >> id;
			switch (choice)
			{
			case 1:
				val = LinearSearch(hotels->Hotels, id);
				if (val >= 0)
					cout << hotels->Hotels[val]->name << endl;
				else
					cout << "ID didn't found\n";
				break;
			case 2:
				sort(hotels->Hotels.begin(), hotels->Hotels.end(), compByID);
				val = BinarySearch(hotels->Hotels, id, 0, hotels->Hotels.size() - 1);
				if (val >= 0)
					cout << hotels->Hotels[val]->name << endl;
				else
					cout << "ID didn't found\n";
				break;
			case 3:
				sort(hotels->Hotels.begin(), hotels->Hotels.end(), compByID);
				val = InterpolationSearch(hotels->Hotels, id);
				if (val >= 0)
					cout << hotels->Hotels[val]->name << endl;
				else
					cout << "ID didn't found\n";
				break;
			case 4:
				RB->search(id);
				break;
			default:
				cout << "ERROR: Not available option, please try again\n";
				break;
			}
			break;
		case 5:
			sort(hotels->Hotels.begin(), hotels->Hotels.end(), compByID);
			cout << "Enter the hotel's stars category\n";
			cin >> val;
			cout << "Enter the hotel's number of reservations\n";
			cin >> val2;
			for (int i = 0; i < hotels->Hotels.size(); i++)
			{
				if ((hotels->Hotels[i]->stars == val) && ((hotels->Hotels[i]->Reservations.size()) == val2))
					cout << hotels->Hotels[i]->name << endl;
			}

			break;
		case 6:
			sort(hotels->Hotels.begin(), hotels->Hotels.end(), compByID);
			found = false;
			cout << "Choose the type of search:\n";
			cout << "1.Linear search\n";
			cout << "2.Digital Tries Search\n";
			cin >> choice;
			cout << "Enter the name\n";
			cin >> answer;

			switch (choice)
			{
			case 1:
				for (int i = 0; i < hotels->Hotels.size(); i++)
				{
					for (int j = 0; j < hotels->Hotels[i]->Reservations.size(); j++)
					{
						if (hotels->Hotels[i]->Reservations[j]->name == answer)
						{
							found = true;
							cout << hotels->Hotels[i]->Reservations[j]->name << " ";
							cout << hotels->Hotels[i]->Reservations[j]->checkinDate << " ";
							cout << hotels->Hotels[i]->Reservations[j]->stayDurationDays << endl;
						}
					}
				}
				if (found == false)
					cout << "This client doesn't exist\n";
				break;
			case 2:
				found = DTree->search(answer);
				if (found == false)
					cout << "This client doesn't exist\n";
				break;
			default:
				cout << "ERROR: Not available option, please try again\n";
				break;
			}
			break;
		case 7:
			do
			{
				cout << "Are you sure you want to exit? [y/n] ";
				cin >> answer;
				if (answer == "y")
				{
					delete DTree;
					delete RB;
					exit(0);
				}
				else if (answer == "n")
					break;
				else
					cout << "ERROR: Please type only y (yes) or n (no)\n";
			} while (answer != "y");
			break;
		default:
			cout << "ERROR: Not available option, please try again\n";
			break;
		}
	} while (cond == 1);

	system("pause");
	return 0;

}