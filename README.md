# 🚁 Multi-Drone Search & Rescue System

### Intelligent Drone Coordination for Disaster Response Using Data Structures and Algorithms

---

## 📌 Project Overview

The **Multi-Drone Search & Rescue System** is a simulation-based software project designed to coordinate multiple drones during emergency and disaster-response operations.

In a large-scale disaster, rescue requests may originate from multiple locations at the same time. Each drone has limited battery capacity, availability, and operational range, making manual assignment of drones and routes inefficient.

This project develops a centralized coordination system that prioritizes rescue missions, selects suitable drones, and determines efficient routes through a simulated disaster environment.

The system demonstrates the practical application of **Data Structures, Algorithms, and Object-Oriented Programming in C++** to solve a real-world coordination problem.

---

## 🎯 Problem Statement

During a disaster-response operation:

- Multiple rescue requests may be generated simultaneously.
- Different rescue requests may have different levels of urgency.
- Drones have limited battery capacity and availability.
- Drones may be located at different points in the disaster area.
- Certain routes may require longer travel distances.
- A drone may become unavailable during an operation.
- New emergency missions may arrive while existing missions are being processed.

A system is therefore required to efficiently **prioritize missions, select appropriate drones, calculate routes, and dynamically update assignments**.

---

## 💡 Proposed Solution

The proposed system uses a **Drone Coordination Engine** that connects mission management, drone management, and route planning.

The system follows four major stages:

### 1. Mission Prioritization

Each rescue mission is assigned a priority based on its urgency.

A **Priority Queue** is used to ensure that high-priority missions are considered before lower-priority missions.

### 2. Drone Selection

Available drones are evaluated using factors such as:

- Current location
- Battery level
- Availability
- Distance from the mission
- Mission requirements

The most suitable available drone is selected for the mission.

### 3. Route Planning

The disaster environment is represented as a **weighted graph**, where:

- Nodes represent locations or zones.
- Edges represent possible routes.
- Edge weights represent travel distance or cost.

**BFS** and **Dijkstra's Algorithm** are used for different route-planning requirements.

### 4. Dynamic Coordination

The system continuously updates the operational state.

For example:

- A drone may run low on battery.
- A route may become unavailable.
- A new high-priority mission may arrive.
- An assigned drone may become unavailable.

The coordinator can then reconsider the assignment and select another suitable drone.

---

## 🧠 Data Structures & Algorithms

| Concept | Application |
|---|---|
| Arrays | Store and manage drone and mission information |
| Structures / Classes | Represent system entities |
| Queue | Manage sequential operations |
| Priority Queue | Process missions according to urgency |
| Graph | Represent the disaster environment |
| Adjacency List | Store connections between locations |
| BFS | Explore reachable locations |
| Dijkstra's Algorithm | Calculate shortest weighted routes |
| Searching | Locate drones, missions and zones |
| Sorting | Rank drones or missions |
| File Handling | Store and retrieve system data |

---

## 💻 Object-Oriented Programming

The project is designed using C++ OOP principles.

### Core Concepts

- Classes and Objects
- Encapsulation
- Constructors
- Inheritance
- Polymorphism
- Abstraction
- STL Containers
- File Handling

### Major Components

**Drone**  
Maintains drone identity, location, battery level and operational status.

**Mission**  
Represents a rescue request with location, priority and status.

**RescueMap**  
Represents the disaster environment and connections between locations.

**RoutePlanner**  
Calculates suitable routes using graph algorithms.

**Coordinator**  
Connects drones and missions and manages assignments.

**Simulation**  
Demonstrates the complete system through a sequence of rescue operations.

---

## ⚙️ System Workflow

```text
        DRONE DATA
            +
       MISSION DATA
            +
         MAP DATA
            ↓
    ┌─────────────────┐
    │ Mission Manager │
    │  Priority Queue │
    └────────┬────────┘
             ↓
    ┌─────────────────┐
    │ Drone Selection │
    │ Availability    │
    │ Battery / Range │
    └────────┬────────┘
             ↓
    ┌─────────────────┐
    │ Route Planner   │
    │ Graph + BFS     │
    │ + Dijkstra      │
    └────────┬────────┘
             ↓
    ┌─────────────────┐
    │   Coordinator   │
    │ Drone ↔ Mission │
    └────────┬────────┘
             ↓
    ┌─────────────────┐
    │ Status Update   │
    │ Battery / Route │
    │ New Missions    │
    └────────┬────────┘
             ↓
          OUTPUT
