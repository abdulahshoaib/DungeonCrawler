# DungeonCrawler - Design Architecture

This document outlines the SOLID design principles and design patterns used throughout the DungeonCrawler project to ensure maintainability, scalability, and clean code architecture.

---

## SOLID Design Principles

### 1. Single Responsibility Principle (SRP)

**Definition**: Each class should have one reason to change, meaning it should have only one job or responsibility.

**Implementation in DungeonCrawler**:

- **Character System** (`src/engine/characters/`)
  - `Character.h/cpp` - Handles base character properties and behavior
  - `Knight1.h/cpp, Knight2.h/cpp, Knight3.h/cpp` - Specific knight variants
  - `Samurai.h/cpp, SamuraiArcher.h/cpp, SamuraiCommander.h/cpp` - Samurai variants
  - `Skeleton_archer.h/cpp, Skeleton_spearman.h/cpp, skeleton_warrior.h/cpp` - Skeleton variants
  - `Karasu_tengu.h/cpp, Yamabushi_tengu.h/cpp` - Yokai variants

- **Entity Management** (`src/engine/core/`)
  - `Player.h/cpp` - Handles player-specific logic
  - `Enemy.h/cpp` - Base enemy logic
  - `EnemyManager.h/cpp` - Manages collection and lifecycle of enemies
  - `GameManager.h/cpp` - Oversees overall game state and progression
  - `Map.h/cpp` - Map data and collision handling
  - `Coin.h/cpp` - Collectible item logic

- **Systems** (`src/engine/system/`)
  - `Animator.h/cpp` - Animation state management
  - `Audio.h/cpp` - Sound and music handling
  - `GameProgress.h/cpp` - Game progress tracking
  - `Loader.h/cpp` - Asset and game data loading

- **UI Components** (`src/ui/ui_elements/`)
  - `Button.h/cpp` - Button behavior
  - `Label.h/cpp` - Text display
  - `Progressbar.h/cpp` - Progress visualization

**Benefits**: Each class can be tested and modified independently without affecting others.

---

### 2. Open/Closed Principle (OCP)

**Definition**: Software entities (classes, modules, functions) should be open for extension but closed for modification.

**Implementation in DungeonCrawler**:

- **Character Hierarchy** - New character types can be added by extending `Character` base class without modifying existing classes:
  ```cpp
  class Character { /* base implementation */ };
  class Knight1 : public Character { /* extension */ };
  class Samurai : public Character { /* extension */ };
  ```

- **Enemy System** - New enemy types extend `Enemy` without modifying the base:
  ```cpp
  class Enemy { /* base implementation */ };
  class EnemySkeleton : public Enemy { /* extension */ };
  class EnemyYokai : public Enemy { /* extension */ };
  ```

- **Game States** (`src/engine/state/`) - New game states extend `GameState`:
  ```cpp
  class GameState { /* base definition */ };
  class MainMenuState : public GameState { /* extension */ };
  class PlayState : public GameState { /* extension */ };
  class PauseState : public GameState { /* extension */ };
  ```

- **Menu System** - New menus extend `Menu` base class:
  ```cpp
  class Menu { /* base implementation */ };
  class MenuHUD : public Menu { /* extension */ };
  class MenuInventory : public Menu { /* extension */ };
  ```

**Benefits**: Adding new character types or game states doesn't require modifying existing code, reducing the risk of breaking functionality.

---

### 3. Liskov Substitution Principle (LSP)

**Definition**: Subclasses should be substitutable for their base classes without breaking the application.

**Implementation in DungeonCrawler**:

- **Character Subclasses** - All character types (Knight, Samurai, Skeleton, Yokai) can be used interchangeably where a `Character` is expected
- **Enemy Subclasses** - `EnemySkeleton` and `EnemyYokai` can be used wherever `Enemy` is expected
- **Game States** - Any game state (Menu, Play, Pause, Death, Load) can be used where `GameState` is expected
- **UI Elements** - Buttons, Labels, and Progressbars follow consistent behavior

**Example**:
```cpp
Enemy* enemy = new EnemySkeleton(...);  // or EnemyYokai(...)
enemy->update();                         // Works for both types
enemy->render();                         // Both implement correctly
```

**Benefits**: Polymorphism allows flexible code that works with different concrete implementations.

---

### 4. Interface Segregation Principle (ISP)

**Definition**: Clients should not be forced to depend on interfaces they don't use.

**Implementation in DungeonCrawler**:

- **Animation System** - `Animation.h` provides focused animation interface separate from character logic
- **Weapon System** - `weapons.h` defines weapon-specific interface independent of character
- **Enemy Path** - `EnemyPath.h` isolated path-following interface
- **UI Elements** - Each UI element (Button, Label, Progressbar) has focused responsibilities:
  - Button handles clicks
  - Label handles text rendering
  - Progressbar handles progress visualization

**Benefits**: Classes only implement methods they actually need, making the codebase cleaner and less bloated.

---

### 5. Dependency Inversion Principle (DIP)

**Definition**: High-level modules should not depend on low-level modules. Both should depend on abstractions.

**Implementation in DungeonCrawler**:

- **GameManager** (`src/engine/core/`) - Depends on abstract `Enemy` and `Player` classes, not concrete implementations
- **EnemyManager** - Works with abstract `Enemy` type rather than specific enemy subclasses
- **Engine** (`src/engine/`) - Depends on `GameState` abstraction for state management
- **Animator** - Works with `Animation` abstraction rather than specific animation types

**Example**:
```cpp
// HIGH-LEVEL: GameManager depends on abstraction
class GameManager {
    Enemy* enemies[MAX_ENEMIES];           // Abstract type
    Player* player;                        // Abstract type
};

// Not on concrete types like EnemySkeleton directly
```

**Benefits**: Changes to concrete implementations don't affect high-level game logic.

---

## Design Patterns

### 1. State Pattern

**Definition**: The State pattern allows an object to alter its behavior when its internal state changes. It appears to change its class without actually doing so.

**Location**: `src/engine/state/` directory

**Implementation**:
```
GameState (Abstract Base)
├── MainMenuState
├── PlayState
├── PauseState
├── DeathState
├── EndState
├── LoadingState
├── LoadGameState
├── NewGameState
├── EnterNameState
└── SettingsState
```

**How It Works**:
- The `Engine` class holds a current `GameState`
- The `GameState` abstract class defines the interface (update, render, input handling)
- Each concrete state implements specific behavior:
  - `MainMenuState` - Displays and handles main menu interactions
  - `PlayState` - Handles active gameplay
  - `PauseState` - Pauses the game and shows pause menu
  - `DeathState` - Handles player death sequence
  - `EndState` - Handles level/game completion

**Code Example**:
```cpp
// In Engine.h
class GameState { /* abstract base */ };
GameState* currentState;

// Transition between states
void Engine::changeState(GameState* newState) {
    if (currentState) delete currentState;
    currentState = newState;
}

// Game loop
void Engine::update() {
    currentState->update();
}
```

**Benefits**:
- Easy to add new game states without modifying existing ones
- Each state encapsulates its own logic
- Clean separation of concerns between different game phases
- Simplifies state transitions

---

### 2. Strategy Pattern

**Definition**: The Strategy pattern defines a family of algorithms, encapsulates each one, and makes them interchangeable. It lets the algorithm vary independently from clients that use it.

**Location**: `src/engine/characters/` directory

**Implementation**:

Each character type (Knight, Samurai, Skeleton, Yokai) represents a different strategy for:
- Combat behavior
- Movement patterns
- Animation sequences
- Special abilities

**Code Structure**:
```
Character (Base Strategy Interface)
├── Knight1
├── Knight2
├── Knight3
├── Samurai
├── SamuraiArcher
├── SamuraiCommander
├── Skeleton_archer
├── Skeleton_spearman
├── skeleton_warrior
├── Karasu_tengu
└── Yamabushi_tengu
```

**How It Works**:
Each character type has different implementations of:
- `attack()` - Different weapon styles and damage
- `move()` - Different movement speeds and patterns
- `takeDamage()` - Different armor/defense mechanics
- `update()` - Different animation and behavior logic

**Code Example**:
```cpp
// Base Strategy
class Character {
    virtual void attack() = 0;
    virtual void move() = 0;
    virtual void takeDamage(int damage) = 0;
};

// Concrete Strategies
class Knight1 : public Character {
    void attack() override { /* Sword attack with moderate speed */ }
    void move() override { /* Standard movement */ }
};

class SamuraiArcher : public Character {
    void attack() override { /* Bow attack from distance */ }
    void move() override { /* Fast movement */ }
};

// Usage - strategies are interchangeable
Character* fighter = new Knight1();  // or SamuraiArcher(), etc.
fighter->attack();
```

**Benefits**:
- Encapsulates different behavior variants
- Strategies can be swapped at runtime
- Eliminates complex conditional logic (no huge if-else chains)
- Easy to add new character types

---

### 3. Singleton Pattern

**Definition**: The Singleton pattern ensures that a class has only one instance and provides a global point of access to it.

**Location**: `src/engine/core/GameManager.h/cpp` and `src/engine/system/Audio.h/cpp`

**Implementation**:

While not explicitly documented with mutex or getInstance() patterns, these classes function as singletons:

- **GameManager** - Single instance managing all game state
- **Audio** - Single instance managing all audio playback
- **Engine** - Single instance running the game loop

**Code Example**:
```cpp
// GameManager - typically instantiated once in main
class GameManager {
private:
    static GameManager* instance;
    GameManager();  // private constructor
    
public:
    static GameManager* getInstance() {
        if (!instance) instance = new GameManager();
        return instance;
    }
    
    void updateGameState();
    void manageEnemies();
    void trackProgress();
};

// Usage
GameManager* manager = GameManager::getInstance();
manager->updateGameState();
```

**Benefits**:
- Ensures only one instance of critical systems exists
- Provides global access point without global variables
- Controls resource usage (memory, audio handles)
- Prevents multiple instances competing for resources

---

### 4. Template Method Pattern

**Definition**: The Template Method pattern defines the skeleton of an algorithm in a base class but lets subclasses override specific steps without changing the algorithm's structure.

**Location**: `src/engine/characters/Character.h/cpp` and state classes

**Implementation**:

The `Character` base class defines a template for character behavior that subclasses customize:

**Code Example**:
```cpp
// Base Template
class Character {
public:
    // Template Method - defines the algorithm skeleton
    void update() {
        updateAnimation();
        updatePosition();
        updateCollisions();
        updateState();
    }
    
    // Steps that subclasses override
    virtual void updateAnimation() = 0;
    virtual void updatePosition() = 0;
    virtual void updateCollisions() = 0;
    virtual void updateState() = 0;
};

// Concrete Implementation - Knight
class Knight1 : public Character {
    void updateAnimation() override { 
        // Knight-specific animation logic 
    }
    void updatePosition() override { 
        // Knight-specific movement logic 
    }
    void updateCollisions() override { 
        // Knight-specific collision handling 
    }
    void updateState() override { 
        // Knight-specific state changes 
    }
};

// Concrete Implementation - SamuraiArcher
class SamuraiArcher : public Character {
    void updateAnimation() override { 
        // Archer-specific animation logic 
    }
    void updatePosition() override { 
        // Archer-specific movement logic 
    }
    void updateCollisions() override { 
        // Archer-specific collision handling 
    }
    void updateState() override { 
        // Archer-specific state changes 
    }
};
```

**How It Works**:
1. Base class (`Character`) defines `update()` which calls a series of virtual methods
2. Each subclass (`Knight1`, `SamuraiArcher`, etc.) overrides only the steps it needs to customize
3. The overall algorithm structure remains the same - all characters follow the same update sequence
4. Subclasses cannot change the order of steps (e.g., animation always updates before position)

**Applied to GameStates**:
```cpp
// Template for all game states
class GameState {
public:
    void run() {
        handleInput();
        update();
        render();
    }
    
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
};

// Concrete states override specific steps
class PlayState : public GameState {
    void handleInput() override { /* Handle gameplay input */ }
    void update() override { /* Update gameplay logic */ }
    void render() override { /* Render game world */ }
};

class MainMenuState : public GameState {
    void handleInput() override { /* Handle menu input */ }
    void update() override { /* Update menu logic */ }
    void render() override { /* Render menu */ }
};
```

**Benefits**:
- Defines invariant parts of an algorithm once (in base class)
- Lets subclasses implement varying parts
- Promotes code reuse and consistency
- Ensures algorithm steps are executed in correct order
- Reduces code duplication

---

## Architecture Overview

```
Engine (Main Game Loop)
  ├── Current GameState (State Pattern)
  │    ├── PlayState
  │    │    ├── GameManager (Singleton)
  │    │    │    ├── Player (Character Strategy)
  │    │    │    ├── EnemyManager
  │    │    │    │    └── Enemies (Strategy Pattern)
  │    │    │    │         ├── EnemySkeleton
  │    │    │    │         └── EnemyYokai
  │    │    │    ├── Map
  │    │    │    └── GameProgress
  │    │    ├── Animator (Template Method)
  │    │    ├── Audio (Singleton)
  │    │    └── UI Menus (Composite, Template Method)
  │    │         └── UI Elements (Button, Label, Progressbar)
  │    └── Other States...
  └── Asset Loader (Singleton)
```

---

## Conclusion

The DungeonCrawler project leverages industry-standard design principles and patterns to create:
- **Maintainable** code through SOLID principles
- **Extensible** systems through inheritance and abstraction
- **Clean separation** of concerns
- **Reusable** components and algorithms
- **Testable** and debuggable codebase

These patterns and principles work together to make the codebase scalable and easier to modify as the project grows.
