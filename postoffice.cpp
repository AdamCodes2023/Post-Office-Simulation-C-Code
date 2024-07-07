//postoffice.cpp
//Written by Adam Miller on 7/6/24.
//DEFINES THE POSTOFFICE CLASS AND ALL OF ITS METHODS TO SIMULATE A REAL POST OFFICE.
#include <iostream> //COUT AND CIN STATEMENTS
#include <random> //RANDOM NUMBER GENERATOR
#include "postoffice.h" //POSTOFFICE CLASS OUTLINE

using namespace std; //No std::

//Ensures PostOffice objects are created with a positive amount of time.
//Any rogue values will be set to an integer 0.
PostOffice::PostOffice(int minutes) {
  if (minutes < 0) {
    setPrivateIntValue(time, 0); //Minimum amount of time.
  } else {
    setPrivateIntValue(time, minutes);
  } //End if (minutes < 0)
} //End PostOffice::PostOffice(int minutes)

//Generates a queue of customers that visit the post office during the day (1 to 5 minutes).
int PostOffice::generatePerson() {
  //Variables
  //Use to create a random seed (Mersenne Twister)!
  random_device rdev; 
  mt19937 mt(rdev());

  //This will produce pseudorandom integers between 1 and 2.
  uniform_int_distribution<int> dist(1, 2);
  int random = dist(mt);
  return random;
} //End int PostOffice::generatePerson()

//Generates the work that a post office employee will perform with a customer (1 to 4 minutes).
int PostOffice::employeeCycle() {
  //Variables
  //Use to create a random seed (Mersenne Twister)!
  random_device rdev; 
  mt19937 mt(rdev());

  //This will produce pseudorandom integers between 1 and 4.
  uniform_int_distribution<int> dist(1, 4);
  return dist(mt);
} //End int PostOffice::employeeCycle()

//Add to the post office queue and arrival time vectors.
void PostOffice::addToVector(std::vector<int> &v, int e) {
  v.push_back(e);
} //End void addToVector(std::vector<int> &v)

//Remove from the post office queue and arrival time vectors.
void PostOffice::removeFromVector(std::vector<int> &v, int pos) {
  v.erase(v.begin() + (pos - 1));
} //End void removeFromVector(std::vector<int> &v, int pos)

//Get the sizes of the vectors used by the post office.
int PostOffice::getVectorSize(std::vector<int> &v) {
  return v.size();
} //End int PostOffice::getVectorSize(std::vector<int> &v)
