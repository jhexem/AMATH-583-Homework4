#include <vector>
#include <queue>
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>


const int NUM_ELEVATORS = 3;
const int FLOORS = 20;
const int APARTMENTS_PER_FLOOR = 10;
const int MAX_PEOPLE = 5;
const int MAX_WAIT_TIME = 300; //300 works best
const int delay = 15; //15 works best

int NUM_PEOPLE = 0;
int NUM_SERVICED = 0;
std::queue<std::vector<int>> ELEVATOR0, ELEVATOR1, ELEVATOR2;
std::vector<int>E0_PASSENGERS(MAX_PEOPLE, -1);
std::vector<int>E1_PASSENGERS(MAX_PEOPLE, -1);
std::vector<int>E2_PASSENGERS(MAX_PEOPLE, -1);
std::vector<int>ELEVATOR_CURRENT_FLOORS(NUM_ELEVATORS, 0);
std::vector<int>ELEVATOR_DIRECTIONS(NUM_ELEVATORS, 1);
std::vector<int>PASSENGERS_SERVICED_PER_ELEVATOR(NUM_ELEVATORS, 0);
std::mutex E0MTX, E1MTX, E2MTX, COUTMTX, NUM_PEOPLE_MTX;


void board_person_onto_elevator(int person, std::vector<int> &elevator_passengers) {

   for (int i=0; i<MAX_PEOPLE; i++) {
      if (elevator_passengers[i] == -1) {
         elevator_passengers[i] = person;
         break;
      }
   }
}

void remove_person_from_elevator(int person, std::vector<int> &elevator_passengers) {

   for (int i=0; i<MAX_PEOPLE; i++) {
      if (elevator_passengers[i] == person) {
         elevator_passengers[i] = -1;
         break;
      }
   }

}

bool check_if_space_on_elevator(std::vector<int> &elevator_passengers) {
   for (int i=0; i<MAX_PEOPLE; i++) {
      if (elevator_passengers[i] == -1) {
         return true;
      }
   }
   return false;
}

int closest_elevator(int current_floor, int direction) {

   int idx = 0;
   int min_distance = FLOORS;
   std::vector<int> same_direction_elevator_indices;

   for (int i=0; i<NUM_ELEVATORS; i++) {
      if (direction == ELEVATOR_DIRECTIONS[i]) {
         same_direction_elevator_indices.push_back(i);
      }
   }

   if (same_direction_elevator_indices.size() == 0) {
      for (int i=0; i<NUM_ELEVATORS; i++) {
         int distance = abs(ELEVATOR_CURRENT_FLOORS[i] - current_floor);
         if (distance < min_distance) {
            min_distance = distance;
            idx = i;
         }
      }
   }
   else {
      for (int i=0; i<same_direction_elevator_indices.size(); i++) {
         int distance = abs(ELEVATOR_CURRENT_FLOORS[same_direction_elevator_indices[i]] - current_floor);
         if (distance < min_distance) {
            min_distance = distance;
            idx = same_direction_elevator_indices[i];
         }
      }
   }

   return idx;

}

void step_towards_destination(int &current_floor, int direction, int elevator) {

   if (direction != -1) {
      current_floor++;
   }
   else {
      current_floor--;
   }
   ELEVATOR_CURRENT_FLOORS[elevator] = current_floor;
}

void person(int i) {

   std::random_device myRandomDevice;
   unsigned seed = myRandomDevice();
   std::default_random_engine gen(seed);
   std::uniform_int_distribution<int> dist(0, FLOORS-1);

   int current_floor = dist(gen);
   int destination = dist(gen);
   while (current_floor == destination) {
      destination = dist(gen);
   }
   int direction = (destination - current_floor) / abs(destination - current_floor);

   bool person_boarded = false;
   bool person_serviced = false;

   COUTMTX.lock();
   std::cout << "Person " << i << " wants to go from floor " << current_floor << " to floor " << destination << std::endl;
   COUTMTX.unlock();

   int elevator_chosen = closest_elevator(current_floor, direction);
   std::vector<int> person_info = {current_floor, destination, direction};

   switch (elevator_chosen) {
      case 0:
         E0MTX.lock();
         ELEVATOR0.push(person_info);
         E0MTX.unlock();

         while (!person_boarded) {
            if (ELEVATOR_CURRENT_FLOORS[0] == current_floor) {
               if (check_if_space_on_elevator(E0_PASSENGERS)) {
                  board_person_onto_elevator(i, E0_PASSENGERS);
                  person_boarded = true;

                  COUTMTX.lock();
                  std::cout << "Person " << i << " has entered elevator " << 0 << std::endl;
                  COUTMTX.unlock();
               }
               else {
                  E0MTX.lock();
                  ELEVATOR0.push(person_info);
                  E0MTX.unlock();
               }
            }
         }

         while (!person_serviced) {
            if (ELEVATOR_CURRENT_FLOORS[0] == destination) {
               remove_person_from_elevator(i, E0_PASSENGERS);
               person_serviced = true;
            }
         }

         break;
      case 1:
         E1MTX.lock();
         ELEVATOR1.push(person_info);
         E1MTX.unlock();

         while (!person_boarded) {
            if (ELEVATOR_CURRENT_FLOORS[1] == current_floor) {
               if (check_if_space_on_elevator(E1_PASSENGERS)) {
                  board_person_onto_elevator(i, E1_PASSENGERS);
                  person_boarded = true;
                  COUTMTX.lock();
                  std::cout << "Person " << i << " has entered elevator " << 1 << std::endl;
                  COUTMTX.unlock();
               }
               else {
                  E1MTX.lock();
                  ELEVATOR1.push(person_info);
                  E1MTX.unlock();
               }
            }
         }

         while (!person_serviced) {
            if (ELEVATOR_CURRENT_FLOORS[1] == destination) {
               remove_person_from_elevator(i, E1_PASSENGERS);
               person_serviced = true;
            }
         }

         break;
      case 2:
         E2MTX.lock();
         ELEVATOR2.push(person_info);
         E2MTX.unlock();

         while (!person_boarded) {
            if (ELEVATOR_CURRENT_FLOORS[2] == current_floor) {
               if (check_if_space_on_elevator(E2_PASSENGERS)) {
                  board_person_onto_elevator(i, E2_PASSENGERS);
                  person_boarded = true;
                  COUTMTX.lock();
                  std::cout << "Person " << i << " has entered elevator " << 2 << std::endl;
                  COUTMTX.unlock();
               }
               else {
                  E2MTX.lock();
                  ELEVATOR2.push(person_info);
                  E2MTX.unlock();
               }
            }
         }

         while (!person_serviced) {
            if (ELEVATOR_CURRENT_FLOORS[2] == destination) {
               remove_person_from_elevator(i, E2_PASSENGERS);
               person_serviced = true;
            }
         }

         break;
   }

}

void elevator(int i) {

   int current_floor = 0;
   int destination = 0;
   int passengers = 0;

   while (NUM_SERVICED < NUM_PEOPLE) {

      switch (i) {
         case 0:
            if (!ELEVATOR0.empty()) {
               std::vector<std::vector<int>> people;
               int number_of_people = 0;
               
               E0MTX.lock();
               people.push_back(ELEVATOR0.front());
               ELEVATOR0.pop();
               E0MTX.unlock();
               ELEVATOR_CURRENT_FLOORS[0] = current_floor;
               number_of_people++;

               destination = people[number_of_people - 1][0];
               ELEVATOR_DIRECTIONS[0] = (destination - current_floor) / abs(destination - current_floor);

               int next_destination = people[number_of_people - 1][1];

               COUTMTX.lock();
               std::cout << "Elevator 0 moving from floor " << current_floor << " to floor " << destination << std::endl;
               COUTMTX.unlock();

               while (current_floor != destination) {
                  step_towards_destination(current_floor, ELEVATOR_DIRECTIONS[0], 0);
                  std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                  if (!ELEVATOR0.empty()) {
                     if ((ELEVATOR0.front()[0] == current_floor && ELEVATOR0.front()[2] == ELEVATOR_DIRECTIONS[0]) && passengers < 5) {
                        E0MTX.lock();
                        people.push_back(ELEVATOR0.front());
                        ELEVATOR0.pop();
                        E0MTX.unlock();
                        number_of_people++;
                        passengers++;

                        if ((people[number_of_people - 1][1] > destination && people[number_of_people - 1][2] == 1) || (people[number_of_people - 1][1] < destination && people[number_of_people - 1][2] == -1)) {
                           destination = people[number_of_people - 1][1];
                        }

                        COUTMTX.lock();
                        std::cout << "Elevator 0 moving from floor " << current_floor << " to floor " << destination << std::endl;
                        //std::cout << "Elevator 0 passengers: " << passengers << std::endl;
                        COUTMTX.unlock();
                     }
                  }
               }

               destination = next_destination;
               passengers = 0;
               passengers++;
               ELEVATOR_DIRECTIONS[0] = (destination - current_floor) / abs(destination - current_floor);
               COUTMTX.lock();
               std::cout << "Elevator 0 moving from floor " << current_floor << " to floor " << destination << std::endl;
               COUTMTX.unlock();

               while (current_floor != destination) {
                  step_towards_destination(current_floor, ELEVATOR_DIRECTIONS[0], 0);
                  std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                  if (!ELEVATOR0.empty()) {
                     if ((ELEVATOR0.front()[0] == current_floor && ELEVATOR0.front()[2] == ELEVATOR_DIRECTIONS[0]) && passengers < 5) {
                        E0MTX.lock();
                        people.push_back(ELEVATOR0.front());
                        ELEVATOR0.pop();
                        E0MTX.unlock();
                        number_of_people++;
                        passengers++;

                        if ((people[number_of_people - 1][1] > destination && people[number_of_people - 1][2] == 1) || (people[number_of_people - 1][1] < destination && people[number_of_people - 1][2] == -1)) {
                           destination = people[number_of_people - 1][1];
                        }

                        COUTMTX.lock();
                        std::cout << "Elevator 0 moving from floor " << current_floor << " to floor " << destination << std::endl;
                        //std::cout << "Elevator 0 passengers: " << passengers << std::endl;
                        COUTMTX.unlock();
                     }
                  }
               }

               passengers = 0;

               NUM_PEOPLE_MTX.lock();
               NUM_SERVICED += number_of_people;
               PASSENGERS_SERVICED_PER_ELEVATOR[0] += number_of_people;
               NUM_PEOPLE_MTX.unlock();
            }
            break;
         case 1:
            if (!ELEVATOR1.empty()) {
               std::vector<std::vector<int>> people;
               int number_of_people = 0;

               E1MTX.lock();
               people.push_back(ELEVATOR1.front());
               ELEVATOR1.pop();
               E1MTX.unlock();
               ELEVATOR_CURRENT_FLOORS[1] = current_floor;
               number_of_people++;

               destination = people[number_of_people - 1][0];
               ELEVATOR_DIRECTIONS[1] = (destination - current_floor) / abs(destination - current_floor);
               
               int next_destination = people[number_of_people - 1][1];

               COUTMTX.lock();
               std::cout << "Elevator 1 moving from floor " << current_floor << " to floor " << destination << std::endl;
               COUTMTX.unlock();

               while (current_floor != destination) {
                  step_towards_destination(current_floor, ELEVATOR_DIRECTIONS[1], 1);
                  std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                  if (!ELEVATOR1.empty()) {
                     if ((ELEVATOR1.front()[0] == current_floor && ELEVATOR1.front()[2] == ELEVATOR_DIRECTIONS[1]) && passengers < 5) {
                        E1MTX.lock();
                        people.push_back(ELEVATOR1.front());
                        ELEVATOR1.pop();
                        E1MTX.unlock();
                        number_of_people++;
                        passengers++;

                        if ((people[number_of_people - 1][1] > destination && people[number_of_people - 1][2] == 1) || (people[number_of_people - 1][1] < destination && people[number_of_people - 1][2] == -1)) {
                           destination = people[number_of_people - 1][1];
                        }

                        COUTMTX.lock();
                        std::cout << "Elevator 1 moving from floor " << current_floor << " to floor " << destination << std::endl;
                        //std::cout << "Elevator 1 passengers: " << passengers << std::endl;
                        COUTMTX.unlock();
                     }
                  }
               }

               destination = next_destination;
               passengers = 0;
               passengers++;
               ELEVATOR_DIRECTIONS[1] = (destination - current_floor) / abs(destination - current_floor);
               COUTMTX.lock();
               std::cout << "Elevator 1 moving from floor " << current_floor << " to floor " << destination << std::endl;
               COUTMTX.unlock();

               while (current_floor != destination) {
                  step_towards_destination(current_floor, ELEVATOR_DIRECTIONS[1], 1);
                  std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                  if (!ELEVATOR1.empty()) {
                     if ((ELEVATOR1.front()[0] == current_floor && ELEVATOR1.front()[2] == ELEVATOR_DIRECTIONS[1]) && passengers < 5) {
                        E1MTX.lock();
                        people.push_back(ELEVATOR1.front());
                        ELEVATOR1.pop();
                        E1MTX.unlock();
                        number_of_people++;
                        passengers++;

                        if ((people[number_of_people - 1][1] > destination && people[number_of_people - 1][2] == 1) || (people[number_of_people - 1][1] < destination && people[number_of_people - 1][2] == -1)) {
                           destination = people[number_of_people - 1][1];
                        }

                        COUTMTX.lock();
                        std::cout << "Elevator 1 moving from floor " << current_floor << " to floor " << destination << std::endl;
                        //std::cout << "Elevator 1 passengers: " << passengers << std::endl;
                        COUTMTX.unlock();
                     }
                  }
               }

               passengers = 0;

               NUM_PEOPLE_MTX.lock();
               NUM_SERVICED += number_of_people;
               PASSENGERS_SERVICED_PER_ELEVATOR[1] += number_of_people;
               NUM_PEOPLE_MTX.unlock();
            }
            break;
         case 2:
            if (!ELEVATOR2.empty()) {
               std::vector<std::vector<int>> people;
               int number_of_people = 0;

               E2MTX.lock();
               people.push_back(ELEVATOR2.front());
               ELEVATOR2.pop();
               E2MTX.unlock();
               ELEVATOR_CURRENT_FLOORS[2] = current_floor;
               number_of_people++;

               destination = people[number_of_people - 1][0];
               ELEVATOR_DIRECTIONS[2] = (destination - current_floor) / abs(destination - current_floor);
               
               int next_destination = people[number_of_people - 1][1];

               COUTMTX.lock();
               std::cout << "Elevator 2 moving from floor " << current_floor << " to floor " << destination << std::endl;
               COUTMTX.unlock();

               while (current_floor != destination) {
                  step_towards_destination(current_floor, ELEVATOR_DIRECTIONS[2], 2);
                  std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                  if (!ELEVATOR2.empty()) {
                     if ((ELEVATOR2.front()[0] == current_floor && ELEVATOR2.front()[2] == ELEVATOR_DIRECTIONS[2]) && passengers < 5) {
                        E2MTX.lock();
                        people.push_back(ELEVATOR2.front());
                        ELEVATOR2.pop();
                        E2MTX.unlock();
                        number_of_people++;
                        passengers++;

                        if ((people[number_of_people - 1][1] > destination && people[number_of_people - 1][2] == 1) || (people[number_of_people - 1][1] < destination && people[number_of_people - 1][2] == -1)) {
                           destination = people[number_of_people - 1][1];
                        }

                        COUTMTX.lock();
                        std::cout << "Elevator 2 moving from floor " << current_floor << " to floor " << destination << std::endl;
                        //std::cout << "Elevator 2 passengers: " << passengers << std::endl;
                        COUTMTX.unlock();
                     }
                  }
               }

               destination = next_destination;
               passengers = 0;
               passengers++;
               ELEVATOR_DIRECTIONS[2] = (destination - current_floor) / abs(destination - current_floor);
               COUTMTX.lock();
               std::cout << "Elevator 2 moving from floor " << current_floor << " to floor " << destination << std::endl;
               COUTMTX.unlock();

               while (current_floor != destination) {
                  step_towards_destination(current_floor, ELEVATOR_DIRECTIONS[2], 2);
                  std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                  if (!ELEVATOR2.empty()) {
                     if ((ELEVATOR2.front()[0] == current_floor && ELEVATOR2.front()[2] == ELEVATOR_DIRECTIONS[2]) && passengers < 5) {
                        E2MTX.lock();
                        people.push_back(ELEVATOR2.front());
                        ELEVATOR2.pop();
                        E2MTX.unlock();
                        number_of_people++;
                        passengers++;

                        if ((people[number_of_people - 1][1] > destination && people[number_of_people - 1][2] == 1) || (people[number_of_people - 1][1] < destination && people[number_of_people - 1][2] == -1)) {
                           destination = people[number_of_people - 1][1];
                        }

                        COUTMTX.lock();
                        std::cout << "Elevator 2 moving from floor " << current_floor << " to floor " << destination << std::endl;
                        //std::cout << "Elevator 2 passengers: " << passengers << std::endl;
                        COUTMTX.unlock();
                     }
                  }
               }

               passengers = 0;

               NUM_PEOPLE_MTX.lock();
               NUM_SERVICED += number_of_people;
               PASSENGERS_SERVICED_PER_ELEVATOR[2] += number_of_people;
               NUM_PEOPLE_MTX.unlock();
            }
            break;
      }

   }

   COUTMTX.lock();
   std::cout << "Elevator " << i << " has finished servicing " << PASSENGERS_SERVICED_PER_ELEVATOR[i] << " people." << std::endl;
   COUTMTX.unlock();
}

int main(int argc, char **argv) {

   if (argc!=2) {
      std::cerr << "Usage: " << argv[0] << " numPeople" << std::endl;
      return 1;
   }

   const int input = std::atoi(argv[1]);
   NUM_PEOPLE = input;

   std::thread elevators[NUM_ELEVATORS];
   for (int i=0; i<NUM_ELEVATORS; i++) {
      elevators[i] = std::thread(elevator, i);
   }

   std::random_device myRandomDevice;
   unsigned seed = myRandomDevice();
   std::default_random_engine gen(seed);
   std::uniform_int_distribution<int> dist(0, MAX_WAIT_TIME);

   for (int i=0; i<NUM_PEOPLE; i++) {
      int wait_time = dist(gen);
      std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));
      std::thread people(person, i);
      people.detach();
   }

   while (NUM_SERVICED < NUM_PEOPLE) {
      std::this_thread::yield();
   }

   COUTMTX.lock();
   std::cout << "Job completed!" << std::endl;
   COUTMTX.unlock();

   for (int i=0; i<NUM_ELEVATORS; i++) {
      elevators[i].join();
   }

   return 0;
}