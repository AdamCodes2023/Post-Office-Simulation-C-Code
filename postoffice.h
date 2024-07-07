//postoffice.h
//Written by Adam Miller on 7/6/24
//SETS UP THE FORMAT OF THE POST OFFICE THAT WILL BE SIMULATED.
#include <vector> //Vectors!

class PostOffice {
//PRIVATE WITHOUT SPECIFIC DECLARATION!
int time; //NUMBER OF "MINUTES" THAT THE POST OFFICE SIMULATION IS GOING TO RUN FOR.
std::vector<int> queue; //THE PEOPLE WAITING FOR POST OFFICE SERVICE.
std::vector<int> arrivalTimes; //THE TIMES AT WHICH PEOPLE ARRIVE AT THE POST OFFICE.
std::vector<int> departureTimes; //THE TIMES AT WHICH PEOPLE LEAVE THE POST OFFICE.
std::vector<int> waitTimes; //THE TIME EACH PERSON WAITS AT THE POST OFFICE.
int newPersonArrivalTime; //HOW MANY MINUTES AWAY A PERSON IS FROM VISITING THE POST OFFICE.
int employeeTaskTime; //HOW MANY MINUTES AWAY THE POST OFFICE EMPLOYEE IS FROM FINISHING A TASK.
//PUBLIC NOW!
public:
  //CONSTRUCTOR//
  PostOffice(int minutes);
  //CLASS METHODS//
  int generatePerson();
  int employeeCycle();
  void addToVector(std::vector<int> &, int);
  void removeFromVector(std::vector<int> &, int);
  int getVectorSize(std::vector<int> &);
  int getVectorElement(std::vector<int> &, int);
  void setPrivateIntValue(int &, int);
  int getPrivateIntValue(int &);
  void decrementPrivateIntValue(int &, int);
  void normalDayLoop();
}; //End class PostOffice
