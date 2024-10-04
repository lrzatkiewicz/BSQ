# BSQ - Biggest Square Finder

## Project Overview

The **BSQ** project is a C program that reads a 2D map from a file and finds the largest possible square that can fit on the map, avoiding obstacles. The map is composed of characters representing empty spaces, obstacles, and the full square. The program dynamically allocates memory and uses a custom algorithm to find the largest square efficiently.

## Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Map File Format](#map-file-format)
- [Error Handling](#error-handling)
- [Development Notes](#development-notes)
- [Contributing](#contributing)
- [License](#license)

## Features

- Reads 2D maps from a file.
- Finds and displays the largest square that fits without overlapping obstacles.
- Validates maps for consistent row lengths and valid characters.
- Uses dynamic memory allocation via `malloc`.
- Handles multiple maps as input parameters.
- Efficient algorithm to compute the largest square.

## Requirements

- macOS, Linux, or any POSIX-compatible system.
- GCC or Clang compiler.
- `make` utility for compilation.
- Tested on macOS 15.0 (Sonoma).

## Installation

1. Clone this repository:

   ```bash
   git clone https://github.com/yourusername/bsq.git
2. Navigate to the project directory:
3. Compile the project using make:
4. The executable will be created in the root of the project directory as bsq.

## Usage
The program takes one or more map files as input.

Example:
./bsq maps/map1.txt maps/map2.txt
If the program successfully finds the largest square in the map, it will print the modified map with the square marked. If any validation errors occur, they will be printed to the standard output.

## Map File Format
The first line of the map file contains metadata:
The number of rows in the map.
Three characters:
Empty: Represents empty spaces.
Obstacle: Represents obstacles.
Full: Used to fill the largest square.

Example:
   ```
   9.oX
   .........
   ...o.....
   .........
   .........
   .....o...
   .........
   .o.......
   .........
   .........
```

The rest of the file contains the map grid, with each row being the same length.

## Error Handling
The program handles the following errors:

Invalid map format.
Inconsistent row lengths.
Invalid characters in the map.
Memory allocation failure.
If an error is detected, an appropriate error message will be printed, and the program will exit gracefully.

## Development Notes
The program uses dynamic memory allocation for flexibility in handling different map sizes.
A custom algorithm is used to efficiently find the largest square by checking each point on the map and determining if a square can fit.

## Contributing
If you'd like to contribute to this project:

Fork the repository.
Create a new branch (git checkout -b feature-branch).
Make your changes.
Push to the branch (git push origin feature-branch).
Open a Pull Request.

## License
This project is licensed under the MIT License - see the LICENSE file for details.
