# Hyper-Dimensional Brainfuck

Hyper-Dimensional Brainfuck is an infite-dimensional version of the Brainfuck programming language. Instead of a tape, we have a "world."
Rays parallel to the axis of each dimension in the world are called "vectors," and act very much like the Brainfuck tape. You can switch
between vectors using the `^` and `V` commands.  

# Commands:  
`+` - increase current cell  
`-` - decrease current cell  
`>` - shift positively along current vector  
`<` - shift negatively along current vector  
`^` - switch to a vector parallel to the next dimensional axis, that pass through the current cell  
`V` - switch to a vector parallel to the previous dimension axis, that pass through the current cell  
`.` - print out contents of current cell  
`,` - input from STDIN  
`[` - skip to matching `]` if cell values zero  
`]` - return to matching `[`  

# Example:  
Let's say we're only considering a 2-dimensional plane of the world  


`[0,1][1,1]`  
`[0,0][1,0]` 

You start at `0,0`. To shift to `1,0`, you would use `>`. To switch to `1,1` from there, you would use `^>`. From there, to switch to `0,1`, you would just use `V<`, and to switch back to `0,0`, you use `^<`  

Now Let's consider a three dimensional cube, specifically a 3x3x3 cube.  
To go from the bottom, left, front corner of the cube, i.e `(0,0,0)` to the top, right, back corner, i.e. `(2,2,2)` You would do the following: 

`>>^>>^>>`  

For a 4x4x4x4 tesseract:  
`>>>^>>>^>>>^>>>`
