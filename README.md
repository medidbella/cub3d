MANDATORY:

![Screenshot from 2024-12-25 16-08-49](https://github.com/user-attachments/assets/9af1bcae-b2aa-4959-b8d4-976f31de265b)

BONUS:

![Screenshot from 2024-12-25 16-14-10](https://github.com/user-attachments/assets/3cfd1484-5cee-468d-bad5-40c3f593d281)

__HOW_TO_PLAY__:

1. clone the game repo and the graphics library:
   $: git clone https://github.com/medidbella/cub3d.git
   $: cd cub3d && git clone https://github.com/42Paris/minilibx-linux.git

2. compile and run:
   $: make bonus
   $: ./cub3d_bonus bonus_maps/maze.cub

__CONTROLS__:

WASD: move around.
MOUSE / LEFT & RIGHT ARROWS: rotate the point of view.
MOUSE LEFT CLICK: use the weapon.
MOUSE SCROLL / Q: switch weapon.
MOUSE RIGHT CLICK:  show/hide mouse cursor
SPACE: open/close a door.

__MORE MAPS__:

instead of using the "maze.cub" map, you can use any of the provided maps in both the bonus_maps
and the mandatory_maps directories, or even make your own map.

__CREAT A VALID MAP__:

you can make your map by following these rules:

1. the map file should have '.cub' as the file extension

2. specify the textures you want to use for each side in this format :
  [SIDE] [PATH_TO TEXTURE] (the texture must be in XPM image format)
  side can be: SO, WE, NO, and EA.
  A good variety of wall textures are provided in the textures directory (colors/, doom/, ...).

3. use this syntax to choose the ceiling and floor colors:
  [F or C] [r,g,b] (F for floor and C for ceiling)
  example: F 255,255,255 (this will set the floor to white color)

4. chose the door texture (if the map will have a door):
  same as choosing the wall texture :
  DOOR [Path to door texture] (there are example is the textures/doors/ directory).

5. you can draw your map using this set of characters:
  '1' for a wall, '0' for an empty space, 'N', 'S', 'W', and 'E' all can be used for the player
    finally, the 'D' character can be used to represent doors.
  the map free spaces, player, and doors must all be surrounded by walls ('1')
  the doors ('D') character must be vertically/horizontally surrounded by walls   

use the provided maps as examples 
