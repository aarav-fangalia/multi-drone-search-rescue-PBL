#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include <map>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

// UAV CLASS

class UAV {
private:
    string id;
    int location;
    int battery;
    bool available;
    bool failed;

public:
    UAV(string id, int location, int battery)
        : id(id), location(location), battery(battery),
          available(true), failed(false) {}

    string getId() const { return id; }
    int getLocation() const { return location; }
    int getBattery() const { return battery; }
    bool isAvailable() const { return available; }
    bool isFailed() const { return failed; }

    void setAvailable(bool value) {
        available = value && !failed && battery > 20;
    }

    void reduceBattery(int amount) {
        battery = max(0, battery - amount);
        if (battery <= 20)
            available = false;
    }

    void setBattery(int value) {
        battery = max(0, min(100, value));
        if (battery <= 20 || failed)
            available = false;
    }

    void fail() {
        failed = true;
        available = false;
    }

    void setLocation(int newLocation) {
        location = newLocation;
    }

    void display() const {
        cout << "UAV-" << id
             << " | Location: " << location
             << " | Battery: " << battery << "%";

        if (failed)
            cout << " | FAILED";
        else if (battery <= 20)
            cout << " | LOW BATTERY";
        else if (available)
            cout << " | AVAILABLE";
        else
            cout << " | BUSY";

        cout << '\n';
    }
};

// MISSION CLASS

class Mission {
private:
    string id;
    int destination;
    int priority;
    string type;
    string status;
    string assignedUAV;

public:
    Mission(string id, int destination, int priority, string type)
        : id(id), destination(destination), priority(priority),
          type(type), status("Pending"), assignedUAV("None") {}

    string getId() const { return id; }
    int getDestination() const { return destination; }
    int getPriority() const { return priority; }
    string getType() const { return type; }
    string getStatus() const { return status; }
    string getAssignedUAV() const { return assignedUAV; }

    void assignUAV(const string& uav) {
        assignedUAV = uav;
        status = "Assigned";
    }

    void complete() {
        status = "Completed";
    }

    void resetToPending() {
        status = "Pending";
        assignedUAV = "None";
    }

    void display() const {
        cout << id
             << " | Destination: " << destination
             << " | Priority: " << priority
             << " | Type: " << type
             << " | Status: " << status
             << " | UAV: " << assignedUAV << '\n';
    }
};

// MISSION PRIORITY COMPARATOR

struct MissionComparator {
    bool operator()(Mission* a, Mission* b) const {
        if (a->getPriority() != b->getPriority())
            return a->getPriority() < b->getPriority();

        return a->getId() > b->getId();
    }
};

// GRAPH CLASS

class Graph {
private:
    int vertices;
    vector<vector<pair<int, int>>> adj;
    vector<vector<bool>> blocked;

public:
    Graph(int vertices) : vertices(vertices) {
        adj.resize(vertices + 1);
        blocked.resize(vertices + 1, vector<bool>(vertices + 1, false));
    }

    void addEdge(int u, int v, int weight) {
        if (u < 1 || u > vertices || v < 1 || v > vertices || weight < 0)
            return;

        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }

    bool blockRoute(int u, int v) {
        if (u < 1 || u > vertices || v < 1 || v > vertices)
            return false;

        bool edgeExists = false;
        for (const auto& edge : adj[u]) {
            if (edge.first == v) {
                edgeExists = true;
                break;
            }
        }

        if (!edgeExists)
            return false;

        blocked[u][v] = true;
        blocked[v][u] = true;

        cout << "\n[EVENT] Route " << u << " <-> " << v
             << " has been BLOCKED.\n";
        return true;
    }

    void displayGraph() const {
        cout << "\n========== DISASTER AREA GRAPH ==========\n";

        for (int i = 1; i <= vertices; i++) {
            cout << "Node " << i << " -> ";

            for (const auto& edge : adj[i]) {
                int next = edge.first;
                int weight = edge.second;

                cout << next << "(" << weight << ")";
                if (blocked[i][next])
                    cout << "[BLOCKED]";
                cout << "  ";
            }
            cout << '\n';
        }
    }

    bool BFS(int start, int destination) const {
        if (start < 1 || start > vertices ||
            destination < 1 || destination > vertices)
            return false;

        vector<bool> visited(vertices + 1, false);
        queue<int> q;

        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            if (current == destination)
                return true;

            for (const auto& edge : adj[current]) {
                int next = edge.first;

                if (!visited[next] && !blocked[current][next]) {
                    visited[next] = true;
                    q.push(next);
                }
            }
        }

        return false;
    }

    pair<int, vector<int>> dijkstra(int source, int destination) const {
        const int INF = numeric_limits<int>::max() / 4;

        if (source < 1 || source > vertices ||
            destination < 1 || destination > vertices)
            return {-1, {}};

        vector<int> distance(vertices + 1, INF);
        vector<int> parent(vertices + 1, -1);

        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;

        distance[source] = 0;
        pq.push({0, source});

        while (!pq.empty()) {
            int currentDistance = pq.top().first;
            int current = pq.top().second;
            pq.pop();

            if (currentDistance != distance[current])
                continue;

            for (const auto& edge : adj[current]) {
                int next = edge.first;
                int weight = edge.second;

                if (blocked[current][next])
                    continue;

                if (distance[current] + weight < distance[next]) {
                    distance[next] = distance[current] + weight;
                    parent[next] = current;
                    pq.push({distance[next], next});
                }
            }
        }

        if (distance[destination] == INF)
            return {-1, {}};

        vector<int> path;
        for (int current = destination; current != -1; current = parent[current])
            path.push_back(current);

        reverse(path.begin(), path.end());
        return {distance[destination], path};
    }
};

// COORDINATOR CLASS

class Coordinator {
private:
    Graph& graph;
    vector<UAV> uavs;
    vector<unique_ptr<Mission>> missions;
    priority_queue<Mission*, vector<Mission*>, MissionComparator> missionQueue;
    map<string, string> assignments;

    int findUAVIndex(const string& id) const {
        for (int i = 0; i < static_cast<int>(uavs.size()); i++) {
            if (uavs[i].getId() == id)
                return i;
        }
        return -1;
    }

    bool missionIdExists(const string& id) const {
        for (const auto& mission : missions) {
            if (mission->getId() == id)
                return true;
        }
        return false;
    }

    int findBestUAV(int destination) const {
        int bestIndex = -1;
        int bestCost = numeric_limits<int>::max();

        for (int i = 0; i < static_cast<int>(uavs.size()); i++) {
            const UAV& uav = uavs[i];

            if (!uav.isAvailable() || uav.isFailed() || uav.getBattery() <= 20)
                continue;

            auto route = graph.dijkstra(uav.getLocation(), destination);
            int routeCost = route.first;

            if (routeCost == -1)
                continue;

            int requiredBattery = routeCost * 10;
            if (uav.getBattery() < requiredBattery)
                continue;

            if (routeCost < bestCost) {
                bestCost = routeCost;
                bestIndex = i;
            }
        }

        return bestIndex;
    }

    void printPath(const vector<int>& path) const {
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i + 1 < path.size())
                cout << " -> ";
        }
    }

public:
    Coordinator(Graph& graph) : graph(graph) {}

    void addUAV(const UAV& uav) {
        uavs.push_back(uav);
    }

    void addMission(const string& id, int destination, int priority, const string& type) {
        if (missionIdExists(id)) {
            cout << "\nMission ID already exists. Please use a unique ID.\n";
            return;
        }

        missions.push_back(make_unique<Mission>(id, destination, priority, type));
        missionQueue.push(missions.back().get());

        cout << "\n[MISSION ADDED] " << id
             << " | Priority: " << priority << '\n';
    }

    void displayUAVs() const {
        cout << "\n========== UAV FLEET ==========\n";
        for (const auto& uav : uavs)
            uav.display();
    }

    void displayMissions() const {
        cout << "\n========== MISSIONS ==========\n";

        if (missions.empty()) {
            cout << "No missions have been added yet.\n";
            return;
        }

        for (const auto& mission : missions)
            mission->display();
    }

    void autoAssignPendingMissions() {
        // Process every currently pending mission, keeping those that cannot be assigned.
        vector<Mission*> pending;

        while (!missionQueue.empty()) {
            Mission* mission = missionQueue.top();
            missionQueue.pop();

            if (mission->getStatus() == "Pending")
                pending.push_back(mission);
        }

        sort(pending.begin(), pending.end(), [](Mission* a, Mission* b) {
            if (a->getPriority() != b->getPriority())
                return a->getPriority() > b->getPriority();
            return a->getId() < b->getId();
        });

        vector<Mission*> stillWaiting;

        for (Mission* mission : pending) {
            int uavIndex = findBestUAV(mission->getDestination());

            if (uavIndex == -1) {
                cout << "\n[PENDING] " << mission->getId()
                     << " | Priority: " << mission->getPriority()
                     << "\nReason: No suitable UAV currently available.\n";
                stillWaiting.push_back(mission);
                continue;
            }

            UAV& uav = uavs[uavIndex];
            auto route = graph.dijkstra(uav.getLocation(), mission->getDestination());

            if (route.first == -1) {
                stillWaiting.push_back(mission);
                continue;
            }

            int cost = route.first;
            int batteryUsed = cost * 10;

            cout << "\n----------------------------------------\n";
            cout << "[AUTO ALLOCATION]\n";
            cout << "Mission: " << mission->getId() << '\n';
            cout << "Priority: " << mission->getPriority() << '\n';
            cout << "Type: " << mission->getType() << '\n';
            cout << "Selected UAV: UAV-" << uav.getId() << '\n';
            cout << "Route: ";
            printPath(route.second);
            cout << "\nRoute Cost: " << cost << '\n';

            uav.reduceBattery(batteryUsed);
            uav.setAvailable(false);
            mission->assignUAV(uav.getId());
            assignments[mission->getId()] = uav.getId();

            cout << "Battery Used: " << batteryUsed << "%\n";
            cout << "Remaining Battery: " << uav.getBattery() << "%\n";
            cout << "[SUCCESS] Mission " << mission->getId()
                 << " assigned to UAV-" << uav.getId() << ".\n";
        }

        for (Mission* mission : stillWaiting)
            missionQueue.push(mission);
    }

    void processMissions() {
        cout << "\n========== AUTOMATIC MISSION ALLOCATION ==========\n";
        autoAssignPendingMissions();
    }

    void completeMission() {
        displayMissions();

        string missionID;
        cout << "\nEnter Mission ID to complete: ";
        cin >> missionID;

        for (auto& mission : missions) {
            if (mission->getId() != missionID)
                continue;

            if (mission->getStatus() != "Assigned") {
                cout << "\nMission is not currently assigned.\n";
                return;
            }

            string uavID = mission->getAssignedUAV();
            mission->complete();
            assignments.erase(missionID);

            int uavIndex = findUAVIndex(uavID);
            if (uavIndex != -1) {
                UAV& uav = uavs[uavIndex];

                // Update the simulated UAV position after completing the mission.
                uav.setLocation(mission->getDestination());

                if (!uav.isFailed() && uav.getBattery() > 20)
                    uav.setAvailable(true);
            }

            cout << "\n========== MISSION COMPLETED ==========\n";
            cout << "Mission: " << missionID << '\n';
            cout << "UAV-" << uavID << " status updated.\n";
            cout << "Checking pending missions...\n";
            autoAssignPendingMissions();
            return;
        }

        cout << "\nMission not found.\n";
    }

    void lowBatteryEvent() {
        displayUAVs();

        if (uavs.empty()) {
            cout << "No UAVs available in the fleet.\n";
            return;
        }

        int choice;
        cout << "\nSelect UAV number (1-" << uavs.size() << "): ";
        if (!(cin >> choice)) {
            handleInputError();
            return;
        }

        if (choice < 1 || choice > static_cast<int>(uavs.size())) {
            cout << "Invalid choice.\n";
            return;
        }

        int battery;
        cout << "Enter new battery level (0-100): ";
        if (!(cin >> battery)) {
            handleInputError();
            return;
        }

        if (battery < 0 || battery > 100) {
            cout << "Invalid battery value.\n";
            return;
        }

        uavs[choice - 1].setBattery(battery);
        cout << "\n[EVENT] UAV-" << uavs[choice - 1].getId()
             << " battery changed to " << battery << "%.\n";

        if (battery <= 20)
            cout << "[WARNING] UAV entered LOW BATTERY state.\n";

        autoAssignPendingMissions();
    }

    void failureEvent() {
        displayUAVs();

        if (uavs.empty()) {
            cout << "No UAVs available in the fleet.\n";
            return;
        }

        int choice;
        cout << "\nSelect UAV number to fail (1-" << uavs.size() << "): ";
        if (!(cin >> choice)) {
            handleInputError();
            return;
        }

        if (choice < 1 || choice > static_cast<int>(uavs.size())) {
            cout << "Invalid choice.\n";
            return;
        }

        string failedID = uavs[choice - 1].getId();
        uavs[choice - 1].fail();

        for (auto& mission : missions) {
            if (mission->getAssignedUAV() == failedID &&
                mission->getStatus() == "Assigned") {
                cout << "\n[ALERT] Mission " << mission->getId()
                     << " affected by UAV failure.\n";

                mission->resetToPending();
                assignments.erase(mission->getId());
                missionQueue.push(mission.get());

                cout << "[SYSTEM] Mission returned to priority queue.\n";
            }
        }

        cout << "\n[EVENT] UAV-" << failedID << " has FAILED.\n";
        autoAssignPendingMissions();
    }

    void blockRouteEvent() {
        cout << "\n========== AVAILABLE ROUTES ==========\n";
        cout << "1. 1 <-> 2\n";
        cout << "2. 1 <-> 3\n";
        cout << "3. 2 <-> 4\n";
        cout << "4. 3 <-> 4\n";
        cout << "5. 3 <-> 5\n";
        cout << "6. 4 <-> 5\n";
        cout << "7. 4 <-> 6\n";
        cout << "8. 5 <-> 6\n";

        int choice;
        cout << "\nEnter route to block: ";
        if (!(cin >> choice)) {
            handleInputError();
            return;
        }

        int u = -1, v = -1;

        switch (choice) {
            case 1: u = 1; v = 2; break;
            case 2: u = 1; v = 3; break;
            case 3: u = 2; v = 4; break;
            case 4: u = 3; v = 4; break;
            case 5: u = 3; v = 5; break;
            case 6: u = 4; v = 5; break;
            case 7: u = 4; v = 6; break;
            case 8: u = 5; v = 6; break;
            default:
                cout << "Invalid route.\n";
                return;
        }

        if (graph.blockRoute(u, v))
            cout << "[SYSTEM] Future route planning will ignore this edge.\n";
        else
            cout << "That route does not exist in the graph.\n";

        autoAssignPendingMissions();
    }

    void addUrgentMission() {
        string id, type;
        int destination;

        cout << "\nEnter urgent mission ID: ";
        cin >> id;

        cout << "Enter destination node (1-6): ";
        if (!(cin >> destination)) {
            handleInputError();
            return;
        }

        if (destination < 1 || destination > 6) {
            cout << "Invalid destination.\n";
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter mission type: ";
        getline(cin, type);

        addMission(id, destination, 5, type);
        cout << "\n[URGENT] Mission " << id
             << " inserted with Priority 5.\n";
        cout << "Checking UAV availability...\n";
        autoAssignPendingMissions();
    }

    void showShortestRoute() {
        int source, destination;

        cout << "\nEnter source node (1-6): ";
        if (!(cin >> source)) {
            handleInputError();
            return;
        }

        cout << "Enter destination node (1-6): ";
        if (!(cin >> destination)) {
            handleInputError();
            return;
        }

        if (source < 1 || source > 6 || destination < 1 || destination > 6) {
            cout << "Invalid nodes.\n";
            return;
        }

        if (!graph.BFS(source, destination)) {
            cout << "\nBFS: Destination is NOT reachable.\n";
            return;
        }

        cout << "\nBFS: Destination is reachable.\n";
        auto result = graph.dijkstra(source, destination);

        if (result.first == -1) {
            cout << "No route available.\n";
            return;
        }

        cout << "Dijkstra Shortest Path: ";
        printPath(result.second);
        cout << "\nTotal Cost: " << result.first << '\n';
    }

    static void handleInputError() {
        cout << "\nInvalid input. Please enter a number and try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void menu() {
        int choice = -1;

        do {
            cout << "\n\n========== DYNAMIC EVENT MENU ==========\n";
            cout << "1. Process Pending Missions\n";
            cout << "2. Simulate Low Battery\n";
            cout << "3. Simulate UAV Failure\n";
            cout << "4. Block a Route\n";
            cout << "5. Add Urgent Mission\n";
            cout << "6. Show Shortest Route\n";
            cout << "7. Show UAV Status\n";
            cout << "8. Show Mission Status\n";
            cout << "9. Show Graph\n";
            cout << "10. Complete Mission\n";
            cout << "0. Exit\n";
            cout << "========================================\n";
            cout << "Enter your choice: " << flush;

            if (!(cin >> choice)) {
                handleInputError();
                continue;
            }

            switch (choice) {
                case 1:
                    cout << "\n[MENU] Processing pending missions...\n";
                    processMissions();
                    break;
                case 2:
                    lowBatteryEvent();
                    break;
                case 3:
                    failureEvent();
                    break;
                case 4:
                    blockRouteEvent();
                    break;
                case 5:
                    addUrgentMission();
                    break;
                case 6:
                    showShortestRoute();
                    break;
                case 7:
                    cout << "\n[MENU] Showing UAV status...\n";
                    displayUAVs();
                    break;
                case 8:
                    cout << "\n[MENU] Showing mission status...\n";
                    displayMissions();
                    break;
                case 9:
                    cout << "\n[MENU] Showing graph...\n";
                    graph.displayGraph();
                    break;
                case 10:
                    completeMission();
                    break;
                case 0:
                    cout << "\nSystem shutting down..\n";
                    break;
                default:
                    cout << "\nInvalid choice. Please select 0-10!!\n";
            }
        } while (choice != 0);
    }
};

// MAIN FUNCTION

int main() {
    cout << "\n========== MULTI-DRONE SEARCH & RESCUE SYSTEM ==========\n";

    Graph graph(6);
    graph.addEdge(1, 2, 4);
    graph.addEdge(1, 3, 3);
    graph.addEdge(2, 4, 2);
    graph.addEdge(3, 4, 1);
    graph.addEdge(3, 5, 5);
    graph.addEdge(4, 5, 2);
    graph.addEdge(4, 6, 4);
    graph.addEdge(5, 6, 1);

    Coordinator coordinator(graph);

    coordinator.addUAV(UAV("A", 1, 100));
    coordinator.addUAV(UAV("B", 3, 90));
    coordinator.addUAV(UAV("C", 5, 85));
    coordinator.addUAV(UAV("D", 2, 95));
    coordinator.addUAV(UAV("E", 4, 80));
    coordinator.addUAV(UAV("F", 6, 90));
    coordinator.addUAV(UAV("G", 1, 75));
    coordinator.addUAV(UAV("H", 3, 70));
    coordinator.addUAV(UAV("I", 5, 95));
    coordinator.addUAV(UAV("J", 2, 85));
    coordinator.addUAV(UAV("K", 4, 65));
    coordinator.addUAV(UAV("L", 6, 80));

    graph.displayGraph();
    coordinator.displayUAVs();

    int numberOfMissions;
    cout << "\n========== MISSION INITIALIZATION ==========\n";
    cout << "Enter number of missions: " << flush;

    if (!(cin >> numberOfMissions)) {
        cout << "Invalid input. Please run the program again and enter a number.\n";
        return 1;
    }

    if (numberOfMissions < 1) {
        cout << "At least one mission is required.\n";
        return 0;
    }

    for (int i = 0; i < numberOfMissions; i++) {
        string id, type;
        int destination, priority;

        cout << "\nMission " << i + 1 << '\n';
        cout << "Enter Mission ID: ";
        cin >> id;

        cout << "Enter Destination Node (1-6): ";
        if (!(cin >> destination)) {
            cout << "Invalid input. Please restart and enter a numeric destination.\n";
            return 1;
        }

        if (destination < 1 || destination > 6) {
            cout << "Invalid destination. Please restart and enter nodes from 1 to 6.\n";
            return 1;
        }

        cout << "Enter Priority (1-5): ";
        if (!(cin >> priority)) {
            cout << "Invalid input. Please restart and enter a numeric priority.\n";
            return 1;
        }

        if (priority < 1 || priority > 5) {
            cout << "Priority must be between 1 and 5. Please restart the program.\n";
            return 1;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Mission Type: ";
        getline(cin, type);

        coordinator.addMission(id, destination, priority, type);
    }

    coordinator.displayMissions();

    cout << "\n========== INITIAL AUTO ALLOCATION ==========\n";
    coordinator.processMissions();

    coordinator.menu();
    return 0;
}
