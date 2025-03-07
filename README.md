# Monster Hunter World Inspired OOP Project

## Overview
This project is a console-based application inspired by *Monster Hunter World*, built using Object-Oriented Programming (OOP) principles in C++. The application simulates the management of a hunter's inventory, including weapons, armor, and hunted monsters.

## Features
- Manage a **Hunter's** inventory, including weapons, armor, and hunted monsters.
- Create, update, and manage **Weapons** with elemental attributes and attack bonuses.
- Design and customize **Armor** with different defense bonuses.
- Generate **Monsters** with unique appearances, elemental weaknesses, and attack strengths.
- Customize **Hunter Appearances** with gender, hair color, eye color, and face shape.
- Interactive **menu system** for CRUD operations (Create, Read, Update, Delete).
- Overloaded **operators** for mathematical and logical operations between objects.

## Classes
### 1. `Weapon`
   - Attributes:
     - `base_atk` (float) - Base attack power
     - `name` (string) - Weapon name
     - `atk_bonus` (float*) - Attack bonuses per combo
     - `maxCombo` (int) - Maximum number of combos
     - `element` (string) - Element type
     - `elemental_bonus` (float) - Additional elemental attack bonus
     - `equipped` (bool) - Whether the weapon is equipped
   - Features:
     - **Operator Overloading:** `+`, `*`, `<=`, `==`, `[]`
     - **Constructor Types:** Default, parameterized, copy
     - **Getters & Setters**

### 2. `Armour`
   - Attributes:
     - `name` (string) - Armour name
     - `def` (double) - Base defense
     - `bonus_def[5]` (int array) - Defense against elements
     - `equipped` (bool) - Whether the armor is equipped
   - Features:
     - **Operator Overloading:** `+`, `*`, `>=`, `==`, `[]`
     - **Constructor Types:** Default, parameterized, copy
     - **Getters & Setters**

### 3. `Hunter`
   - Attributes:
     - `playerId` (const int) - Unique ID
     - `online` (bool) - Online status
     - `username` (char*) - Player's name
     - `level` (unsigned int) - Hunter's level
     - `weapons` (Weapon*) - List of weapons
     - `armours` (Armour*) - List of armors
     - `hunted_monsters` (int*) - List of hunted monsters
     - `appearence` (Hunter_Appearence) - Hunter's visual details
   - Features:
     - **Operator Overloading:** `+`, `*`, `>`, `==`, `[]`
     - **Getters & Setters**
     - **CRUD Operations in the menu**

### 4. `Monster`
   - Attributes:
     - `monster_id` (const int) - Unique ID
     - `name` (string) - Monster's name
     - `zone` (char) - Habitat zone
     - `hp` (int) - Monster's health
     - `atk` (float) - Monster's attack power
     - `elemental_weakness` (string) - Weakness type
     - `appearence` (Monster_Appearence) - Monster's visual details
   - Features:
     - **Operator Overloading:** `+`, `*`, `>`, `==`
     - **Getters & Setters**

## Functionalities
- **CRUD Operations**:
  - Create, update, delete hunters, weapons, armor, and monsters.
  - Display all stored data.
- **Operator Overloading**:
  - Weapons and armors can be combined.
  - Hunters can merge inventories.
- **Dynamic Memory Management**:
  - Used for storing weapons, armor, and monsters.
- **Interactive Menu**:
  - Allows users to navigate and interact with the system.

