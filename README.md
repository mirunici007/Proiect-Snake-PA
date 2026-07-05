# Snake Game

A robust, modular, and state-driven implementation of the classic Snake game, developed in C as a practical project for the *Design of Algorithms* course at the Faculty of Automatic Control and Computers.

## Project Context

Our objective was to move beyond the traditional "Snake" tutorial approach and build a robust, interactive application that addresses real-world software engineering challenges. The focus was placed on structured code, efficient resource management in C, and the implementation of a predictable, state-driven application logic.

## Technical Approach & Implementation

Rather than relying on a single large file, we prioritized a modular design to ensure the code remains maintainable, testable, and scalable.

### Finite State Machine (FSM)

The core of the application is a Finite State Machine. We treated the game as a series of distinct states (**Start, Menu, Gameplay, Pause, Quiz, Game Over**). This architectural choice allowed us to:

* **Decouple** the game logic from the UI rendering.
* **Prevent** conflicting user inputs across different application screens.
* **Manage** audio playback based on the specific state of the application.

### Modular Architecture

To keep the codebase clean, we separated responsibilities into distinct modules:

* **Central Controller (`game.c`):** Manages the orchestration between entities and validates state transitions.
* **Entity Logic (`snake.c`, `food.c`):** Implements grid-based movement and collision algorithms, ensuring the game remains deterministic and avoids floating-point inaccuracies.
* **Educational Module (`question.c`):** A distinct system that intercepts the gameplay loop to trigger a quiz interface, validating user input and providing immediate audio-visual feedback.
* **Interface Layer (`menu.c`, `input.c`):** Centralizes the handling of user interactions (keyboard/mouse), ensuring the rendering logic remains independent of the underlying mechanics.


## Key Features

* **Gameplay Modes:** Supports both "Classic" rules (wall collisions terminate the game) and "Wrap Mode" (border teleportation for continuous play).
* **Integrated Educational System:** A built-in quiz system that tests the user's knowledge during gameplay, offering a unique blend of arcade fun and academic assessment.
* **Resource & Memory Management:** Given the constraints of the C language, we implemented rigorous resource handling. Textures, audio streams, and window resources are initialized and released using a lifecycle-aware cleanup process to prevent memory leaks.
* **Customization:** The application includes support for dynamic theme swapping and a comprehensive audio engine that manages background music and sound effects (SFX) per game state.


## Project Structure

| Module | Role |
| --- | --- |
| `main.c` | Defines the application lifecycle (Initialization -> Main Loop -> Cleanup). |
| `game.c` | Controls gameplay mechanics, scoring and FSM transitions. |
| `snake.c` | Snake entity logic: movement paths, segment growth and self-collision. |
| `food.c` | Handles random spawn algorithms and invalid-spawn validation. |
| `question.c` | Manages the educational quiz data and user interaction feedback. |
| `menu.c` | Renders all UI screens (Menus, Settings, Credits). |
| `input.c` | Maps raw hardware input to application-level events. |


## Installation & Build

### Prerequisites

* **Compiler:** GCC or Clang
* **Build System:** Make
* **Library:** `raylib` (ensure the development headers are installed on your system).

### Execution

1. **Build:** Use the provided Makefile to compile all modules:
```bash
make game

```


2. **Run:** Execute the compiled binary:
```bash
./game

```


3. **Cleanup:** Remove build artifacts:
```bash
make clean

```




## 👥 Authors & Recognition

This project represents the collective work of our team at the **Faculty of Automatic Control and Computers**, overseen by **Conf. Dr. Ing. Dan Mihail Caramihai**.

**Team Members:**

* Sardaru Andreea-Miruna
* Paraschiv Georgiana-Simona
* Dumitrescu Laura
* Flores-Botezatu Edyra-Alexia
* Mitea Roberta-Elena

> **Note:** This project is intended for educational purposes. We believe this modular approach serves as a helpful reference for other students learning to manage complexity in C-based graphical applications.