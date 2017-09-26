# Knights-Tour
Programming project for solving the Knight's Tour Problem.

This program takes an NxN board to find a Closed Knight's Tour.

The value of boardSize can be modified to easily try this program out for
any given boardSize.  However, bear in mind that a closed tour may only be found
for any N >= 6 that is even.  Odd values and lesser values cannot complete a closed
tour.

This program utilizes recursive backtracking and Warnsdorff's Rule to find a
closed tour.  Warnsdorff's Rule takes an initial starting position and
searches for subsequent locations with the fewest moves, moving to them.  

We use this approach to get near a closed tour.  However, achieving a closed
tour is not guaranteed with Warndorff's Rule.  This is why we also employ 
recursive backtracking.  We move back steps taken in Warndorff's Rule until
we arrive at a position to finish a closed tour.

While this may increase complexity a bit, the backtracking usually only involves
the final steps of Warnsdorff's Rule, meaning that we don't have to backtrack far
to reach our closed tour. 
