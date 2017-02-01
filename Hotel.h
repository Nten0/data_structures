#include "Reservation.h"
#include <vector>


class Hotel
{
public:
	int id, stars, numberOfRooms;
	string name;
	vector<Reservation*> Reservations;
}; 


bool compByID(Hotel* hotel1, Hotel* hotel2)
{
	return (hotel1->id < hotel2->id);
}