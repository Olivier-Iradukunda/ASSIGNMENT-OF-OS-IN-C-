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
  *...Using the priority (preemptive) Scheduling Algorithm
  */
int main() {
	int i, j, zero_found, p, invalid_priority, processes_count;
	i = j = zero_found = p = invalid_priority = processes_count = 0;
	double total = 0.0, accumulated_time = 0, arrival, burst, high_priority = DBL_MAX, arrived_first;
	vector<double> arrival_time, burst_time, waiting_times, burst_copy, priority;

	cout<<"Howdy!!!"<<endl;
	cout<<"* This program helps you to compute the average waiting time of a number of processes ..."<<endl;
	cout<<" ... in a priority scheduling 'preemptive' mode."<<endl;
	cout<<"* You will Enter the arrival time, priority and burst time of each process."<<endl;
	cout<<"* Time is in milliseconds."<<endl;
    cout<<"* Priority values must be less or equal to the number of processes."<<endl;

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

        cout<<"Enter priority: ";
        cin>>p;

        if(p <= 0) {
            cout<<"Invalid input priority, priority can't be zero or less than zero."<<endl;
            return 0;
        }
        priority.push_back(p);

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
        if (priority[i] > priority.size()) {
            invalid_priority = 1;
            break;
        }
		i++;
	}

	if (!zero_found) {
		cout<<"/!\\ Invalid inputs. Input values must contain arrival time 0"<<endl;
		return 0;
	}
    if(invalid_priority) {
        cout<<"Invalid input priority. Priority can not be greater than the number of input processes.";
        return 0;
    }


	processes_count = arrival_time.size();
    burst_copy = burst_time;

	while(arrival_time.size() > 0) {
		i = 0;
        high_priority = DBL_MAX;
		while(i < arrival_time.size()) {
			if ((arrival_time[i] <= accumulated_time) && (priority[i] <= high_priority)) {
                if((priority[i] == high_priority) && (arrival_time[i] >= arrived_first) && (i > 0)){}
                else {
					high_priority = priority[i];
                    arrived_first = arrival_time[i];
					j = i;
                }
			}
			i++;
		}
        accumulated_time++;
		burst_time[j]--;
        for (auto k : burst_time) {
            cout<<k<<endl;
        }
		if (burst_time[j] == 0) {
			waiting_times.push_back(accumulated_time - burst_copy[j] - arrival_time[j]);
            arrival_time.erase(arrival_time.begin() + j);
			burst_copy.erase(burst_copy.begin() + j);
			burst_time.erase(burst_time.begin() + j);
            priority.erase(priority.begin() + j);

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
