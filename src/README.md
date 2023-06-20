# 765X 2023-2024 VEX Season

Lead Programmer: Eshaan Barkataki

Features: 

* Simulation for Odometery: defined in odom/OdomSim.h
    * without the need to have an entire coding drivebase (although this would be really helpful), you could use the simulated version to test your PID loop functions or what not
    
    * Definitely not a full-blown vehicle simulator (that would be insane), but it replicates arcade drive somewhat (with acceleration and decelleration)

    * Very deterministic simulation! Defined in `odom/OdomSim.hpp`

* Custom ODOM (**Not tested**):
    * Just a custom odometry 
    * idk not tested yet and probably will change the entire process entirely
    * *Need physical hardware to test, like a prog codebase*
    * Easily switch between Custom Odom or Okapi's Odom (in case the other one fails lol VEX 2022-2023)

* Bigger Console: using LVGL as a text display/interface we could basically create our own console
    * Defined in `display/Console.h`
    * could store **12** lines of useful information with more text per line 
    * Also, for overflow text it would automatically scroll horizontally instead of clipping out

* Auton selector using LVGL + risky/nonrisky step
