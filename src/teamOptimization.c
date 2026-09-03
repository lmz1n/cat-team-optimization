/* COP 3502C PA2
This program is written by: Luiz Miguel Vicente Massolini */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SCORES 5 // size of a cat scores array representing 5 traits
#define MAX_STR 25 // maximum name length of a cat
const float POSITION_BONUS[10] = {3.0, 5.0, 4.0, 6.0, 7.0, 2.0, 8.0, 1.0, 9.0, 1.5};

typedef struct Cat{
    char *name; // dynamically allocated cat name
    char *breed; // dynamically allocated breed
    int scores[MAX_SCORES]; // array of size 5 representing trait scores
    int baseScore; // sum of scores array
} Cat;

typedef struct Rivals{
    Cat *cat1; // pointer to cat1
    Cat *cat2; // pointer to cat2
} Rivals;

// bonus percentages that apply to each position
Cat *cats;
Rivals *rivals;
float bestPermScore;
int **tracker;

// Function prototypes
void getInput(int *c, int *n, int *r, int *t);
void generatePermutations(int start, int c, int r, int t, int n, int* perm, int* used);
float scoreTeam(int* perm, int startIndex, int c, int r);
bool AllBreedsDiff(int* perm, int teamStart, int c, int start, int cat);
void updateTracker(int* perm, int n, int c);
void printResults(int n, int c, int r);
void freeAll(int t, int n, int * perm, int * used);
int countHighPerformerTraits(Cat* cats, int score);
bool synergyBonusApplies(int* perm, int teamStart, int c, int currentCatInTeam, int traitIndex);
int rivalPenaltyApplies(Cat* cats, Rivals* rivals, int* perm, int teamStart, int catStart, int rivalsStart, int r, int c);

int main() {
    int c, n, r, t;
    getInput(&c, &n, &r, &t);

    bestPermScore = -1.0;

    // allocating memory for perm and used
    int* perm = malloc(t * sizeof(int));
    int* used = calloc(t, sizeof(int));
    
    // Start the recursive search for the best grouping
    generatePermutations(0, c, r, t, n, perm, used);

    printResults(n, c, r);

    freeAll(t, n, perm, used);

    return 0;
}
// Reads input, dinamically allocates memory for cat struct and rivals struct
void getInput(int *c, int *n, int *r, int *t) {
    // temporary buffers
    char tempName[MAX_STR];
    char tempBreed[MAX_STR];
    //error handling
    if (scanf("%d %d", n, c) != 2) return;
    *t = (*c) * (*n);
    // allocating memory and checking
    cats = (Cat*)malloc(*t * sizeof(Cat));
    if (cats == NULL) return;

    // Load cat data and calculate base scores
    for (int i = 0; i < *t; i++) {
        if(scanf("%s %s %d %d %d %d %d", tempName, tempBreed, &cats[i].scores[0], &cats[i].scores[1], &cats[i].scores[2],
            &cats[i].scores[3], &cats[i].scores[4]) != 7) return;

        cats[i].baseScore = 0;
        for(int j = 0; j < MAX_SCORES; j++) {
            cats[i].baseScore += cats[i].scores[j];
        }
        //allocating memory for names and breeds
        cats[i].name = (char*)malloc(strlen(tempName) + 1);
        cats[i].breed = (char*)malloc(strlen(tempBreed) + 1);
        strcpy(cats[i].name, tempName);
        strcpy(cats[i].breed, tempBreed);
    }
    // error handling and allocating memory for rivals
    if(scanf("%d", r) != 1) return;
    rivals = (Rivals*)malloc(*r * sizeof(Rivals));

    // Map rival names to their corresponding Cat pointers
    char tempName1[MAX_STR], tempName2[MAX_STR];
    for (int i = 0; i < *r; i++) {
        if(scanf("%s %s", tempName1, tempName2) != 2) return;
        rivals[i].cat1 = NULL;
        rivals[i].cat2 = NULL;

        for(int j = 0; j < *t; j++) {
            if(strcmp(cats[j].name, tempName1) == 0) rivals[i].cat1 = &cats[j];
            if(strcmp(cats[j].name, tempName2) == 0) rivals[i].cat2 = &cats[j];
        }
    }

    // Initialize 2D tracker to store the best cat IDs per team
    tracker = (int**)malloc(sizeof(int*) * (*n));
    for(int i = 0; i < *n; i++) {
        tracker[i] = (int*)malloc(sizeof(int) * (*c));
    }
}

int countHighPerformerTraits(Cat* cats, int score) {
    if (score == MAX_SCORES) return 0; // bs cs: calculated all scores
    int count = countHighPerformerTraits(cats, score + 1); // recursive case: next score
    if (cats->scores[score] >= 90) count++; 
    return count;
}

bool synergyBonusApplies(int* perm, int teamStart, int c, int catStart, int score) {
    if (catStart == c) return true;  // bs cs: all cats satisfy condition
    if (score == MAX_SCORES) return false; // bs cs: a cat does not satisfy condition

    //condition check
    if (cats[perm[teamStart + catStart]].scores[score] >= 85)
        return synergyBonusApplies(perm, teamStart, c, catStart + 1, 0); // recursive cs: next cat
   
    return synergyBonusApplies(perm, teamStart, c, catStart, score + 1); // recursive cs: next score
}

int rivalPenaltyApplies(Cat* cats, Rivals* rivals, int* perm, int teamStart, int catStart, int rivalsStart, int r, int c) {
    if (catStart >= c - 1) return 0; // bs cs: all cats analyzed
    if (rivalsStart >= r) return rivalPenaltyApplies(cats, rivals, perm, teamStart, catStart + 1, 0, r, c); // recursive cs: checked all rivalsand nothing, go to next cat
    // getting cat ptrs
    Cat* a = &cats[perm[teamStart + catStart]];
    Cat* b = &cats[perm[teamStart + catStart + 1]];
    // comparing cat a and b and vice versa
    if ((a == rivals[rivalsStart].cat1 && b == rivals[rivalsStart].cat2) ||
        (a == rivals[rivalsStart].cat2 && b == rivals[rivalsStart].cat1)) {
        return 1 + rivalPenaltyApplies(cats, rivals, perm, teamStart, catStart + 1, 0, r, c); // recursive cs: found rivals, go to next cat
    } else {
        return rivalPenaltyApplies(cats, rivals, perm, teamStart, catStart, rivalsStart + 1, r, c); // recursive cs: did not match rivals, go to next rivals
    }
}

void generatePermutations(int start, int c, int r, int t, int n, int* perm, int* used) {
    if (start == t) { // bs cs: full permutation 
        float currentTotalScore = 0.0;
        for(int i = 0; i < n; i++) {
            currentTotalScore += scoreTeam(perm, i * c, c, r); // calculate score of that specific team
        }

        // Save the best grouping found so far
        if (currentTotalScore > bestPermScore) {
            bestPermScore = currentTotalScore; 
            updateTracker(perm, n, c);
        }
        return;
    }  
    // used array recursive permutation
    for(int i = 0; i < t; i++) {
        if(!used[i]) { // check if used
            used[i] = 1; // mark as used
            perm[start] = i; //save index in perm
            generatePermutations(start + 1, c, r, t, n, perm, used); // next index
            used[i] = 0; // backtracking (uncheck it for next permutation)
        }
    }
}

float scoreTeam(int* perm, int startIndex, int c, int r) {
    float teamScore = 0;

    // Team base score calculation
    for(int i = 0; i < c; i++) {
        teamScore += (1.0 / c) * (cats[perm[startIndex + i]].baseScore);
    }

    // Apply various bonuses (High Performer, Synergy, Diversity, Position)
    for(int i = 0; i < c; i++) {
        teamScore += countHighPerformerTraits(&cats[perm[startIndex + i]], 0) * 5.0;
    }

    if (synergyBonusApplies(perm, startIndex, c, 0, 0)) teamScore += 30.0;
    if (AllBreedsDiff(perm, startIndex, c, 0, 1)) teamScore += 10.0;

    for(int i = 0; i < c; i++) {
        teamScore += (cats[perm[startIndex + i]].baseScore * (POSITION_BONUS[i] / 100.0));
    }

    // Apply penalties (Rivals and Duplicate Breeds)
    teamScore -= rivalPenaltyApplies(cats, rivals, perm, startIndex, 0, 0, r, c) * 25.0;
    if (!AllBreedsDiff(perm, startIndex, c, 0, 1)) teamScore -= 15.0;

    return teamScore;
}

bool AllBreedsDiff(int* perm, int teamStart, int c, int start, int cat) {
    if (start == c - 1) return true; // bs cs: all breeds diifer
    if (cat == c) return AllBreedsDiff(perm, teamStart, c, start + 1, start + 2); // recursive cs: cat's breed is unique, go to check next cats in team

    // check breed if breed names differ
    if (strcmp(cats[perm[teamStart + start]].breed, cats[perm[teamStart + cat]].breed) != 0) {
        return AllBreedsDiff(perm, teamStart, c, start, cat + 1); // recursive cs: breeds differ, go compare it to next cat
    }
    return false; // bs cs: duplicated breeds
}

void updateTracker(int* perm, int n, int c) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < c; j++) {
            tracker[i][j] = perm[i * c + j]; // 1d array perm into 2d array tracker
        }
    }
}

void printResults(int n, int c, int r) {
    float maxTeamScore = -1.0;
    int bestTeamIndex = 0;

    printf("Best Teams Grouping score: %.2f\n", bestPermScore);
    for(int i = 0; i < n; i++) {
        float currentTeamScore = scoreTeam(tracker[i], 0, c, r); // get scores
        printf("Team %d: ", i + 1);
        for(int j = 0; j < c; j++) {
            printf("%s ", cats[tracker[i][j]].name); 
        }
        printf("%.2f\n", currentTeamScore);

        if (currentTeamScore > maxTeamScore) { // print team with best score based on this logic
            maxTeamScore = currentTeamScore;
            bestTeamIndex = i;
        }
    }

    printf("Best Candidate: "); // print best team
    for (int i = 0; i < c; i++) {
        printf("%s%s", cats[tracker[bestTeamIndex][i]].name, (i == c - 1) ? "" : " ");
    }
    printf("\n");
}

// freeing all memory, inward to outward
void freeAll(int t, int n, int * perm, int * used) {
    for(int i = 0; i < t; i++) {
        free(cats[i].breed);
        free(cats[i].name);
    }
    free(cats);
    free(rivals);
    for(int i = 0; i < n; i++) free(tracker[i]);
    free(tracker);
    free(perm);
    free(used);
}
