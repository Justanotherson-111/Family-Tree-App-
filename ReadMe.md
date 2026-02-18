## 🌳 CayGiaPha (Family Tree App)

CayGiaPha is a desktop application for creating and visualizing family trees.
It allows users to manage people, relationships, and branches in a structured and interactive graphical view.

Built with C++, Qt6, and CMake.

---

## ✨ Features 

📌 Interactive family tree visualization

👤 Add, edit, and remove family members

👨‍👩‍👧 Manage relationships (parents, children, spouses)

🌿 Branch analysis tools

💾 Data import/export (CSV / JSON)

🖨️ Export family tree to PDF

🖱️ Context menus and inspector panel for editing

---

## 🧱 Tech Stack

C++17

Qt 6

Core

Widgets

PrintSupport

CMake ≥ 3.16

---

## 📂 Project Structure
`
.
├── app/        # Application bootstrap
├── core/       # Business logic, entities, rules, services
├── data/       # Persistence layer (CSV/JSON mapping, repository)
├── ui/         # Qt UI components and controllers
├── main.cpp
└── CMakeLists.txt
`
---

## ⚙️ Requirements

Make sure you have:

CMake ≥ 3.16

Qt6 (Core, Widgets, PrintSupport)

A C++17 compatible compiler

GCC / Clang / MSVC

---

## 🚀 Build Instructions
``
Linux / macOS
mkdir build
cd build
cmake ..
cmake --build .
``

Run:
``
./CayGiaPha
``
==Windows (Qt + MSVC or MinGW)==
``
mkdir build
cd build
cmake ..
cmake --build . --config Release
``

Run:
``
CayGiaPha.exe
``
**📦 Deployment (Windows)**

To deploy on Windows:

Build in Release mode

Use Qt's deployment tool:

windeployqt CayGiaPha.exe


This copies required Qt DLLs and plugins.

You can then package the folder or create an installer.

---

## 🛠️ Development Notes

CMake features enabled:

AUTOMOC

AUTOUIC

AUTORCC

Position-independent code

Compile commands export (for tooling)

Project config:

cmake_minimum_required(VERSION 3.16)
project(CayGiaPha VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

---

## 📌 Roadmap (Ideas)

Multi-page PDF export

Undo/Redo system

Theming support

Drag-and-drop tree editing

Cross-platform installers

---

## 🤝 Contributing

Contributions are welcome!

Fork the repo

Create a feature branch

Submit a pull request

---

## 👤 Author
Justanotherson-111


