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

//Set the values of the private integers that the post office uses.
void PostOffice::setPrivateIntValue(int &p, int n) {
  p = n;
} //End void PostOffice::setPrivateIntValue(int &p, int n)

//Get the values of the private integers that the post office uses.
int PostOffice::getPrivateIntValue(int &p) {
  return p;
} //End int PostOffice::getPrivateIntValue(int &p)

//Decrement the values of the private integers that the post office uses.
void PostOffice::decrementPrivateIntValue(int &p, int d) {
  p -= d;
} //End void PostOffice::decrementPrivateIntValue(int &p, int d)

//Get the values from the private PostOffice vectors containing wait time and queue information.
int PostOffice::getVectorElement(std::vector<int> &v, int e) {
  return v[e];
} //End int PostOffice::getVectorElement(std::vector<int> &v, int e)

//Simulates a day at the post office (480 minutes).
void PostOffice::normalDayLoop() {
  cout << "POST OFFICE IS OPEN!" << endl;
  bool employeeBusy = false;
  int totalCustomers = 0;
  int totalTaskTime = 0;
  int totalTasks = 0;
  int customersPastWorkDay = 0;
  int forceCustomerArrival = 0;
  setPrivateIntValue(newPersonArrivalTime, 0);
  setPrivateIntValue(employeeTaskTime, 0);
  for (int runTime = getPrivateIntValue(time); runTime > 0; runTime--) {
    //POST THE TIME LEFT IN THE WORK DAY!
    cout << endl << "TIME LEFT: " << runTime << endl << endl;
    //A CUSTOMER HAS TO COME INTO THE POST OFFICE IF 5 MINUTES PASSES WITHOUT A NEW CUSTOMER ARRIVING.
    forceCustomerArrival++;
    //GENERATE A POST OFFICE CUSTOMER'S ARRIVAL TIME (1 - 5 MINUTES)!
    setPrivateIntValue(newPersonArrivalTime, generatePerson());
    //A POST OFFICE CUSTOMER ARRIVES (50% CHANCE)!
    if (getPrivateIntValue(newPersonArrivalTime) == 1 || forceCustomerArrival == 5) {
      addToVector(queue, 1); 
      addToVector(arrivalTimes, runTime);
      cout << "A PERSON ARRIVES!" << endl;
      forceCustomerArrival = 0;
    } //End if (newPersonArrivalTime == 0)
    //GENERATE THE POSTAL EMPLOYEE'S TASK FOR THE NEXT CUSTOMER!
    //REMOVE THE CUSTOMER FROM THE QUEUE ONCE THE POSTAL EMPLOYEE COMPLETES THE TASK!
    if (employeeBusy == false) {
      //EMPTY QUEUE CAUSES A MEMORY LEAK BECAUSE THERE IS NOBODY TO REMOVE FROM THE QUEUE!
      if (getVectorSize(queue) > 0) {
        setPrivateIntValue(employeeTaskTime, employeeCycle());
        totalTaskTime += getPrivateIntValue(employeeTaskTime);
        totalTasks++;
        employeeBusy = true;
        removeFromVector(queue, 1);
        addToVector(departureTimes, runTime);
        totalCustomers++;
        cout << "POSTAL EMPLOYEE IS BUSY!" << endl;
        cout << "CUSTOMER #" << totalCustomers << " WAITED " << getVectorElement(arrivalTimes, totalCustomers - 1) - getVectorElement(departureTimes, totalCustomers - 1) << " MINUTE(S)!" << endl;
      } //End if (getVectorSize(queue) > 0)
    } //End if (employeeBusy == false)
    //POSTAL EMPLOYEE WORKS ON THE TASK!
    decrementPrivateIntValue(employeeTaskTime, 1);
    //FREE THE POSTAL EMPLOYEE FROM THE CURRENT TASK!
    if (getPrivateIntValue(employeeTaskTime) == 0) {
      employeeBusy = false;
      cout << "A PERSON DEPARTS! THE POSTAL EMPLOYEE IS FREE!" << endl;
    } //End if (employeeTaskTime == 0)
    //ONE MINUTE PASSES!
  } //End for (int runTime = time; runTime > 0; runTime--)
  cout << "POST OFFICE DOORS ARE CLOSED!" << endl;
  //RECORD THE NUMBER OF CUSTOMERS LEFT AT THE DOOR OF THE POST OFFICE!
  bool customerBeingHelped = false;
  if (employeeBusy == true) {
    customerBeingHelped = true;
  } //End if (employeeBusy == true)
  customersPastWorkDay = getVectorSize(queue);
  //TAKE CARE OF THE REST OF THE POST OFFICE CUSTOMERS IN THE QUEUE!
  int runTime = 0;
  bool dayFinished = false;
  //CHECK TO SEE IF THE POST OFFICE IS ABLE TO CLOSE!
  //POSTAL EMPLOYEE IS NOT BUSY AND THE QUEUE IS EMPTY!
  if (employeeBusy == false && getVectorSize(queue) == 0) {
      dayFinished = true;
  } //End if (employeeBusy == false && getVectorSize(queue) == 0)
  while (dayFinished != true) {
    //POST THE TIME WORKED PAST THE NORMAL POST OFFICE WORK DAY!
    cout << endl << "TIME OVER: " << runTime << endl << endl;
    //GENERATE THE POSTAL EMPLOYEE'S TASK FOR THE NEXT CUSTOMER!
    //REMOVE THE CUSTOMER FROM THE QUEUE ONCE THE POSTAL EMPLOYEE COMPLETES THE TASK!
    if (employeeBusy == false) {
      //EMPTY QUEUE CAUSES POST OFFICE TO CLOSE BEFORE THE FINAL CUSTOMER IS FINISHED BEING SERVED BY THE POSTAL EMPLOYEE!
      if (getVectorSize(queue) > 0) {
        setPrivateIntValue(employeeTaskTime, employeeCycle());
        totalTaskTime += getPrivateIntValue(employeeTaskTime);
        totalTasks++;
        employeeBusy = true;
        removeFromVector(queue, 1);
        addToVector(departureTimes, runTime);
        totalCustomers++;
        cout << "POSTAL EMPLOYEE IS BUSY!" << endl;
        cout << "CUSTOMER #" << totalCustomers << " WAITED " << getVectorElement(arrivalTimes, totalCustomers - 1) - getVectorElement(departureTimes, totalCustomers - 1) << " MINUTE(S)!" << endl;
      } //End if (getVectorSize(queue) != 0)
    } //End if (employeeBusy == false)
    //POSTAL EMPLOYEE WORKS ON HIS TASK!
    decrementPrivateIntValue(employeeTaskTime, 1);
    //FREE THE POSTAL EMPLOYEE FROM THE CURRENT TASK!
    if (getPrivateIntValue(employeeTaskTime) == 0) {
      employeeBusy = false;
      cout << "A PERSON DEPARTS! THE POSTAL EMPLOYEE IS FREE!" << endl;
    } //End if (employeeTaskTime == 0)

    //CHECK TO SEE IF THE POST OFFICE IS ABLE TO CLOSE!
    //POSTAL EMPLOYEE IS NOT BUSY AND THE QUEUE IS EMPTY!
    if (employeeBusy == false && getVectorSize(queue) == 0) {
      dayFinished = true;
      cout << endl;
    } else {
      //ONE MINUTE PASSES!
      runTime--;
    } //End if (employeeBusy == false && getVectorSize(queue) == 0)
  } //End while (queue.size() != 0)  
}
