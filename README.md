MANDATORY:

![Screenshot from 2024-12-25 16-08-49](https://github.com/user-attachments/assets/9af1bcae-b2aa-4959-b8d4-976f31de265b)

BONUS:

![Screenshot from 2024-12-25 16-14-10](https://github.com/user-attachments/assets/3cfd1484-5cee-468d-bad5-40c3f593d281)

__HOW_TO_PLAY__:

1. clone the game repo and the graphics library:<br>
   $: git clone "https://github.com/medidbella/cub3d.git"<br>
   $: cd cub3d && git clone "https://github.com/42Paris/minilibx-linux.git"<br>

2. compile and run:<br>
   $: make bonus<br>
   $: ./cub3d_bonus bonus_maps/maze.cub<br>
<br>
__CONTROLS__:<br>
<br>
WASD: move around.<br>
MOUSE / LEFT & RIGHT ARROWS: rotate the point of view.<br>
MOUSE LEFT CLICK: use the weapon.<br>
MOUSE SCROLL / Q: switch weapon.<br>
MOUSE RIGHT CLICK:  show/hide mouse cursor<br>
SPACE: open/close a door.<br>
<br>
__MORE MAPS__:<br>
<br>
instead of using the "maze.cub" map, you can use any of the provided maps in both the bonus_maps<br>
and the mandatory_maps directories, or even make your own map.<br>
<br>
__CREAT A VALID MAP__:<br>
<br>
you can make your map by following these rules:<br>
<br>
1. the map file should have '.cub' as the file extension<br>
<br>
2. specify the textures you want to use for each side in this format:<br>
  [SIDE] [PATH_TO TEXTURE] (the texture must be in XPM image format)<br>
  side can be: SO, WE, NO, and EA.<br>
  A good variety of wall textures are provided in the textures directory (colors/, doom/, ...).<br>
<br>
3. use this syntax to choose the ceiling and floor colors:<br>
  [F or C] [r,g,b] (F for floor and C for ceiling)<br>
  example: F 255,255,255 (this will set the floor to white color)<br>
<br>
4. chose the door texture (if the map will have a door):<br>
  same as choosing the wall texture :<br>
  DOOR [Path to door texture] (there are examples in the textures/doors/ directory).<br>
<br>
5. you can draw your map using this set of characters:<br>
  '1' for a wall, '0' for an empty space, 'N', 'S', 'W', and 'E' all can be used for the player<br>
    finally, the 'D' character can be used to represent doors.<br>
  the map free spaces, player, and doors must all be surrounded by walls ('1')<br>
  the doors ('D') character must be vertically/horizontally surrounded by walls   <br>
<br>
use the provided maps as examples <br>
