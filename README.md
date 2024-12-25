mandatory part:
![Screenshot from 2024-12-25 16-08-49](https://github.com/user-attachments/assets/9af1bcae-b2aa-4959-b8d4-976f31de265b)
bonus part:
![Screenshot from 2024-12-25 16-11-20](https://github.com/user-attachments/assets/49e38c0a-f5b4-4424-8df6-6b70dd9ecdab)
![Screenshot from 2024-12-25 16-14-10](https://github.com/user-attachments/assets/50ed854b-b794-4187-abac-58079caf9d97<<)

__HOW_TO_PLAY__:

1. clone the game repo and the griphics library:
   $: git clone https://github.com/medidbella/cub3d.git
   $: cd cub3d && git clone https://github.com/42Paris/minilibx-linux.git

2. compile and run:
   $: make bonus
   $: ./cub3d_bonus bonus_maps/maze.cub

__CONTROLS__:

WASD : move around.
MOUSE / LEFT & RIGHT ARROWs : rotate the point of view.
MOUSE LEFT CLICK : use the wepon.
MOUSE SCROLL / Q : switch weapon.
MOUSE RIGHT CLICK :  show / hide mouse cursur
SPACE : open / close a door.

__MORE MAPS__:

instead of using maze.cub you can use any of the provided maps in both of the bonus_maps
and the mandatory_maps , or make your own map .

__CREAT A VALID MAP__:

you can make your own map by following thies rules:

1.the map file should have '.cub' as the file extension

2.specify the textures you want to use for each side in this format :
  [SIDE] [PATH_TO TEXTURE] (the texture must be in xpm image format)
  side can be : SO, WE, NO and EA.
  there is a good variaty of wall textures provided in the textures directory (colors/, doom/, ...)

3.the use this syntax to chose the ceiling and floor colors:
  [F or C] [r,g,b] (F for floor and C for ceiling)
  example: F 255,255,255 (this will set the floor to white color)

4.chose the door texture (if the map will have a door):
  same as chosing the wall texture :
  DOOR [Path to door texture] (there are example is the textures/doors/ directory).

5. you can draw your map using this set of character:
  '1' for a wall, '0' for an empty space, 'N', 'S', 'W', and 'E' all can be used for the player
    and finaly the 'D' character can be used to represent doors.
  the map free spaces, player, and doors must all be surrounded by walls ('1')
  the doors ('D') character must be vertacly/horizonatly surrounded by walls   

use the provided maps as examples 
