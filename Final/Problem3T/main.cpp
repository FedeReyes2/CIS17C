/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <queue>
#include <random>
#include <array>
#include <algorithm>

#include "Classes.hxx"

bool hasCustomerArrived(std::mt19937 &rng, double timeBetweenCustomerArrival);



void runSimulation(std::mt19937 &rng)
{
    // 1 min = 4;1 hour = 240; 4 min waiting = 16
    int totalNumCostumers, simulationTime{240}, numberOfServers{3}, timeBetweenCA{16}, totalTimeWaiting{0};
    std::array<Clerks, 4> servers{Clerks{4},Clerks{2},Clerks{3},Clerks{4}};

    std::queue<CostumerType> myCostumers;

    for(int clockP{1}; clockP <= simulationTime; clockP++)
    {
      std::cout << clockP << std::endl;
        if(hasCustomerArrived(rng, static_cast<double>(timeBetweenCA)))
        {
            std::cout << "costumer has arrived" <<'\n';
            totalNumCostumers++;
            bool found{};
            for(size_t i{}; i < numberOfServers; i++)
            {
                if(!found)
                {
                    if(!servers[i].returnBusy())
                    {
                      servers[i].setBusy(true);
                      found = true;
                    }
                }
                
            }
            myCostumers.push(CostumerType {0});
        }
        
        if(myCostumers.size() == 5)
        {
            numberOfServers = 4;
        }
        else if(myCostumers.size() == 0)
        {
            numberOfServers = 3;
        }
        
        for(auto& i : servers)
        {
            if(i.returnBusy())
            {
                i.setIClock();
                if(i.returnInnerClock() == i.returnTimeAverage())
                {  
                    totalTimeWaiting+=myCostumers.front().returnMyTime();
                    myCostumers.pop();
                    i.setInnerClockZero();
                    i.setBusy(false);
                }
            }
        }
        for(size_t i{}; i < myCostumers.size();i++)
        {
            myCostumers.push(CostumerType {myCostumers.front().returnMyTime()+1});
            myCostumers.pop();
        }
        
   
    }
    double average = static_cast<double>(totalTimeWaiting)/static_cast<double>(totalNumCostumers);
    std::cout << totalTimeWaiting << '\n';
    std::cout << "my average customer waiting is: " << average << std::endl;
    std::cout << "The number of Costumer was: " << totalNumCostumers << std::endl;
}

int main()
{
   
    std::random_device rd;
    std::mt19937 rng(rd());
    runSimulation(rng);

    return 0;
}

bool hasCustomerArrived(std::mt19937 &rng, double timeBetweenCustomerArrival)
{
    double value = static_cast<double>(rng()) / static_cast<double>(rng.max());
    return (value > std::exp(-1.0 / timeBetweenCustomerArrival));
}