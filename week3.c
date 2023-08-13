
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATES 5
#define MAX_VOTERS 100

struct Candidate {
    char name[50];
    int votes;
};

struct Voter {
    char name[50];
    int vote; // Index of the candidate voted for (1 to numCandidates), 0 for NOTA
};

struct Candidate candidates[MAX_CANDIDATES];
struct Voter voters[MAX_VOTERS];
int numCandidates = 0;
int numVoters = 0;

void displayMenu() {
    printf("\n----- Election Menu -----\n");
    printf("1. Add Candidates\n");
    printf("2. Cast Votes\n");
    printf("3. Display Winner(s)\n");
    printf("4. Exit\n");
    printf("Choose an option: ");
}

void addCandidates() {
    if (numCandidates >= MAX_CANDIDATES) {
        printf("Maximum candidate limit reached.\n");
        return;
    }

    printf("Enter number of candidates: ");
    scanf("%d", &numCandidates);

    for (int i = 0; i < numCandidates; i++) {
        printf("Enter candidate %d name: ", i + 1);
        scanf("%s", candidates[i].name);
        candidates[i].votes = 0;
    }

    printf("Candidates added successfully!\n");
}

int findCandidateIndex(int candidateChoice) {
    return candidateChoice - 1;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        printf("\033[H\033[J");  // Clear terminal on Unix-like systems
    #endif
}

void castVotes() {
    if (numVoters >= MAX_VOTERS) {
        printf("Maximum voter limit reached.\n");
        return;
    }

    printf("Enter number of voters: ");
    scanf("%d", &numVoters);

    for (int i = 0; i < numVoters; i++) {
        printf("Enter voter %d name: ", i + 1);
        scanf("%s", voters[i].name);

        clearScreen();

        printf("Welcome, %s! It's time to cast your vote.\n", voters[i].name);

        printf("Candidates:\n");
        for (int j = 0; j < numCandidates; j++) {
            printf("%d. %s\n", j + 1, candidates[j].name);
        }
        printf("%d. NOTA (None of the above)\n", numCandidates + 1);

        printf("Enter your choice (1 to %d, %d for NOTA): ", numCandidates, numCandidates + 1);
        scanf("%d", &voters[i].vote);

        if (voters[i].vote >= 1 && voters[i].vote <= numCandidates) {
            int candidateIndex = findCandidateIndex(voters[i].vote);
            candidates[candidateIndex].votes++;
        } else if (voters[i].vote == numCandidates + 1) {
            // Voter chose NOTA
        } else {
            printf("Invalid choice. Skipped voting for %s.\n", voters[i].name);
        }

        clearScreen();
    }

    printf("Votes casted successfully!\n");
}

void displayWinners() {
    int maxVotes = 0;
    printf("\nWinner(s):\n");

    for (int i = 0; i < numCandidates; i++) {
        if (candidates[i].votes > maxVotes) {
            maxVotes = candidates[i].votes;
        }
    }

    int numWinners = 0;
    for (int i = 0; i < numCandidates; i++) {
        if (candidates[i].votes == maxVotes) {
            printf("%s - %d votes\n", candidates[i].name, candidates[i].votes);
            numWinners++;
        }
    }

    if (numWinners > 1) {
        printf("It's a tie! %d candidates have the same number of votes.\n", numWinners);
    }
}

int main() {
    int choice;

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addCandidates();
                break;
            case 2:
                castVotes();
                break;
            case 3:
                displayWinners();
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please choose a valid option.\n");
        }
    } while (choice != 4);

    return 0;
}
