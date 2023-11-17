#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
/**
  *main - program entry point
  *Return: 0
  *The following code will help you to...
  *...Calcute the Average waiting time...
  *...Using the Round Robin Scheduling Algorithm (non-preemptive mode)
  */
int main() {
	int i = 0, index = 0, j = 0, processes_count = 0,
    accumulated_time = 0, arrival = 0, burst = 0, k, quantum = 0, remaining_burst = 0;
    float total = 0.0;
	vector<int> arrival_time, burst_time, waiting_times, burst_copy;

	cout<<"Howdy!!!"<<endl;
	cout<<"* This program helps you to compute the average waiting time of a number of processes ..."<<endl;
	cout<<" ... in a Round Robin 'non-preemptive' mode."<<endl;
	cout<<"* You will Enter the quantum time. Then, the arrival time and burst time of each process."<<endl;
	cout<<"*/!\\Time is in milliseconds."<<endl<<endl;

    cout<<"Enter the quantum time: ";
    cin>>quantum;
	while (true) {
		cout<<"Enter arrival time (Enter -1 to quit): ";
		cin>>arrival;
		
		if (arrival == -1)
			break;
		else if (arrival < 0) {
			cout<<"Invalid input."<<endl;
			return 0;
		}
        index = arrival_time.size();
        if (arrival_time.size() > 0) {
            j = arrival_time.size() - 1;
            while (j >= 0) {
                if(arrival < arrival_time[j]) {
                    index = j;
                }else {
                    break;
                }
                j--;
            }
        }

		cout<<"Enter burst time: ";
		cin>>burst;
		if (burst < 0) {
			cout<<"Invalid input."<<endl;
			return 0;
		}
		
        if (arrival_time.size() == 0 || index == arrival_time.size()) {
		    arrival_time.push_back(arrival);
            burst_time.push_back(burst);
        }else {
            arrival_time.insert(arrival_time.begin() + index, arrival);
            burst_time.insert(burst_time.begin() + index, burst);
        }
	}

    int first = arrival_time[0];

    for(int y = 0; y < arrival_time.size(); y++) {
        arrival_time[y] -= first;    
	}

    if (burst_time[0] == 0) {
        cout<<"The burst time of the first process can't be zero.";
        return 0;
    }  

	processes_count = arrival_time.size();
    vector<int> last_exec(processes_count);
    burst_copy = burst_time;
	
  //  while(true) {
        while(true) {
            k = (i + 1)%processes_count;
            while (true) {
                if ((arrival_time[k] <= accumulated_time) && (burst_time[k] > 0) && ((((last_exec[k] < last_exec[i]) || (last_exec[k] < arrival_time[i])) && (burst_copy[k] != burst_time[k])) || (k == i))) {
                    if((burst_time[k] <= quantum)) {
                        accumulated_time += burst_time[k];
                        last_exec[k] = accumulated_time;
                        waiting_times.push_back(accumulated_time - arrival_time[k] - burst_copy[k]);
                        burst_time[k] = 0;
                    }else {
                        accumulated_time += quantum;
                        burst_time[k] -= quantum;
                        last_exec[k] = accumulated_time;
                    }
                }
                k = (k + 1)%processes_count;
                if (k == ((i + 1)%processes_count)) {
                    break;
                }           
            }
        i = (i + 1)%processes_count;
        remaining_burst = 0;
        for (auto t : burst_time) {
            remaining_burst += t;
        }
        if (remaining_burst <= 0) {
            break;
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

