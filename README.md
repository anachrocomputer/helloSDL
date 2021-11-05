# helloSDL #

Rudimentary "Hello, world" program for SDL,
the Simple DirectMedia Layer library.

Displays a window containing an isometric grid,
and uses the keyboad arrow keys to move around it.
Also detects joystick(s) and reads input from them.

## SDL Tutorial ##

To write this program, I referred to *Beginning Game Programming v2.0*
at Lazy Foo' Productions:

[Lazy Foo' Productions - Beginning Game Programming v2.0](https://lazyfoo.net/tutorials/SDL/index.php)

In particular, Lesson 19 on Gamepads and Joysticks.

## Building the Program ##

Install the C compiler, linker and libraries.

`sudo apt-get install build-essential`

Install SDL libraries and the development package.

`sudo apt-get install libsdl2-2.0` <br />
`sudo apt-get install libsdl2-dev` <br />

Run 'make':

`make`
