# Hyper-Dimensional Brainfuck

Hyper-Dimensional Brainfuck is an infinite-dimensional version of the Brainfuck programming language. Instead of a tape, we have a "world."
Lines within the world are called "vectors," and act very much like the Brainfuck tape. You can switch
between vectors using the `^` and `V` commands.  

# Commands:  
`+` - increment value of current cell  
`-` - decrement value of current cell  
`>` - shift positively along current vector  
`<` - shift negatively along current vector  
`^` - switch to a vector, parallel to the next dimensional axis, that passes through the current cell  
`V` - switch to a vector, parallel to the previous dimension axis, that passes through the current cell  
`.` - print out contents of current cell  
`,` - replace contents of current cell with input from STDIN  
`[` - skip past matching `]` if current cell values zero  
`]` - return to matching `[`  

Debug Commands (enabled with `-d`):  
`#` - print out coordinates and value of current cell  
`?` - print out current coordinates

# Interdimensional Travel
The `^` and `V` commands do not change the current cell, but only the direction in which the pointer will travel. Note that `^V` and `V^` is useless code, because the cancel each other out. A good way to think about this is a simple array of nodes, storing the cell's values and coordinates. For example, the list at the start of a program may be `{(0)=0}` where the cell at position `0` is equal to `0`. At the end of the program, the list may be `{(0)=5,(0,1)=2,(1,1,1)=3,(1,5)=7, ...}`  

The `<` and `>` commands will actually switch to a different node in the array. For example, starting at coordinate `(0)`, `^>>>^^>>` will go to the cell at position `(0,3,0,2)`  

In our notation, `(0)` is the same coordinate as `(0,0,0,0)` or `(0,0,0,0,0,0,0,0,0,0,0)`
# Example:  
Let's say we're only considering a 2-dimensional plane of the world:


`[0,1][1,1]`  
`[0,0][1,0]` 

You start at `0,0`. To shift to `1,0`, you would use `>`. To switch to `1,1` from there, you would use `^>`. From there, to switch to `0,1`, you would just use `V<`, and to switch back to `0,0`, you use `^<`  

Now let's consider a three dimensional cube, specifically a 3x3x3 cube.  
To go from the bottom, left, front corner of the cube, i.e `(0,0,0)` to the top, right, back corner, i.e. `(2,2,2)` You would do the following: 

`>>^>>^>>`  

For a 4x4x4x4 tesseract:  
`>>>^>>>^>>>^>>>`
# Install:
    git clone https://github.com/Property404/hdbf
    cd hdbf
    make
    sudo make install
    # test
    hdbf ./examples/LostKingdom.bf

# Command Line Usage:
    hdbf somefile.hdbf //Run some file
    hdbf -o somefile.hdbf // Run optimized version of some file
    hdbf -b somefile.hdbf // Run some file as pure brainfuck
    hdbf -d somefile.hdbf // Run some file in debug mode
    hdbf -di "+++++++>^^+++#" // Run command in debug mode
    hdbf --help // Display help
