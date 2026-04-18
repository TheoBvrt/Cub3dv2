# cub3D

*This project has been created as part of the 42 curriculum by <login>.*

## Description

cub3D is a graphical project based on the ray-casting technique used in early first-person games such as Wolfenstein 3D.

The goal of the project is to create a simple 3D representation of a maze from a first-person point of view using the miniLibX graphical library.

The player can move through the map, rotate the camera, and interact with the environment through keyboard controls. Different textures are displayed depending on the orientation of the wall, while the floor and ceiling are rendered with custom RGB colors.

This project focuses on:

* Ray-casting fundamentals
* Parsing and validating `.cub` configuration files
* Window and event management with miniLibX
* Texture loading and rendering
* Collision detection
* Memory management and error handling

---

## Features

* First-person 3D view using ray-casting
* WASD movement
* Left and right camera rotation
* Different wall textures for North, South, East, and West walls
* Floor and ceiling colors
* Map parsing from `.cub` files
* Validation for invalid maps and malformed configuration files
* Clean exit on `ESC` or window close
* Memory leak protection and error handling

---

## Controls

| Key   | Action        |
| ----- | ------------- |
| `W`   | Move forward  |
| `S`   | Move backward |
| `A`   | Move left     |
| `D`   | Move right    |
| `←`   | Rotate left   |
| `→`   | Rotate right  |
| `ESC` | Exit the game |

---

## Installation

Clone the repository:

```bash
git clone <repository_url>
cd cub3D
```

Compile the project:

```bash
make
```

Clean object files:

```bash
make clean
```

Remove object files and executable:

```bash
make fclean
```

Recompile everything:

```bash
make re
```

---

## Usage

Run the program with a valid `.cub` map file:

```bash
./cub3D maps/example.cub
```

Example of a valid map file:

```text
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100001
1000N1
100001
111111
```

---

## Project Structure

```text
cub3D/
├── Makefile
├── README.md
├── includes/
├── src/
├── textures/
├── maps/
├── libft/
└── minilibx/
```

---

## Parsing Rules

The `.cub` file must contain:

* Four texture paths:

  * `NO`
  * `SO`
  * `WE`
  * `EA`
* One floor color:

  * `F`
* One ceiling color:

  * `C`
* A valid closed map
* Exactly one player starting position:

  * `N`
  * `S`
  * `E`
  * `W`

The map can contain only:

* `0` for empty space
* `1` for wall
* `N`, `S`, `E`, `W` for player position
* Spaces where necessary

Invalid files must produce:

```text
Error
<explicit error message>
```

---

## Technical Overview

The rendering system is based on ray-casting.

For every vertical column of pixels on the screen, a ray is sent from the player's position into the map until it collides with a wall. The distance between the player and the wall is then used to determine the height of the wall slice to draw on the screen.

To avoid fish-eye distortion, perpendicular wall distance is used instead of raw ray distance.

y = \frac{h}{d}

Where:

* `h` is the projected wall height
* `d` is the perpendicular distance to the wall

The Digital Differential Analyzer (DDA) algorithm is used to step through the map grid efficiently until a wall is reached.

---

## Error Handling

The program handles:

* Invalid file extensions
* Missing textures
* Invalid texture paths
* Invalid RGB values
* Missing identifiers
* Multiple player positions
* Missing player position
* Open maps
* Invalid characters
* Memory allocation failures

All errors must exit cleanly without memory leaks.

---

## Resources

Documentation and references used during the project:

* miniLibX documentation
* Wolfenstein 3D for ray-casting inspiration
* John Carmack articles and interviews about rendering engines
* Lode's Computer Graphics Tutorial
* Permadi ray-casting tutorial
* 42 intra subject and peer discussions
* `man mlx`
* `man math`
* `man open`
* `man read`
* `man malloc`

### AI Usage

AI tools were used only for:

* Understanding ray-casting concepts
* Reviewing parsing strategies
* Generating testing ideas
* Identifying edge cases for invalid maps
* Improving README structure and documentation

All code, architecture, and debugging decisions were reviewed, tested, and understood before being integrated into the project.
