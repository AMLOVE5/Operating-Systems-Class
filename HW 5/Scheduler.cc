#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>

struct Process { 
    int id, arrival, burst, priority; // input fields
    int remaining, completion; // computed fields
    Process(int id_, int arrival_, int burst_, int priority_) // constructor
        : id(id_), arrival(arrival_), burst(burst_), priority(priority_),
          remaining(burst_), completion(0) {}
};

struct Results {
    double avgTurnaround, avgWaiting, throughput; // output metrics
};

Results computeMetrics(const std::vector<Process>& processes) {
    int n = static_cast<int>(processes.size()); // number of processes
    double totalTT = 0.0, totalWT = 0.0; // total turnaround and waiting times
    int firstArrival = processes[0].arrival, lastCompletion = 0; // track times
    for (const Process& p : processes) { // compute turnaround and waiting times
        int tt = p.completion - p.arrival;
        totalTT += tt;
        totalWT += tt - p.burst;
        if (p.arrival < firstArrival)   firstArrival   = p.arrival;
        if (p.completion > lastCompletion) lastCompletion = p.completion;
    }
    Results r = { totalTT / n, totalWT / n, // throughput = total processes / total time
                  static_cast<double>(n) / (lastCompletion - firstArrival) };
    return r;
}

void printResults(const Results& r) { // print metrics with 3 decimal places
    std::cout << std::fixed << std::setprecision(3)
              << "Average Turnaround Time: " << r.avgTurnaround << "\n"
              << "Average Waiting Time: "    << r.avgWaiting    << "\n"
              << "Throughput: "              << r.throughput    << "\n";
}

void runFCFS(std::vector<Process> processes) { // sort by arrival time, then by ID for tie-breaking
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival != b.arrival ? a.arrival < b.arrival : a.id < b.id;
    });
    int currentTime = 0;
    for (Process& p : processes) { // if process arrives after current time, move current time to arrival
        if (currentTime < p.arrival) currentTime = p.arrival;
        p.completion = currentTime + p.burst;
        currentTime  = p.completion;
    }
    std::cout << "--- FCFS ---\n"; // as per  example output format
    printResults(computeMetrics(processes));
    std::cout << "\n";
}

void runSJFP(std::vector<Process> processes) { //  always run the arrived process with shortest remaining time
    for (Process& p : processes) p.remaining = p.burst;
    int n = static_cast<int>(processes.size());
    int done = 0, time = 0;
    while (done < n) {
        int best = -1;
        for (int i = 0; i < n; i++) { // find arrived unfinished process with shortest remaining time
            if (processes[i].arrival > time || processes[i].remaining <= 0) continue;
            if (best == -1 || processes[i].remaining < processes[best].remaining)
                best = i;
        }
        if (best == -1) { time++; continue; } // cpu idle no process has arrived yet
        processes[best].remaining--;
        if (processes[best].remaining == 0) { // process finished
            processes[best].completion = time + 1;
            done++;
        }
        time++;
    }
    std::cout << "--- SJFP ---\n";
    printResults(computeMetrics(processes));
    std::cout << "\n";
}

void runPriority(std::vector<Process> processes) { // always run the arrived process with highest priority (lowest number)
    for (Process& p : processes) p.remaining = p.burst;
    int n = static_cast<int>(processes.size());
    int done = 0, time = 0;
    while (done < n) {
        int best = -1;
        for (int i = 0; i < n; i++) { // find arrived, unfinished process with highest priority
            if (processes[i].arrival > time || processes[i].remaining <= 0) continue;
            if (best == -1 || processes[i].priority < processes[best].priority)
                best = i;
        }
        if (best == -1) { time++; continue; } // cpu idle, no process has arrived yet
        processes[best].remaining--;
        if (processes[best].remaining == 0) { // process finished
            processes[best].completion = time + 1;
            done++;
        }
        time++;
    }
    std::cout << "--- Priority ---\n";
    printResults(computeMetrics(processes));
    std::cout << "\n";
}

int main(int, char* argv[]) { // read processes from CSV
    std::ifstream infile(argv[1]);
    std::vector<Process> processes;
    std::string line;
    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string token;
        int id, arrival, burst, priority;

        std::getline(ss, token, ','); id = std::stoi(token);
        std::getline(ss, token, ','); arrival = std::stoi(token);
        std::getline(ss, token, ','); burst = std::stoi(token);
        std::getline(ss, token, ','); priority = std::stoi(token);

        processes.emplace_back(id, arrival, burst, priority);
    }
    runFCFS(processes);
    runSJFP(processes);
    runPriority(processes);
    return 0;
}