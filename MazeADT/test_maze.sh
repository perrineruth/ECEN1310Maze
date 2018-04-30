!# /bin/bash

# Run solveMaze through several test mazes.

run () {
  echo "$*"
  if $*
  then echo 'success'
  else echo 'error'
  fi
}
# Invalid tests.
# Invalid file name
echo 'Invalid file name'
run ./solveMaze <<EOF
doot doot doot
EOF

#Multiple start points.
echo 'multiple start points'
run ./solveMaze <<EOF
multiStart.txt
EOF

#Multiple end points.
echo 'Multiple end points'
run ./solveMaze <<EOF
multiEnd.txt
EOF

# Deal with no solution situations
echo 'Test no solution situations'
run ./solveMaze <<EOF
noSolution.txt
EOF


#Valid tests.
# Basic test maze
echo 'Basic maze test'
run ./solveMaze <<EOF
maze.txt
EOF

# Ability to avoid loop entrapment.
echo 'Test for loop entrapment'
run ./solveMaze <<EOF
hasLoop.txt
EOF

# Difficult maze with start point within maze.
echo 'Difficult maze with start point within maze'
run ./solveMaze <<EOF
mazeHard.txt
EOF

