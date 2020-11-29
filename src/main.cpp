#include <chrono>
#include <fstream>
#include <iostream>

#include "../include/manager.hpp"
#include "../include/router.hpp"

using namespace std;


void client_server(){
  
  Manager manager;
  Router r1(1, &manager, {{2, 1000}, {3, 1000}, {4, 1000}, {5, 1000}});
  Router r2(2, &manager, {{1, 1000}});
  Router r3(3, &manager, {{1, 1000}});
  Router r4(4, &manager, {{1, 1000}});
  Router r5(5, &manager, {{1, 1000}});
  

  r1.set_forwarding_tables({{2, 2}, {3, 3}, {4, 4}, {5, 5}});
  r2.set_forwarding_tables({{1, 1}, {3, 1}, {4, 1}, {5, 1}});
  r3.set_forwarding_tables({{1, 1}, {2, 1}, {4, 1}, {5, 1}});
  r4.set_forwarding_tables({{1, 1}, {2, 1}, {3, 1}, {5, 1}});
  r5.set_forwarding_tables({{1, 1}, {2, 1}, {3, 1}, {4, 1}});


  manager.routers.push_back(r1);
  manager.routers.push_back(r2);
  manager.routers.push_back(r3);
  manager.routers.push_back(r4);
  manager.routers.push_back(r5);


  // messages
  manager.add_message(2, 1);
  manager.add_message(5, 1);
  manager.add_message(4, 1);



  // wait until all messages are recieved
  auto start_time = clock();

  while (!manager.finished()) {
    manager.tick();
  }

  auto end_time = clock();
  
  auto duration = float(end_time - start_time) / CLOCKS_PER_SEC;

  cout << "Time it takes for Client-Server Topology is: " << duration << " seconds" << endl << endl << endl;
 
}



void ring_topology(){

  Manager manager;
  Router r1(1, &manager, {{2, 100}, {8, 100}});
  Router r2(2, &manager, {{1, 100}, {3, 100}});
  Router r3(3, &manager, {{2, 100}, {4, 100}});
  Router r4(4, &manager, {{3, 100}, {5, 100}});
  Router r5(5, &manager, {{4, 100}, {6, 100}});
  Router r6(6, &manager, {{5, 100}, {7, 5000}});
  Router r7(7, &manager, {{6, 5000}, {8, 100}});
  Router r8(8, &manager, {{1, 100}, {7, 100}});
  

  r1.set_forwarding_tables({{2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 8}, {8, 8}});
  r2.set_forwarding_tables({{1, 1}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 1}, {8, 1}});
  r3.set_forwarding_tables({{1, 2}, {2, 2}, {4, 4}, {5, 4}, {6, 4}, {7, 2}, {8, 2}});
  r4.set_forwarding_tables({{1, 3}, {2, 3}, {3, 3}, {5, 5}, {6, 5}, {7, 3}, {8, 3}});
  r5.set_forwarding_tables({{1, 4}, {2, 4}, {3, 4}, {4, 4}, {6, 6}, {7, 4}, {8, 4}});
  r6.set_forwarding_tables({{1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {7, 5}, {8, 5}});
  r7.set_forwarding_tables({{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {8, 8}});
  r8.set_forwarding_tables({{1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 7}});
  


  manager.routers.push_back(r1);
  manager.routers.push_back(r2);
  manager.routers.push_back(r3);
  manager.routers.push_back(r4);
  manager.routers.push_back(r5);
  manager.routers.push_back(r6);
  manager.routers.push_back(r7);
  manager.routers.push_back(r8);


  // messages
  manager.add_message(1, 3);
  manager.add_message(8, 4);
  manager.add_message(6, 7);



  // wait until all messages are recieved
  auto start_time = clock();

  while (!manager.finished()) {
    manager.tick();
  }

  auto end_time = clock();
  
  auto duration = float(end_time - start_time) / CLOCKS_PER_SEC;

  cout << "Time it takes for Ring Topology is: " << duration << " seconds" << endl << endl << endl;
 

}

void complex_network(){

  Manager manager;
  Router r1(1, &manager, {{2, 300}, {5, 1200}});
  Router r2(2, &manager, {{1, 300}, {3, 800}, {7, 500}});
  Router r3(3, &manager, {{2, 800}, {6, 1500}, {7, 2000}, {8, 900}});
  Router r4(4, &manager, {{7, 300}});
  Router r5(5, &manager, {{1, 1200}, {6, 600}});
  Router r6(6, &manager, {{3, 1500}, {5, 600}, {9, 200}});
  Router r7(7, &manager, {{2, 500}, {3, 2000}, {4, 300}});
  Router r8(8, &manager, {{3, 900}, {9, 400}});
  Router r9(9, &manager, {{6, 200}, {8, 400}});
  

  r1.set_forwarding_tables({{2, 2}, {3, 2}, {4, 2}, {5, 5}, {6, 5}, {7, 2}, {8, 2}, {9, 5}});
  r2.set_forwarding_tables({{1, 1}, {3, 3}, {4, 7}, {5, 1}, {6, 1}, {7, 7}, {8, 3}, {9, 3}});
  r3.set_forwarding_tables({{1, 2}, {2, 2}, {4, 2}, {5, 6}, {6, 6}, {7, 2}, {8, 8}, {9, 8}});
  r4.set_forwarding_tables({{1, 7}, {2, 7}, {3, 7}, {5, 7}, {6, 7}, {7, 7}, {8, 7}, {9, 7}});
  r5.set_forwarding_tables({{1, 1}, {2, 1}, {3, 6}, {4, 1}, {6, 6}, {7, 1}, {8, 6}, {9, 6}});
  r6.set_forwarding_tables({{1, 5}, {2, 5}, {3, 3}, {4, 3}, {5, 5}, {7, 3}, {8, 3}, {9, 9}});
  r7.set_forwarding_tables({{1, 2}, {2, 2}, {3, 2}, {4, 4}, {5, 2}, {6, 2}, {8, 2}, {9, 2}});
  r8.set_forwarding_tables({{1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 9}, {6, 9}, {7, 3}, {9, 9}});
  r9.set_forwarding_tables({{1, 6}, {2, 8}, {3, 8}, {4, 8}, {5, 6}, {6, 6}, {7, 8}, {8, 8}});


  manager.routers.push_back(r1);
  manager.routers.push_back(r2);
  manager.routers.push_back(r3);
  manager.routers.push_back(r4);
  manager.routers.push_back(r5);
  manager.routers.push_back(r6);
  manager.routers.push_back(r7);
  manager.routers.push_back(r8);
  manager.routers.push_back(r9);


  // messages
  manager.add_message(8, 6);
  manager.add_message(1, 9);
  manager.add_message(4, 5);



  // wait until all messages are recieved
  auto start_time = clock();

  while (!manager.finished()) {
    manager.tick();
  }

  auto end_time = clock();
  
  auto duration = float(end_time - start_time) / CLOCKS_PER_SEC;

  cout << "Time it takes for Complex-Network Topology is: " << duration << " seconds" << endl << endl << endl;
 

}

int main()
{
  client_server();
  ring_topology();
  complex_network();
}


