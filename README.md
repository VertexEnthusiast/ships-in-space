# Ships in Space
'Ships in Space' is a Space Invaders-esque game written in C++, built on the SFML library. It relies largely on the SFML Graphics API for rendering of sprites, and has been extended in this project to support animations and UI construction.

## Demo


https://github.com/herbertiser/ships-in-space/assets/152287856/55dbdccc-7a2a-4b57-8a74-5ee5912dc613

## Prerequisites

- C++ compiler (e.g., g++)
- [SFML](https://www.sfml-dev.org/download.php) library

## Building the Project

1. Clone the repository:
    ```sh
    git clone https://github.com/herbertiser/ships-in-space.git
    ```

2. Set the environment variables (or edit the makefile comments directly) for the SFML include and library directories:
    ```sh
    export SFML_INCLUDE_DIR=/path/to/sfml/include
    export SFML_LIB_DIR=/path/to/sfml/lib
    ```

3. Build the project with `make`:
    ```sh
    make
    ```

## Running the Project

After building, you can run the executable:

    ./game

## Cleaning Up

To clean up build files:

    make clean





# License
This project is licensed under the MIT License.
