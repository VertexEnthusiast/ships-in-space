# Ships in Space
'Ships in Space' is a Space Invaders-esque game written in C++, built on the SFML library. It relies largely on the SFML Graphics API for rendering of sprites, and has been extended in this project to support animations and UI construction.

## Demo

![Demo](https://github.com/herbertiser/ships-in-space/tree/main/assets/demo.mov)

## Building the Project

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/MyProject.git
    cd MyProject
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