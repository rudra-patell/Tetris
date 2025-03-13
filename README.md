# 🎮 Tetris Game (C++ Console Edition)

Welcome to **Tetris**, a console-based implementation of the classic block-stacking game, built using **C++** and Windows console utilities. Developed by **Team Falcons**, this project brings back the nostalgia of Tetris with customizable gameplay, developer mode, and smooth performance—all within the Windows terminal.

---

## 🚀 Features

✅ **Classic Tetris Mechanics** – Stack falling tetrominoes, clear lines, and chase the high score.  
✅ **Customizable Grid** – Adjust the grid size (between `10x10` and `60x30`) for a tailored experience.  
✅ **Dynamic Difficulty** – Choose from *Easy, Normal,* or *Hard*, with adaptive difficulty scaling.  
✅ **Developer Mode** – Edit the grid in real time, tweak scores, and test mechanics.  
✅ **Score Tracking** – High scores are saved and updated in `userdata.txt`.  
✅ **Console Graphics** – Uses ASCII characters with Windows console colors for a retro feel.  
✅ **Pause Menu** – Pause, resume, or exit the game with ease.  

---

## ⚙️ Prerequisites

📌 **Operating System**: Windows (requires Windows Console APIs).  
📌 **C++ Compiler**: MSVC (Visual Studio) or MinGW (g++).  
📌 **Libraries**: No external dependencies; uses C++ Standard Library and `windows.h`.

---

## 🛠️ Installation & Running the Game

1️⃣ **Clone the repository**  
```bash
git clone https://github.com/rudra-patell/Tetris.git
cd Tetris
```

2️⃣ **Compile the code**  
```bash
g++ main.cpp Game.cpp Tetris.cpp -o tetris.exe
```

3️⃣ **Run the game**  
```bash
./tetris.exe
```

---
##  Controls

| Action           | Key |
|-----------------|----|
| Move Left       | ←  (Left Arrow) |
| Move Right      | →  (Right Arrow) |
| Rotate         | ↑  (Up Arrow) |
| Soft Drop       | ↓  (Down Arrow) |
| Hard Drop       | `Spacebar` |
| Pause / Resume | `ESC` |
| Quit Game       | `Q` |
---

## 🏆 Score & Difficulty Scaling

- Score increases as you clear lines.
- Higher difficulty levels unlock as you progress:
  - **Easy** → **Normal** → **Hard** → **Extreme** (based on score milestones).
- Highest score is saved in `userdata.txt`.
---

## 🔧 Developer Mode (For Debugging & Testing)

- **Enable Developer Mode** from the main menu.
- Modify the grid in real time.
- Manually adjust scores and difficulty levels.
- Unlock hidden high-difficulty settings.
---
## | Scope of Future Developments
- Made in **Modular format** for easier development
- This code is Heavily windows dependent we can add support for other platforms with cross-platform libraries like `ncurses` and `PDCurses`.

---

## | Acknowledgments

- **Developed by Team Falcons**  

- Special thanks to **Stack Overflow** and **GeeksforGeeks** for inspiration on console manipulation techniques.

---

## [ Team Members ]
| Name           | Roll Number | Group |
|---------------|------------|-------|
| **Rudra Patel** | [202404028](mailto:202404028@daiict.ac.in) | G6 (Leader) |
| **Pranav Patel** | 202404051 | G6 |
| **Devanshi Modi** | 202401498 | G6 |
| **Deep Sutariya** | 202401219 | G4 |

