# 🚁 Multi-Drone Search & Rescue System

### Graph-Based Path Planning and Priority-Based Task Allocation for Dynamic Disaster Response

---

## 📌 Project Overview

The **Multi-Drone Search & Rescue System** is a simulation-based project designed to improve the speed and efficiency of rescue operations during dynamic disaster situations.

During disasters, multiple rescue requests can occur at different locations while drones have limited battery, availability, and capabilities. Manually managing these missions and selecting suitable routes can be time-consuming.

This project focuses on coordinating multiple UAVs using **Data Structures in C** and **Object-Oriented Programming in C++**.

---

## 🎯 Problem Statement

In a disaster situation:

- Multiple rescue missions may arrive simultaneously.
- Missions can have different priorities.
- Drones have limited battery and availability.
- Some routes may be blocked or unavailable.
- A drone failure may require task reassignment.
- Selecting the most suitable drone and route manually can be inefficient.

The proposed system provides a structured approach for **mission prioritization, drone assignment, route planning, and dynamic reallocation**.

---

## 💡 Proposed Solution

The system divides the problem into two major parts:

### 1. Mission Allocation

Rescue missions are assigned priorities and managed using a **Priority Queue**, ensuring urgent missions are handled first.

### 2. Route Planning

The disaster area is represented as a **Graph using Adjacency Lists**. Graph algorithms such as **Dijkstra and BFS** are used to find suitable routes between locations.

The system also considers drone availability, battery level, distance, and mission requirements while assigning drones.

---

## 🧠 Data Structures & Algorithms

| Concept | Application |
|--------|-------------|
| Graphs | Represent disaster-affected areas |
| Adjacency Lists | Store connections between locations |
| Priority Queue | Manage rescue missions based on priority |
| Queue | Manage pending tasks |
| Searching | Find suitable drones and locations |
| Sorting | Rank drones and missions |
| Dijkstra Algorithm | Find shortest/suitable paths |
| BFS | Explore reachable/search zones |
| Arrays | Store and manage system data |

---

## 💻 OOP Concepts Used

The system is designed using C++ Object-Oriented Programming concepts:

- Classes and Objects
- Encapsulation
- Inheritance
- Polymorphism
- STL Containers
- File Handling

### Major Modules

- **UAV** – stores drone information such as battery, location and availability.
- **Mission** – represents rescue requests and their priorities.
- **SearchZone** – represents disaster-affected areas.
- **Route** – manages paths between locations.
- **Coordinator** – handles drone-to-mission assignment.
- **Simulation** – demonstrates the working of the complete system.

---

## ⚙️ System Workflow

```text
Mission Input
     +
Drone Data
     +
Map Data
     ↓
Task Manager
(Priority Queue)
     +
Route Planner
(Graph + Dijkstra/BFS)
     ↓
Coordination Engine
(Drone ↔ Mission Matching)
     ↓
Monitoring & Updates
(Battery / Failure / New Task)
     ↓
Output
(Assignment / Route / Status / Reallocation)
```

---

## 🔄 Dynamic Features

The system is designed to respond to changing conditions during a rescue operation.

Examples include:

- Low drone battery
- Drone failure
- Blocked route
- New high-priority mission
- Mission reassignment
- Change in drone location

When required, the system can re-evaluate the situation and assign another suitable drone or route.

---

## 🛠️ Technology Stack

- **C**
- **C++**
- **Data Structures**
- **Object-Oriented Programming**
- **STL**
- **Graph Algorithms**
- **Dijkstra Algorithm**
- **BFS**
- **Priority Queue**
- **Searching & Sorting**
- **File Handling**
- **Git & GitHub**

---

## 🎯 Project Objectives

1. Develop a simulation for coordinating multiple rescue drones.
2. Prioritize emergency missions efficiently.
3. Find suitable routes using graph algorithms.
4. Assign drones based on availability and constraints.
5. Demonstrate practical applications of Data Structures and OOP.
6. Handle dynamic situations such as drone failure and new emergency requests.

---

## 📊 Expected Outcome

The expected outcome is a practical simulation demonstrating:

- Efficient multi-drone coordination
- Priority-based mission allocation
- Graph-based route planning
- Suitable drone selection
- Dynamic task reassignment
- Practical implementation of DSA and OOP concepts

---

## 🚀 Future Scope

The system can be extended in the future with:

- Real-time drone telemetry
- GPS-based navigation
- Real disaster maps
- Live sensor data
- Advanced AI-based task allocation
- 3D path planning
- Drone simulation using ArduPilot SITL
- Real UAV hardware integration

---

## 👨‍💻 Project Information

**Project:** Multi-Drone Search & Rescue System  
**Domain:** AI / UAV Systems  
**Technologies:** C, C++, Data Structures & OOP

---

## 📚 References

- ArduPilot Documentation – Simulation and Mission Planning
- GeeksforGeeks – Dijkstra's Shortest Path Algorithm
- GeeksforGeeks – Priority Queue
- cppreference – C++ Classes and OOP
- sciencedirect – Articles relevant for the topic 

---

## ⭐ Project Goal

> To demonstrate how Data Structures and Object-Oriented Programming can be used to coordinate multiple drones efficiently during dynamic disaster response operations.

---

# Project Development Phases

## Phase-I: Project Proposal and Initial Design

Phase-I focused on identifying the problem, defining the project objectives, and preparing the initial design for the Multi-Drone Search & Rescue System.

### Work Completed
- Defined the problem of coordinating multiple UAVs during disaster-response situations.
- Finalized the project objectives and scope.
- Planned a weighted-graph representation for disaster locations and routes.
- Identified graph algorithms and priority-based mission scheduling as core concepts.
- Prepared the initial project proposal and documentation.

## Phase-II: System Design and Implementation

Phase-II focuses on developing the core C++ simulation and organizing the system into modules.

### Main Modules
- **Graph and Path Planning:** Weighted graph, BFS traversal/reachability, and Dijkstra's shortest-path algorithm.
- **Mission Management:** Priority-based scheduling of rescue missions.
- **UAV Management:** Tracking drone location, battery level, availability, and status.
- **Coordinator and Event Handling:** Connecting modules and planning mission reassignment for dynamic events.

### Current Development Focus
- Implementing and integrating the main modules.
- Checking mission priority and route feasibility.
- Testing scenarios involving battery constraints, UAV failure, and blocked routes.
- Maintaining source code and project documents in GitHub.

## Phase-III: Testing and Finalization

Phase-III will focus on completing remaining features, testing the integrated simulation, validating results, and preparing the final demonstration and report.

### Planned Work
- Complete and verify the remaining modules.
- Test route planning and mission allocation under different scenarios.
- Validate battery constraints, blocked routes, and UAV failure handling.
- Finalize documentation and prepare the project demonstration.

---

**Note:** Features described as planned or under development will be marked complete only after implementation and testing.
