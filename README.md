# cnc

cnc is a small wrapper program which sets some terminal settings such that your input will be character- rather than line-buffered, turns off terminal echoing, and then forwards your arguments to the real netcat program. The result is the ability to connect to services over the network to game-like services where line-buffering is not desired.
