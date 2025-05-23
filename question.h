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

extern QuestionNode* currentQuestion;

static void addQuestion(const char* q, const char* a);
void initQuestions();                      // Inițializează întrebările (din fișier)
void selectRandomQuestion();                // Afișează o întrebare aleatoare
int checkAnswer(int userAnswer);  // Verifică răspunsul
void freeQuestions();                     // Eliberează memoria întrebărilor
//void showRandomQuestion(); // Afișează întrebarea pe ecran
void draw_question(QuestionNode* q);

#endif