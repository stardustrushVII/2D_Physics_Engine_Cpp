A 2D physics engine that emulates classic Sonic the Hedgehog games. Here, I'll explain what everything does inside the root directory.
The "src" folder holds all the .cpp files used for operation.

input.cpp is the logic file that holds everything related to input. It handles key up, key down and pauseState using void processPlayerInput.

pause.cpp handles pause logic in-engine at runtime. Pause freezes logic update ticks until unpaused. Uses SDL_ttf to draw "Paused" on-screen.

physics.cpp handles everything related to player movement, jumping and deltaTime calculations, wall collisions and friction are currently TODOs.

player.cpp handles player character rendering and it's own collision detection with the engine world state.

resolution_selector.cpp handles the resolution selection menu called at the start of runtime using dynamic memory allocstion via std::vector. The Stardust Engine supports resolutions from 480p up to 4K with bespoke ultrawide 1440p support also included!

tilemap.cpp handles world rendering in 32x32 tilemaps. There are also test slopes included.

main.cpp is the executable. Takes everything from each respective .cpp via their .h file and runs it together. main doesn't really do anything on its own except having its own scrolling camera logic (which I should probably refactor into its own file).

The "include" folder houses all the .cpp files declarations through their .h files that share the same names as their .cpp files. 

The "build" folder has has the Unix executable files that are the compiled code as applications.

The "RUNFROMINHERE" inside "build" is where you should actually run the applications from because the compiled code relies on assets/Roboto.ttf for in-engine text rendering. The assets folder lives in here for easy launching.
