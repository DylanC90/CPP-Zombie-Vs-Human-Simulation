# Zombie Apocalypse — 2D Predator-Prey Simulation
<img width="326" height="480" alt="image" src="https://github.com/user-attachments/assets/445f285c-e6c6-445a-a645-d637c8d6a8d7" />
<img width="408" height="401" alt="image" src="https://github.com/user-attachments/assets/a2bb7bb7-5daf-49a6-b61a-5a84fd5927ea" />

A modified predator-prey simulation set in a zombie apocalypse. Prey are **humans** and predators are **zombies**. These organisms live in a **20 x 20 grid of cells** (a city) and are represented using simple ASCII characters when the grid is printed.

| Symbol | Represents |
|--------|------------|
| `H`    | Human      |
| `Z`    | Zombie     |
| `-`    | Empty cell |
| `#`    | Building   |

---

## Rules of Simulation

### Humans

Humans behave according to the following rules, applied in order each time step:

**1. Move**
> For every time step, the humans randomly try to move (aka run screaming) up, down, left, or right. If the neighboring cell in the selected direction is occupied or would move the human out of the city (i.e., off the grid), then the human stays in the current cell.

**2. Recruit**
> If a human survives for three time-steps, at the end of the time step the human will recruit a new human into an adjacent empty space. This is simulated by creating a new human in an adjacent (up, down, left, or right — i.e., diagonal not allowed) cell that is empty. If there is no empty cell available, no recruiting occurs. Once a recruit is produced, a human cannot recruit again until it has survived three more steps. If humans are still alive and are unable to recruit (i.e., are surrounded by zombies and/or edges) their recruit counter should be reset to zero.

**3. Buildings**
>Humans can go inside Buildings to avoid being Eaten or Breed By a zombie, putting them in a "Safe" State
---

### Zombies

Zombies behave according to the following rules, applied in order each time step:

**1. Move / Eat**
> For every time step, the zombie will move to an adjacent cell (including diagonal) containing a human and eat the human. Note that a zombie will not eat another zombie (because they taste bad). If there are no humans, the zombie will simply move to an empty position.

**2. Breed**
> If a zombie survives for eight time-steps, and after it has moved/eaten, it will convert a randomly selected adjacent (including diagonal) human into a zombie (i.e., replace the human with a new zombie). If a zombie is still alive and is unable to convert, their breed counter should retain a state so that they will convert a human provided the very next opportunity (post move/eat).

**3. Starve**
> If the zombie has not eaten any humans within three time-steps, at the end of the third time step the virus will lose its hold and the zombie will convert to a human (i.e., replace the zombie with a new human).


Problem Provided by Professor David Russel at NSCC IT Programming within the Course of PROG2100: Programming C++
Loosely Based on: ‘Doodlebugs’, Savitch, Absolute C++, 3rd edition
