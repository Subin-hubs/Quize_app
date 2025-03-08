#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void menu();
void choose();
void question();
void saveScore(int score);
void viewScore();

int main() {
    menu();
    return 0;
}

void menu() {
    int choice;
    while (1) {
        printf("\n*-----------------*\n");
        printf("1: Start the quiz\n");
        printf("2: View Score\n");
        printf("3: Exit the quiz\n");
        printf("*-----------------*\n");

         //call choose function to choose the user needs
        choose();
    }
}

void choose() {
    int choice;
    printf("\nWhat do you want to do?\n");
    printf("Press 1 to start the Quiz\n");
    printf("Press 2 to view the score\n");
    printf("Press 3 to exit\n\n");
    scanf("%d", &choice);

    if (choice == 1) {
        question(); //Start the quize and ask diffrent question to the user
    } else if (choice == 2) {
        viewScore(); // previous score
    } else if (choice == 3) {
        printf("Exiting Quiz...\n");
        exit(0);//stop the program
    } else {
        printf("\nInvalid Choice\n");
    }
}

void question() {
    char *questions[10] = {
        "1. What is the capital city of Nepal?",
        "2. What is the national language of Nepal?",
        "3. Which mountain is the highest in Nepal?",
        "4. Which river is considered the holiest in Nepal?",
        "5. Who was the first King of unified Nepal?",
        "6. Which city is known as the 'Gateway to Nepal'?",
        "7. Which famous temple is located in Lumbini, Nepal?",
        "8. What is the currency of Nepal?",
        "9. What is the national animal of Nepal?",
        "10. In which year did Nepal become a federal democratic republic?"
    };

    char *options[10][4] = {
        {"1) Kathmandu", "2) Pokhara", "3) Lalitpur", "4) Bhaktapur"},
        {"1) Nepali", "2) English", "3) Hindi", "4) Maithili"},
        {"1) Kanchenjunga", "2) Mount Everest", "3) Dhaulagiri", "4) Makalu"},
        {"1) Ganges", "2) Karnali", "3) Bagmati", "4) Koshi"},
        {"1) Prithvi Narayan Shah", "2) Tribhuvan", "3) Bhimsen Thapa", "4) Rana Bahadur Shah"},
        {"1) Biratnagar", "2) Pokhara", "3) Kathmandu", "4) Nepalgunj"},
        {"1) Pashupatinath", "2) Swayambhunath", "3) Lumbini", "4) Muktinath"},
        {"1) Nepali Rupee", "2) Indian Rupee", "3) Dollar", "4) Euro"},
        {"1) Cow", "2) Elephant", "3) Tiger", "4) Yeti"},
        {"1) 1950", "2) 2008", "3) 2015", "4) 1990"}
    };

    int correctAnswers[10] = {1, 1, 2, 3, 1, 3, 3, 1, 1, 2}; // Correct answers
    int userAnswer, score = 0;

    for (int i = 0; i < 10; i++) {
        printf("\n%s\n", questions[i]);

        // Print the options
        for (int j = 0; j < 4; j++) {
            printf("%s\n", options[i][j]);
        }

        // Start Timer
        time_t startTime, endTime;
        startTime = time(NULL);

        printf("Enter your answer (1/2/3/4) within 10 seconds: ");
        scanf("%d", &userAnswer);

        // Check time taken
        endTime = time(NULL);
        if (difftime(endTime, startTime) > 10) {
            printf("Time's up! Moving to the next question...\n");
            continue;
        }

        // Validate input
        if (userAnswer < 1 || userAnswer > 4) {
            printf("Invalid input! Please enter a number between 1 and 4.\n");
            i--; // Repeat the same question
            continue;
        }

        // Check if answer is correct
        if (userAnswer == correctAnswers[i]) {
            score++;
            printf("Correct!\n");
        } else {
            printf("Incorrect. The correct answer is: %d\n", correctAnswers[i]);
        }
    }

    printf("\nYour final score: %d/10\n", score);

    // Grading system
    if (score >= 8) {
        printf("Grade: Excellent\n");
    } else if (score >= 6) {
        printf("Grade: Good\n");
    } else if (score >= 4) {
        printf("Grade: Average\n");
    } else {
        printf("Grade: Poor\n");
    }

    // Save score to file
    saveScore(score);

    // Ask user if they want to retry
    int retry;
    printf("\nDo you want to retry the quiz? (1 for Yes, 2 for No): ");
    scanf("%d", &retry);

    if (retry == 1) {
        question();
    } else {
        menu();
    }
}

void saveScore(int score) {
    FILE *file = fopen("quiz_scores.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "Score: %d/10\n", score);
    fclose(file);
}

void viewScore() {
    FILE *file = fopen("quiz_scores.txt", "r");
    if (file == NULL) {
        printf("No previous scores found!\n");
        return;
    }

    printf("\nPrevious Scores:\n");
    char line[50];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}
