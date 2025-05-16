#ifndef QUESTIONS_H
#define QUESTIONS_H

#define MAX_TEXT 256

typedef struct Question {
    char question[MAX_TEXT];
    char correctAnswer[MAX_TEXT];
    char correctAnswers[5][MAX_TEXT]; // maxim 5 variante corecte per întrebare
    int answerCount;
} Question;

typedef struct QuestionNode {
    Question data;
    struct QuestionNode* next;
} QuestionNode;

extern QuestionNode* currentQuestion;

void initQuestions();                      // Inițializează întrebările (din fișier)
void showRandomQuestion();                // Afișează o întrebare aleatoare
int checkAnswer(const char* userAnswer);  // Verifică răspunsul
void freeQuestions();                     // Eliberează memoria întrebărilor

#endif