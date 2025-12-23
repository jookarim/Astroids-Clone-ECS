
# Astroids-Clone-ECS
Astroids clone ECS with SDL2 and ImGui.
=======
# ECS Assignment – Entity Management with SDL2 & ImGui

This project is an implementation of an **Entity Component System (ECS)** built from scratch in **C++**, using **SDL2** for windowing and input, and **ImGui** for debugging and editor UI.

The goal of this project is to demonstrate a clear understanding of **ECS architecture**, **entity lifecycle management**, and **editor tooling**, without relying on any provided source code.

---

## Features

- Custom **ECS architecture**
  - Lightweight Entity Class that holds all components in a tuple
  - Decoupled Components (data-only)
  - Systems operating on component sets

- **Entity Management**
  - Create and destroy entities at runtime
  - Safe entity removal without breaking systems
  - Optional entity ID reuse

- **ImGui Editor**
  - Control / delete entities
  - Inspect entity components and values
  - Simple inspector-style UI

- **Scene Management**
  - Multiple scenes implemented within the same project
  - Scene switching and lifecycle handling

## Game Controls

The game uses a simple keyboard-based control scheme designed for clarity and testing ECS behavior.

- **Movement**

  - Move Forward: W key or Up Arrow

  - Move Backward: S key or Down Arrow

  - Rotate Clockwise: E key or Right Arrow

  - Rotate Counter-Clockwise: Q key or Left Arrow

- **Actions**

  - Shoot: Space

  - Mute / Unmute Audio: M key

- **Debug & Editor**

  - Toggle ImGui Debug UI: G key

- Built with:
  - **C++**
  - **SDL2**
  - **ImGui**
  - **CMake**

---

## Architecture Overview

### Entity
A lightweight class used to group components.  
Entities contain Components (Not fully Data orianted ECS)

### Component
Plain data-only structures attached to entities, representing specific aspects such as position, physics, or behavior.

### System
Logic that operates on entities by processing specific sets of components.  
Systems do not own entities; they only work on relevant component data.

---

## Scene Management Design Choice

Scenes are implemented within the same project but **do not use ECS**.

ECS is used for **gameplay logic and data-driven entities**, while scenes such as menus or transitions are kept simple and managed without ECS.

---

## Build & Run

### Requirements
- C++ compiler supporting **C++17 or newer**
- **SDL2**
- **ImGui**
- **CMake**

### Build Steps
```bash
git clone <repository-url>
cd <repository-folder>
cmake -S . -B build
cmake --build build