//Post Office Simulation
//Written by Adam Miller on 7/6/24
//Description: This program simulates the line at the post office. 
//Customers are able to enter the post office at any time during the 480 minute day. 
//They arrive at intervals of 1 to 5 minutes and each customer has a task to handle with the postal employee. 
//The task time can take between 1 and 4 minutes. 
//With only one employee working, if the employee is helping another customer, all entering customers will be placed 
//in line and helped in the order in which they arrived. This simple concept is illustrated using a queue to hold the time at 
//which each customer arrives and a simple state machine to flag the status of the employee as either busy or available. 
//All of this is contained in a while loop that runs for 480 iterations to simulate the length of a business day. 
//If there is anyone left in the queue at the end of the 480 iterations, they are simply de-queued until the queue is empty. 
//This program may also use an additional C++ file to hold all of the functions associated with the main method. 
//Things to display at the closing of the doors would be total number of people processed, longest wait time, 
//shortest wait time, average wait time, average task time, and how many customers are left at the door.

#include "postoffice.h" //POST OFFICE CLASS TO RUN THE SIMULATION!

int main() {

  //RUN THE SIMULATION WITH THE POST OFFICE CLASS (480 MINUTES)!
  PostOffice postOffice(480);
  postOffice.normalDayLoop();
  //Complete int main()
  return 0;
} //End int main()
