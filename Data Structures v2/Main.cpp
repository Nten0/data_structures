#include "File Actions.h"
#include "Searching Methods.h"
#include <cstdio>
#include <algorithm>
#include  <stdlib.h>
#include <time.h>

using namespace std;

extern int comparisons(0);

int main()
{
	int choice, id, val, val2, size, k, cond = 1;
	string input, answer;
	bool found;
	HotelsVector* hotels = new HotelsVector();
	Trie* DTree = new Trie();
	RBtree* RB = new RBtree();
	clock_t time;
	clock_t totalTime = 0;

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
			comparisons = 0;
			totalTime = 0;
			switch (choice)
			{
			case 1:
				for (int i = 0; i < hotels->Hotels.size(); i++)
				{
					id = rand() % hotels->Hotels.size();
					time = clock();

					val = LinearSearch(hotels->Hotels, id);
					if (val >= 0)
						cout << hotels->Hotels[val]->name << endl;
					else
						cout << "ID didn't found\n";

					time = clock() - time;
					totalTime += time;
				}
				cout << "Total time for linear search is " << ((float)totalTime / CLOCKS_PER_SEC) << " seconds\n";
				cout << "Total Comparisons for linear search are " << comparisons << endl;
				break;
			case 2:
				sort(hotels->Hotels.begin(), hotels->Hotels.end(), compByID);
				for (int i = 0; i < hotels->Hotels.size(); i++)
				{
					id = rand() % hotels->Hotels.size();
					time = clock();

					val = BinarySearch(hotels->Hotels, id, 0, hotels->Hotels.size() - 1);
					if (val >= 0)
						cout << hotels->Hotels[val]->name << endl;
					else
						cout << "ID didn't found\n";

					time = clock() - time;
					totalTime += time;
				}
				cout << "Total time for binary search is " << ((float)totalTime / CLOCKS_PER_SEC) << " seconds\n";
				cout << "Total Comparisons for binary search are " << comparisons << endl;
				break;
			case 3:
				sort(hotels->Hotels.begin(), hotels->Hotels.end(), compByID);
				cin >> id;
				for (int i = 0; i < hotels->Hotels.size(); i++)
				{
					
					time = clock();

					val = InterpolationSearch(hotels->Hotels, id);
					if (val >= 0)
						cout << hotels->Hotels[val]->name << endl;
					else
						cout << "ID didn't found\n";

					time = clock() - time;
					totalTime += time;
				}
				cout << "Total time for interpolation search is " << ((float)totalTime / CLOCKS_PER_SEC) << " seconds\n";
				cout << "Total Comparisons for interpolation search are " << comparisons << endl;
				break;
			case 4:
				for (int i = 0; i < hotels->Hotels.size(); i++)
				{
					id = rand() % hotels->Hotels.size();
					time = clock();

					RB->search(id);

					time = clock() - time;
					totalTime += time;
				}
				cout << "Total time for RED-BLACK search is " << ((float)totalTime / CLOCKS_PER_SEC) << " seconds\n";
				cout << "Total Comparisons for RED-BLACK search are " << comparisons << endl;
				break;
			default:
				cout << "ERROR: Not available option, please try again\n";
				break;
			}		
			break;
		case 5:
			comparisons = 0;
			totalTime = 0;
			sort(hotels->Hotels.begin(), hotels->Hotels.end(), compByID);
			val = rand() % hotels->Hotels.size();
			val2 = rand() % hotels->Hotels.size();
			for (int c = 0; c < hotels->Hotels.size(); c++)
			{
				time = clock();
				for (int i = 0; i < hotels->Hotels.size(); i++)
				{
					comparisons++;
					if ((hotels->Hotels[i]->stars == val) && ((hotels->Hotels[i]->Reservations.size()) == val2))
						cout << hotels->Hotels[i]->name << endl;
				}
				time = clock() - time;
				totalTime += time;
			}
			cout << "Total time for linear search is " << ((float)totalTime / CLOCKS_PER_SEC) << " seconds\n";
			cout << "Total Comparisons for linear search are " << comparisons << endl;
			break;
		case 6:
			sort(hotels->Hotels.begin(), hotels->Hotels.end(), compByID);
			found = false;
			cout << "Choose the type of search:\n";
			cout << "1.Linear search\n";
			cout << "2.Digital Tries Search\n";
			cin >> choice;
			k = rand() % hotels->Hotels.size();
			answer = hotels->Hotels[k]->Reservations[rand() % hotels->Hotels[k]->Reservations.size()]->name;
			comparisons = 0;
			totalTime = 0;
			switch (choice)
			{
			case 1:
				for (int c = 0; c < hotels->Hotels.size(); c++)
				{
					time = clock();
					for (int i = 0; i < hotels->Hotels.size(); i++)
					{
						for (int j = 0; j < hotels->Hotels[i]->Reservations.size(); j++)
						{
							comparisons++;
							if (hotels->Hotels[i]->Reservations[j]->name == answer)
							{
								found = true;
								//cout << hotels->Hotels[i]->Reservations[j]->name << " ";
								//cout << hotels->Hotels[i]->Reservations[j]->checkinDate << " ";
								//cout << hotels->Hotels[i]->Reservations[j]->stayDurationDays << endl;
							}
						}
					}
					if (found == false)
						cout << "This client doesn't exist\n";

					time = clock() - time;
					totalTime += time;
				}
				cout << "Total time for linear search is " << ((float)totalTime / CLOCKS_PER_SEC) << " seconds\n";
				cout << "Total Comparisons for linear search are " << comparisons << endl;
				break;
			case 2:
				for (int i = 0; i < hotels->Hotels.size(); i++)
				{
					time = clock();
					found = DTree->search(answer);
					time = clock() - time;
					totalTime += time;
				}
				cout << "Total time for digital tries search is " << ((float)totalTime / CLOCKS_PER_SEC) << " seconds\n";
				cout << "Total Comparisons for digital tries search are " << comparisons << endl;

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