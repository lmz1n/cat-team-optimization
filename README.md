# Cat Team Optimization
A C program that uses recursion and backtracking to generate every possible arrangement of cats into teams and determine the grouping with the highest overall score.
Each cat has five trait scores and belongs to a breed. Teams are evaluated based on base scores, high-performing traits, team synergy, breed diversity, positional bonuses, and rivalries.

# Features
- Reads cat and rivalry data from an input file.
- Dynamically allocates memory for cat names, breeds, rival data, permutations, and team tracking.
- Generates all possible permutations of the available cats.
- Uses recursion and backtracking to explore possible team groupings.
- Calculates scores for individual teams.
- Applies bonuses and penalties based on team composition.
- Tracks the highest-scoring overall grouping.
- Identifies the highest-scoring individual team within the optimal grouping.
- Properly frees dynamically allocated memory before the program terminates.

# Input Format
The program receives its data through standard input.

The first line contains:

- Number of Teams  Cats per Team

The total number of cats must equal:

- Number of Teams × Cats per Team

Each following line contains information about one cat:

- Name Breed Trait1 Trait2 Trait3 Trait4 Trait5

Each cat has five numerical trait scores. The program calculates the cat's base score by adding all five traits together.

After the cat data, the input contains the number of rival pairs:

- Number of Rivalries

Each rivalry is then listed as:

- CatName1 CatName2

# Example Input
The input file used for this example is:

_3 3_

_Coco Ragdoll 85 90 75 80 88_

Polter Ragdoll 70 85 92 78 81

Hana DSH 95 72 80 91 77

Leo Tux 88 12 71 83 79

Fudge DSH 76 81 89 92 84

Pieces DSH 82 77 86 79 93

Caesar Siamese 47 82 15 63 91

Percy DSH 28 54 76 39 12

Pikachu DSH 58 23 87 41 69

1
Coco Polter

This creates 3 teams with 3 cats each, for a total of 9 cats. It also defines Coco and Polter as rivals.
