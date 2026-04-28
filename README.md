# Logic Gate Simulator

Choose language: [Українська](#українська) | [English](#english)

---

## Українська

### Опис проєкту
Розробка інтерактивного навчального середовища для візуального моделювання цифрових вузлів ЕОМ. Проєкт є десктопним застосунком для моделювання цифрової логіки, що поєднує конструктор схем та навчальні модулі.

### Основні характеристики
* Автор: SemiNophim
* Платформа: Desktop (Linux, Windows)
* Технології: C++, Qt6, CMake
* Дата старту: 25.04.2026

### Функціональні можливості
* Конструктор схем: вирівнювання за сіткою, розрахунок фізичних величин (струм, напруга, опір).
* Кастомні компоненти: створення власних модулів на базі існуючих схем для повторного використання.
* Користувацький досвід: підтримка скасування дій (Undo), копіювання/вставки, масштабування (Zoom) та візуалізація компонента перед розміщенням.
* Навчальний режим: покрокові уроки від базової фізики до архітектури АЛП.

### Технічні вимоги для збірки
* Компілятор C++ (GCC / Clang / MSVC)
* CMake 3.16+
* Qt6 SDK

---

## English

### Project Description
Development of an interactive educational environment for visual modeling of digital computer units. This desktop application is designed for digital logic simulation, combining a circuit constructor with educational modules.

### Key Specifications
* Author: SemiNophim
* Platform: Desktop (Linux, Windows)
* Technologies: C++, Qt6, CMake
* Start Date: April 25, 2026

### Functional Features
* Circuit Constructor: grid snapping, calculation of physical values (current, voltage, resistance).
* Custom Components: ability to create modular units based on existing circuits for reuse.
* User Experience: support for Undo (Ctrl+Z), Copy/Paste, Zoom, and ghost-component visualization before placement.
* Educational Mode: step-by-step lessons ranging from basic physics to ALU architecture.

### Build Requirements
* C++ Compiler (GCC / Clang / MSVC)
* CMake 3.16+
* Qt6 SDK

### Installation
1. Clone the repository:
   git clone https://github.com/SemiNophim/LogicGateSimulator.git
2. Build the project:
   mkdir build && cd build
   cmake ..
   make
