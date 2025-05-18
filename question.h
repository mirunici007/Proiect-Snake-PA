#ifndef QUESTIONS_H
#define QUESTIONS_H

#define MAX_TEXT 256

typedef struct Question {
    char question[MAX_TEXT];
    int correctAnswer;
    //char correctAnswers[5][MAX_TEXT]; // maxim 5 variante corecte per întrebare
    int answerCount;
} Question;

typedef struct QuestionNode {
    Question data;
    struct QuestionNode* next;
} QuestionNode;

void initQuestions();                      // Inițializează întrebările (din fișier)
void showRandomQuestion();                // Afișează o întrebare aleatoare
void showRandomEasyQuestion();
void showRandomHardQuestion();
int checkAnswer(int userAnswer);  // Verifică răspunsul
void freeQuestions();                     // Eliberează memoria întrebărilor

#endif