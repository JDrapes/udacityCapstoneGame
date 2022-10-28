# Info
Welcome to Jordan Draper's capstone game for the Udacity C++ nanodegree. This uses SDL2. Press WASD to move around - (W/S for elevators).
The game is simple you just move around and use the lifts. All files under src for ease of review.

# Dependencies
sudo apt-get install libsdl2-2.0-0 libsdl2-d* libsdl2-ttf-* libsdl2-image-*

## Build instructions

1. Clone this repo
2. Make a build directory in the top level directory: mkdir build && cd build
3. Compile: cmake .. && make
4. Run ./capstoneGame

# Marking ruberic

Things I implemented:
- A README with instructions is included with the project
- The README indicates which project is chosen.
- The README includes information about each rubric point addressed.
- The submission must compile and run.
- The project demonstrates an understanding of C++ functions and control structures. [src/game.h line 20 to line 32]
- The project reads data from a file and process the data, or the program writes data to a file. [src/game.cpp line 201 to line 232]
- The project accepts user input and processes the input.[src/game.cpp line 123 to line 169]
- The project uses Object Oriented Programming techniques. [src/game.cpp line 105 to line 106]
- Classes use appropriate access specifiers for class members. [src/entity.h whole file]
- Classes encapsulate behavior. [src/game.cpp line 171 to 175 can create draw any object with that function]
- Classes follow an appropriate inheritance hierarchy. [src/entity.h extends class object]
- The project makes use of references in function declarations. [src/entity.h lots of refs here]
- The project uses destructors appropriately. [src/game.cpp line 31 to line 40]
- The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate. [src/game.cpp line 4 to line 30 lots of things init when starting]



Things I chose to not implement:
- Derived class functions override virtual base class functions.
- Overloaded functions allow the same function to operate on different parameters.
- Class constructors utilize member initialization lists.
- Templates generalize functions in the project.
- The project follows the Rule of 5.
- The project uses smart pointers instead of raw pointers.
- The project uses multithreading.
- A promise and future is used in the project.
- A mutex or lock is used in the project.
- A condition variable is used in the project.
- The project uses move semantics to move data, instead of copying it, where possible. 
