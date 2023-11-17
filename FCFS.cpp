#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(void) {
    int arrival, burst, wait = 0, processes = 0;
    double total_waiting_time = 0;
    vector<int> arrival_time, burst_time, sorted_arrival, waiting_time;
    
    cout<<"Howdy!!!"<<endl;
    cout<<"* This program helps you to compute the average waiting time of a number of processes ..."<<endl;
    cout<<" ... in a First Come First Served (FCFS) fashion."<<endl;
    cout<<"* You will Enter the arrival time and burst time of each process."<<endl;
    cout<<"* Time is in milliseconds."<<endl;

    while(true) {
        if (processes == 0) {
            cout<<"Enter process-"<<processes + 1<<" arrival_time: ";
        }
        if (processes > 0) {
            cout<<"Enter process-"<<processes + 1<<" arrival_time (Enter -1 to calculate Average waiting time): ";
        }
        
        cin>>arrival;

        if (arrival == -1 && processes > 0) {
            break;
        }
        if (arrival < 0) {
            cout<<"Invalid Input."<<endl;
            return 0;
        }

        arrival_time.push_back(arrival);

        cout<<"Enter process-"<<processes + 1<<" burst_time: ";
        cin>>burst;

        if(burst < 0) {
            cout<<"Invalid Input."<<endl;
            return 0;
        }
        burst_time.push_back(burst);

        processes++;
    }

    sorted_arrival = arrival_time;
    sort(sorted_arrival.begin(), sorted_arrival.end());
    auto last = unique(sorted_arrival.begin(), sorted_arrival.end());
    sorted_arrival.erase(last, sorted_arrival.end());

    for(int i = 0; i < sorted_arrival.size(); i++) {
        for(int j = 0; j < processes; j++) {
            if(sorted_arrival[i] == arrival_time[j]) {
                waiting_time.push_back(wait - arrival_time[j]);
                wait += burst_time.at(j);
            }
        }
    }

    for(int i : waiting_time) {
        total_waiting_time += i;
    }

    cout<<endl<<"The average waiting time is "<<total_waiting_time/processes<<" milliseconds."<<endl;
    cout<<"-------------------- Stay cool, Be Happy :) ---------------------"<<endl;

    return 0;
}