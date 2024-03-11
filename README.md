# ZeldaCPP
The Legend of Zelda: CPP Edition
This repository is part of a Programming Assignment for the Advanced Programming Course.

## Setup
1. Clone this project inside an OpenFrameworks installation's "apps/myApps/" directory
2. Build & Run the project

## Submitting Assignment
To submit this assignment, create a Release with the branch that holds all the changes you have added. If no Release is made, the last commit to the master branch will be graded.
Don't forget that you must also fill out an evaluation form in Moodle to consider the project submitted.

## Grading

(802-21-8814) (Yaniel Varela Soler) (Yaniel.varela@upr.edu)
(843-20-2952) (Nelson S. Escalona Ortiz) (nelson.escalona@upr.edu)

Any project that doesn't compile will receive a 0.

If a partner has no commits in the repositories, they'll will receive a 0.

## Student Notes
If you have any bonus specs, bonus or any details the TA's should know, you should include it here:

What are the extra specs/bonuses we created? Here they are:

1)  Ohhh fearsome hero, there are 2 unexplored dungeons scattered around the Overworld that beg to be explored.
    - In the Fire Dungeon, you should find the mighty Magma Potion, which enhances your sword and doubles
      the damage enemies take. It also changes the appearance of the sword.
    - In the Cold Hidden Dungeon, full of enemies, you should find the rarest weapon of them all.
      Some people call it DragonScale.

2)  There's a new enemy lurking around the rocky/deserted part of the map. BEWARE!!! He's able to track you down
    and has a fearsome damage like no other :O.

3)  You may have noticed during your fight with the new enemy, there seems to be a shield protected by a guard.
    They say that, in order to be worthy, you should defeat this new dangerous enemy; once defeated, the guard
    should grant passage for the shield.

4)  There is no doubt you should require some healing during your journey. In some parts of the map, there
    should be a meat-looking item. Give it a go to see what happens :D

Summary:

1)  Added a Magic Staff in the new Dungeon that kills enemies with 1 attack (In the Hidden Dungeon).
2)  Added an Additional Fire Dungeon on the extra Door.
3)  Added a Power Potion that increments Link's attack by 2 toward enemies (In the Fire Dungeon).
4)  Added a Shield that halves the damage that Link receives, but you must kill the boss first to take it.
    This shield also changes Link's movement animation to the one where he carries the big shield.
5)  Added a healing item around the map that grants 2 health.
6)  Link is able to carry multiple weapons at the same time.

Recursion Spec:

For the recursion spec, we created a superclass named ArrowDirection and 4 subclasses, one for 
each direction. The Recursion spec is in the onCollision method of each subclass which is called
when Link collides with the tiles. Each subclass is located in the Static folder inside the Entity folder. 
