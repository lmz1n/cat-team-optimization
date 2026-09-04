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
