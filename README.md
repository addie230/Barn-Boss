# 🌾 BarnBoss

A text-based farm management game built in C++ as a course project for Object-Oriented Programming at the Faculty of Mathematics and Informatics, Sofia University, 2025/2026.

---

## About

You run a farm. Plant seeds, raise animals, sell produce, and complete delivery tasks to earn score and money. Three roles exist — **Player**, **MarketManager**, and **TaskManager** — each with their own responsibilities.

The game auto-saves on exit and restores the saved state on the next start.

---

## OOP Concepts

The project applies the core concepts covered in the OOP course:

**Abstract classes and inheritance** — `User` is an abstract base class with a pure virtual `getType()`. `Player`, `MarketManager`, and `TaskManager` inherit from it. Similarly, `FarmEntity` is abstract, with `Plant` and `Animal` as concrete subclasses.

**Polymorphism** — `GameEngine` uses `dynamic_cast` to dispatch commands to the correct role at runtime. Virtual methods like `profileInfo()` behave differently depending on the actual type of the user.

**Modern C++ resource management** — the project relies on STL containers and `std::unique_ptr` for ownership management. No manual memory management with `new` or `delete` is used.

**RAII** — dynamically allocated objects such as `User` and `FarmEntity` instances are owned by `std::unique_ptr`. Resources are acquired and released automatically.

**Encapsulation** — internal state is hidden behind class interfaces, while helper functions such as `harvestReadyEntities` and command-parsing utilities remain private to their translation units through anonymous namespaces.

---

## Architecture

The project is organized into focused, single-responsibility classes:

- **`GameEngine`** — the main loop. Reads commands, dispatches to the correct handler, manages save/load on startup and exit.
- **`UserManager`** — holds all registered users, handles registration and login.
- **`Player`** — owns a `Barn` and a `Farm`, tracks balance, score, and cycles.
- **`Farm`** — manages cropland and farmland, advances plant and animal growth each cycle.
- **`Market`** — holds all products with quantities and prices.
- **`TaskBoard`** — holds delivery tasks and handles adding/removing tasks.
- **`Scoreboard`** — sorts and displays all players by score, then balance, then registration order.
- **`SaveManager`** — serializes and deserializes the full game state to a text file.

---

## Save System

On every `exit`, the full game state is written to `save.txt` — market prices and quantities, all tasks, and every user's balance, score, cycles, barn inventory, and farm contents including the growth progress of each plant and animal.

On startup, the file is parsed section by section. Each section is validated — if a value is out of range, a count does not match, or a required line is missing, loading fails cleanly and the game starts fresh without crashing.

---

## Roles

| Role | What they do |
|---|---|
| `Player` | Farms, trades, completes tasks |
| `MarketManager` | Restocks products, adjusts prices |
| `TaskManager` | Adds and removes delivery tasks |

Only one `MarketManager` and one `TaskManager` can exist at a time.

---

## Player Commands

### Info Commands

| Command | Description |
|---|---|
| `profileInfo` | Show your stats |
| `checkBalance` | Show current balance |
| `checkScore` | Show current score |
| `checkBarn` | Show barn inventory |
| `checkFarm` | Show cropland and farmland |
| `openMarketCatalog` | Browse the market |
| `showTaskBoard` | See active tasks |
| `showScoreboard` | See the leaderboard |
| `harvest` | Collect ready crops and animals |

### Action Commands

| Command | Description |
|---|---|
| `buyItem <id> <qty>` | Buy from the market |
| `sellItem <id> <qty>` | Sell from your barn |
| `sowPlant <1\|2>` | Plant wheat (1) or corn (2) |
| `addAnimal <3\|4>` | Add chicken (3) or cow (4) |
| `expandCropland` | Expand cropland capacity |
| `expandFarmland` | Expand farmland capacity |
| `completeTask <id>` | Complete a delivery task |

---

## Products

| ID | Product | Default Price |
|---|---|---|
| 1 | Wheat Seed | 10 |
| 2 | Corn Seed | 15 |
| 3 | Chicken | 25 |
| 4 | Cow | 50 |
| 5 | Wheat | 15 |
| 6 | Corn | 20 |
| 7 | Egg | 30 |
| 8 | Milk | 60 |

---

## Growth

| Entity | Cycles to mature | Produces |
|---|---|---|
| Wheat | 3 | Wheat |
| Corn | 4 | Corn |
| Chicken | 3 | Egg |
| Cow | 5 | Milk |

---

## MarketManager Commands

| Command | Description |
|---|---|
| `openMarketCatalog` | Browse the market |
| `restock <id> <qty>` | Add stock to a product |
| `changePrice <id> <price>` | Set a new price |

---

## TaskManager Commands

| Command | Description |
|---|---|
| `showTasks` | List all active tasks |
| `addTask <product> <qty> <balanceReward> <scoreReward>` | Add a delivery task |
| `removeTask <id>` | Remove a task |

---

## Universal Commands

| Command | Description |
|---|---|
| `register <username> <password> <role>` | Create an account |
| `login <username> <password>` | Log in |
| `logout` | Log out |
| `changePassword <old> <new>` | Change your password |
| `exit` | Save and quit |
