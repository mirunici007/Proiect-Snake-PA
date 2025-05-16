#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "question.h"

static QuestionNode* easyHead = NULL;
static int easyCount = 0;
static QuestionNode* hardHead = NULL;
static int hardCount = 0;
 QuestionNode* currentQuestion = NULL;


static void addEasyQuestion(const char* q, const char* a) {
    QuestionNode* newNode = (QuestionNode*)malloc(sizeof(QuestionNode));
    if (!newNode) {
        perror("Eroare la alocarea memoriei");
        exit(EXIT_FAILURE);
    }

    strncpy(newNode->data.question, q, MAX_TEXT - 1);
    newNode->data.question[MAX_TEXT - 1] = '\0';

    strncpy(newNode->data.correctAnswer, a, MAX_TEXT - 1);
    newNode->data.correctAnswer[MAX_TEXT - 1] = '\0';

    // Parsăm răspunsurile
    newNode->data.answerCount = 0;
    char copy[MAX_TEXT];
    strncpy(copy, a, MAX_TEXT - 1);
    copy[MAX_TEXT - 1] = '\0';
    char* token = strtok(copy, "|");
    while (token && newNode->data.answerCount < 5) {
        strncpy(newNode->data.correctAnswers[newNode->data.answerCount], token, MAX_TEXT - 1);
        newNode->data.correctAnswers[newNode->data.answerCount][MAX_TEXT - 1] = '\0';
        newNode->data.answerCount++;
        token = strtok(NULL, "|");
    }

    newNode->next = easyHead;
    easyHead = newNode;
    easyCount++;
}

static void addHardQuestion(const char* q, const char* a) {
    QuestionNode* newNode = (QuestionNode*)malloc(sizeof(QuestionNode));
    if (!newNode) {
        perror("Eroare la alocarea memoriei");
        exit(EXIT_FAILURE);
    }

    strncpy(newNode->data.question, q, MAX_TEXT - 1);
    newNode->data.question[MAX_TEXT - 1] = '\0';

    strncpy(newNode->data.correctAnswer, a, MAX_TEXT - 1);
    newNode->data.correctAnswer[MAX_TEXT - 1] = '\0';

    newNode->data.answerCount = 0;
    char copy[MAX_TEXT];
    strncpy(copy, a, MAX_TEXT - 1);
    copy[MAX_TEXT - 1] = '\0';
    char* token = strtok(copy, "|");
    while (token && newNode->data.answerCount < 5) {
        strncpy(newNode->data.correctAnswers[newNode->data.answerCount], token, MAX_TEXT - 1);
        newNode->data.correctAnswers[newNode->data.answerCount][MAX_TEXT - 1] = '\0';
        newNode->data.answerCount++;
        token = strtok(NULL, "|");
    }

    newNode->next = hardHead;
    hardHead = newNode;
    hardCount++;
}


void initQuestions() {
    srand((unsigned int)time(NULL));

   addEasyQuestion("Cat face 2 + 2?", "4|patru");
   addEasyQuestion("Ce culoare are cerul senin?", "albastru");
   addEasyQuestion("Ce limbaj folosesti in acest proiect?", "C|c");

   addHardQuestion("Care este cel mai lung fluviu din lume?", "Amazon");
    addHardQuestion("In ce an a avut loc Revolutia Franceza?", "1789");
    addHardQuestion("Care este al doilea nume al lui Mihai Eminescu?", "Eminovici");

    }


void showRandomEasyQuestion() {
    if (easyCount == 0) {
        printf("Nicio întrebare ușoară disponibilă.\n");
        return;
    }

    int index = rand() % easyCount;
    QuestionNode* current = easyHead;
    for (int i = 0; i < index && current != NULL; i++) {
        current = current->next;
    }

    if (current) {
        currentQuestion = current;
        printf("Întrebare ușoară: %s\n", current->data.question);
    }
}

void showRandomHardQuestion() {
    if (hardCount == 0) {
        printf("Nicio întrebare grea disponibilă.\n");
        return;
    }

    int index = rand() % hardCount;
    QuestionNode* current = hardHead;
    for (int i = 0; i < index && current != NULL; i++) {
        current = current->next;
    }

    if (current) {
        currentQuestion = current;
        printf("Întrebare grea: %s\n", current->data.question);
    }
}

int checkAnswer(const char* userAnswer) {
    if (!currentQuestion) return 0;

    for (int i = 0; i < currentQuestion->data.answerCount; i++) {
        if (strcasecmp(userAnswer, currentQuestion->data.correctAnswers[i]) == 0) {
            return 1; // răspuns corect
        }
    }

    return 0; // niciun răspuns nu se potrivește
}

void freeQuestions() {
    QuestionNode* current;

    current = easyHead;
    while (current) {
        QuestionNode* temp = current;
        current = current->next;
        free(temp);
    }
    easyHead = NULL;
    easyCount = 0;

    current = hardHead;
    while (current) {
        QuestionNode* temp = current;
        current = current->next;
        free(temp);
    }
    hardHead = NULL;
    hardCount = 0;

    currentQuestion = NULL;
}

/*initQuestions();

showRandomEasyQuestion();  // Afișează o întrebare ușoară
showRandomHardQuestion();  // Afișează o întrebare grea*/