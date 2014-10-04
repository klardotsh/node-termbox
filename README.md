node-termbox
============

> ## WARNING 04 Oct 2014: UNMAINTAINED
> There's a greater-than-zero chance these bindings are entirely useless against modern versions of Termbox, as I've had no projects using this providing motivation to update the bindings. PRs welcome, otherwise this repository is mostly kept around for historical purposes.
>
> -- Josh

Some simple bindings of [termbox](http://github.com/nsf/termbox) to
node.js. Not perfect at all, and I'm sure there's bugs somewhere, but
for a one-nighter it worked out pretty well. I seem to be able to do
anything I would need to (time will tell). Bug reports welcome.

FUNCTIONS
---------

    init() -> [Number]
    shutdown() -> [Number] -- Always 0
    width() -> [Number]
    height() -> [Number]
    clear() -> [Number] -- Always 0
    present() -> [Number] -- Always 0
    setCursor(x, y) [Number], [Number] -> [Number] -- Always 0
    hideCursor() -> [Number] -- Always 0
    changeCell(x, y, char, fg, bg) [Number], [Number], [String], [Number], [Number] -> [Number] -- Always 0
    selectInputMode(mode) [Number] -> [Number]
    setClearAttributes(fg, bg) [Number], [Number]
    peekEvent(timeout) [Number] (milliseconds) -> [Object] -- type, mod, key, ch, w, h
    pollEvent() -> [Object] -- type, mod, key, ch, w, h

CONSTANTS
---------

I'll spare you the detail of *every single one* of these, as it's a
massive list. I expose everything defined in termbox.h, so go to town.

LICENSE
-------

    Copyright (c) 2013 Josh Klar <j@iv597.com>
    
    Do whatever you want with this code as long as you leave this header.
    This code has no warranty. If shit hits the fan, it's your problem.

