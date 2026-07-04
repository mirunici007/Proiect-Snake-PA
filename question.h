#ifndef QUESTIONS_H
#define QUESTIONS_H
#include"raylib.h"

#define MAX_TEXT 3000
extern int selectedAnswer;

typedef struct Question {
    char question[MAX_TEXT];
    int correctAnswer;
    int answerCount;
} Question;

typedef struct QuestionNode {
    Question data;
    struct QuestionNode* next;
} QuestionNode;

extern QuestionNode* currentQuestion;

//function that adds a new question to the linked list of questions
static void addQuestion(const char* q, const char* a);

//function that initializes the questions by adding them to the linked list
void initQuestions();

//function that selects a random question from the linked list of questions and sets it as the current question on the screen
void selectRandomQuestion();

//function that checks if the user's answer is correct
int checkAnswer(int userAnswer);

//function that frees the memory allocated for the linked list of questions
void freeQuestions();

void DrawTextManualWrap(const char* text, int x, int y, int maxWidth, int fontSize, Color color);

void draw_question(QuestionNode* q);

#endif