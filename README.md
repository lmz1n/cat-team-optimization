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

_Polter Ragdoll 70 85 92 78 81_

_Hana DSH 95 72 80 91 77_

_Leo Tux 88 12 71 83 79_

_Fudge DSH 76 81 89 92 84_

_Pieces DSH 82 77 86 79 93_

_Caesar Siamese 47 82 15 63 91_

_Percy DSH 28 54 76 39 12_

_Pikachu DSH 58 23 87 41 69_

_1_

_Coco Polter_

This creates 3 teams with 3 cats each, for a total of 9 cats. It also defines Coco and Polter as rivals.

# Scoring System
Each team is evaluated using several factors.

**Base Score:**

Each cat's five trait scores are added together:

_Base Score = Trait1 + Trait2 + Trait3 + Trait4 + Trait5_

The team's base score is calculated using the average of the cats' base scores.

**High Performer Bonus:**

A cat receives an additional bonus for every trait score greater than or equal to 90.

_Bonus = 5 points × Number of Traits ≥ 90_

**Synergy Bonus:**

A team receives a 30-point bonus if every cat on the team has at least one trait with a score of 85 or higher.

**Breed Diversity:**

A team receives a:

+10 bonus

when every cat belongs to a different breed.

If a team contains duplicate breeds, it receives:

-15 penalty

**Position Bonus:**

Each position in a team applies a percentage bonus based on the cat's base score.

The program defines the following position bonuses:

- Position 1 → 3.0%
- Position 2 → 5.0%
- Position 3 → 4.0%
- Position 4 → 6.0%
- Position 5 → 7.0%
- Position 6 → 2.0%
- Position 7 → 8.0%
- Position 8 → 1.0%
- Position 9 → 9.0%
- Position 10 → 1.5%

The position bonus is calculated using:

_Position Bonus = Cat Base Score × Position Percentage_

**Rival Penalty:**

If rival cats are placed next to each other within a team, the team receives:

-25 points per rival pairing

# Algorithm
The program uses recursive permutation generation with backtracking.

Conceptually:

Start

|

├── Select an unused cat

├── Add the cat to the current permutation

├── Recursively select the next unused cat

├── Continue until every cat has been placed

├── Divide the permutation into teams

├── Calculate the score of every team

├── Calculate the total grouping score

├── Save the grouping if it is the best found

└── Backtrack and try another arrangement

The used array tracks which cats are currently included in the permutation.

After a recursive branch is completed, the cat is marked as unused again, allowing the algorithm to explore another possible arrangement.

# Data Structures

The project uses two main structures.

**Cat:**

Cat

├── name

├── breed

├── scores[5]

└── baseScore

The name and breed fields are dynamically allocated.

**Rivals:**

Rivals

├── cat1

└── cat2

Each rivalry stores pointers to the corresponding Cat structures.

# Example Output
Using the provided input, the program produces:

_Best Teams Grouping score: 1297.89_

_Team 1: Caesar Fudge Polter 476.61_

_Team 2: Percy Coco Leo 375.49_

_Team 3: Pikachu Pieces Hana 445.79_

_Best Candidate: Caesar Fudge Polter_

The program first identifies the highest-scoring overall grouping and then determines which individual team within that grouping has the highest score.

# Technologies Used
- C
- Recursion
- Backtracking
- Permutation generation
- Dynamic memory allocation
- Structures
- Pointers
- Arrays
- Standard input/output
- String manipulation
