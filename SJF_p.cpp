#include <iostream>
#include <vector>
#include <algorithm>
#include <cfloat>
using namespace std;
/**
  *main - program entry point
  *Return: 0
  *The following code will help you to...
  *...Calcute the Average waiting time...
  *...Using the Shortest Job First Scheduling Algorithm (preemptive mode)
  */
int main() {
	int i, j, zero_found, processes_count;
	i = j = zero_found = processes_count = 0;
	double total = 0.0, accumulated_time = 0, arrival, burst, shortest_time = DBL_MAX, arrived_first;
	vector<double> arrival_time, burst_time, waiting_times, burst_copy;

	cout<<"Howdy!!!"<<endl;
	cout<<"* This program helps you to compute the average waiting time of a number of processes ..."<<endl;
	cout<<" ... in a Shortest Job First (SJF) 'preemptive' mode."<<endl;
	cout<<"* You will Enter the arrival time and burst time of each process."<<endl;
	cout<<"* Time is in milliseconds."<<endl;

	while (true) {
		cout<<"Enter arrival time (Enter -1 to quit): ";
		cin>>arrival;
		
		if (arrival == -1)
			break;
		else if (arrival < 0) {
			cout<<"Invalid input."<<endl;
			return 0;
		}
		arrival_time.push_back(arrival);

		cout<<"Enter burst time: ";
		cin>>burst;
		if (burst < 0) {
			cout<<"Invalid input."<<endl;
			return 0;
		}
		burst_time.push_back(burst);
	}
	
	while (i < arrival_time.size()) {
		if (arrival_time[i] == 0) {
			zero_found = 1;
			break;
		}
		i++;
	}

	if (!zero_found) {
		cout<<"/!\\ Invalid inputs. Input values must contain arrival time 0"<<endl;
		return 0;
	}

	processes_count = arrival_time.size();
    burst_copy = burst_time;

	while(arrival_time.size() > 0) {
		i = 0;
        shortest_time = DBL_MAX;
		while(i < arrival_time.size()) {
			if ((arrival_time[i] <= accumulated_time) && (burst_time[i] < shortest_time)) {
                if((burst_time[i] == shortest_time) && (arrival_time[i] >= arrived_first) && (i > 0)){}
                else {
					shortest_time = burst_time[i];
                    arrived_first = arrival_time[i];
					j = i;
                }
			}
			i++;
		}
        accumulated_time++;
		burst_time[j]--;
		if (burst_time[j] == 0) {
			waiting_times.push_back(accumulated_time - burst_copy[j] - arrival_time[j]);
            arrival_time.erase(arrival_time.begin() + j);
			burst_copy.erase(burst_copy.begin() + j);
			burst_time.erase(burst_time.begin() + j);
		}
	}
	cout<<"The individual waiting times are: ";
	for(auto k : waiting_times) {
		cout<<k<<" ";
		total += k;
	}
	cout<<endl;

	cout<<"The average waiting time is "<<total/processes_count<<" milliseconds."<<endl;

	return 0;
}
