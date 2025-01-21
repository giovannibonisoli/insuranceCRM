# Insurance Customer Relationships Management (ICMR)

## Overview
**Insurance Customer Relationships Management (ICRM)** is a C++ program designed to manage customer relationships in an insurance business. This software provides functionalities to handle client data and utilities for managing related operations.

### Features
- Costumer data management: add, edit and delete a costumer.
- Visualize all the costumers and search them.
- Insert, visualize and search interactions for each costumer.

---

## File Structure
The project is organized as follows:
- **main.cpp**: The main entry point of the program.
- **clients.cpp**: Handles customer-related functionalities.
- **clients.h**: Header file for `clients.cpp`.
- **utils.cpp**: Provides utility functions for various operations.
- **utils.h**: Header file for `utils.cpp`.

---

## Compilation Instructions
To compile the program, use the following commands based on your operating system:

### Windows
Open a terminal or command prompt and run:
```bash
g++ main.cpp utils.cpp clients.cpp -o my_program
```

### Linux
Open a terminal and run:
```bash
g++ main.cpp utils.cpp clients.cpp -o my_program
```

### macOS
Open a terminal and run:
```bash
g++ main.cpp utils.cpp clients.cpp -o my_program
```

---

## Running the Program
After successful compilation, an executable file named `my_program` will be generated. Use the following command to run the program:

### Windows
```bash
my_program.exe
```

### Linux / macOS
```bash
./my_program
```

---

## Prerequisites
- Ensure you have **g++** installed on your system.
  - On Linux, you can install it using:
    ```bash
    sudo apt-get install g++
    ```
  - On macOS, use Homebrew:
    ```bash
    brew install gcc
    ```
  - For Windows, install **MinGW** or a similar toolchain.

---

## License
This project is open-source and available under the MIT License.

---

Enjoy managing your insurance customer relationships with ease!

---

If you’d like further customization or additional sections, let me know!
