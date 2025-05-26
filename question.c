#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "question.h"
#include "raylib.h"

static QuestionNode* questionHead = NULL;
static int questionCount = 0;
 QuestionNode* currentQuestion = NULL;
extern int selectedAnswer = -1;

static void addQuestion(const char* q, const char* a) {
    QuestionNode* newNode = (QuestionNode*)malloc(sizeof(QuestionNode));
    if (!newNode) {
        perror("Eroare la alocarea memoriei");
        exit(EXIT_FAILURE);
    }

    strncpy(newNode->data.question, q, MAX_TEXT - 1);
    newNode->data.question[MAX_TEXT - 1] = '\0';


    newNode->data.correctAnswer = atoi(a); 
    newNode->data.answerCount = 4; 


    newNode->next = questionHead;
    questionHead = newNode;
    questionCount++;
}

void initQuestions() {
    srand((unsigned int)time(NULL));

   addQuestion("What are the main types of text-based digital content?\n  articles, blog posts, ebooks, and whitepapers\n  images and infographics\n  videos and podcasts\n social media posts and tweets", "1");
   addQuestion("Name two formats commonly used for interactive digital content.\n  quizzes and interactive infographics\n  blog posts and articles\n  videos and webinars\n  social media posts and emails.", "1");
   addQuestion("How can businesses use social media content to engage with their audience effectively?\n  ignoring customer comments and messages on social media platforms\n  posting content only abouts their products or services without providing any value to the audience\n  creating and sharing valuable and relevant content that addresses their audience's needs and interest\n  overloading the audience with excessive promotional posts and advertisements", "3");
   addQuestion("Which is an example of a digital content format that can be used to showcase product features and benefits?\n podcast episodes discussing the product features\n  an explainer video\n  a collection of images without any context\n  social media posts with short descriptionsof the product without any visuals or demonstrations.","2");
   addQuestion("How can virtual and augmented reality content enhance user experience?\n It can be really distracting and confusing for users.\n  It is only suitable for gaming and entertainment purposes\n  It is limited to expensive and high-end devices, making it inaccessible for most users\n  It can enhance user experience by providing immersive and interactive experiences that blend digital elements with the real world.","4");
   addQuestion("Is it important to analyze audience feedback and comments to identify areas for improvement and refinement in content?\n It is not relevant or necessary. \n Yes, it is essential to identify areas improvement and refinement in content.\n  Only feedback from friends and family should be considered.\n  One should rely only on intuition and personal preferences to determine conetnt improvements.","2");
   addQuestion("Is regularly updating digital content with the latest data, statistics, and industry trends to keep it relevant and valuable?\n  No, it is a time-consuming process.\n  Yes, regularly updating digital content is crucial to keep it relevant and valuable.\n  It shouldn't be a priority, as it doesn't affect its value.\n  Outdated information is easier to find and use. ","2");
   addQuestion("Why is it important to explore a diverse range of sources, such as articles, data, images, and videos, when gathering content for creating new and original digital content?\n  It helps increase the word count an dlenght of the content.\n  It allows the use of the same conent repeatedly for different projects, saving time and effort.\n  It is unnecessary and may lead to confusion and inconsistencies in the content. \n  It provides a varienty of perspectives and insights for a more comprehensive and unique content creation.","4");
   addQuestion("How do multimedia elements, such as images, videos, and infographics, enhance the visual appeal of digital content?\n  They encrease word count and lenght of the content, making it more comprehensive.\n  They distract the audience from the main message of the content, making it harder to understand.\n  They are unnecessary and do not impact the visual appeal.\n  They enhance visual appeal if digital content by captivating the audience's attention and making the conetnt more visually appealing and engaging.","4");
   addQuestion("What is the purpose of incorporating interactive elements, such as quizzes, or calls-on-action, in digital content?\n They overwhelm the audience with too much information, leading to disengagement\n They make the content more complicated and challeging to understand, discouraging audience interaction.\n  They create a more engaging and participative experience, encouraging audience interaction and feedback.\n They have no impact on audience engagement and participation.","3");
   addQuestion("What is GPT-3 primarly used for in content creation? \n  creating databases\n  generating text\n  developing mobile apps\n composing music","2");
   addQuestion("Which AI tool is known for generating visual content?\n  Excel\n Tensorflow\n AutoCAD\n  DALL-E","4");
   addQuestion("How can AI like GPT-3 enhance the content creation process?\n by replacing all marketing jobs\n by eliminating the need for human creativity\n  by automating and scalng content production\n by only generating content in English","3");
   addQuestion("In the context of AI-generated content, what does 'augmenting human creativity' mean? \n  AI completely takes over the creative process from humans\n  Humans are no longers needed in any creative process from humans\n  AI restricts the forms of content that can be created \n AI assists and enhances human-driven content creation ","4");
   addQuestion("Which type of content is NOT typically generated by AI like GPT-3 and DALL-E?\n  marketing copy\n  blog articles\n  visual art\n  perfume scents","4");
   addQuestion(" Which AI model is well-known for text generation capabilities?\n  AutoCAD\n  SolidWorks\n  Blender\n  GPT-4","4");
   addQuestion("What is a key consideration when using DALL-E for creating visuals?\n  The color calibration of the monitor\n The specificity of the text prompt\n  The pixel density of the images\n  The storage capacity of the AI system", "2");
   addQuestion("Why is ethical reasoning important in AI-generated content?\n  To make the content more entertaining\n  To ensure the content can go viral\n  To ensure content adheres to moral and legal standards\n  To reduce the cost of content production","3");
   addQuestion(" In the context of AI-generated content, what is 'integration'?\n  Combining different forms of content for a cohesive presentation\n  Reducing file sizes for storage\n  Translating content into multiple languages\n  Programming the AI to self-replicate","1");
   addQuestion("What does an effective prompt for GPT-3 include?\n  Ambiguous instructions\n Minimum character length\n  Maximum keyword density\n  Detailed context and desired output format","4");

    addQuestion("What are some common examples of visual content used in digital marketing?\n  text-based articles and blog posts\n audio podcasts and webinars\n social media posts wihtout any visuals or images\n infographics", "4");
    addQuestion("What is the difference between webinars and online courses?\n  They are the same, just the names differ.\n Webinars are live or pre-recorded online events that focus on a specific topic; they are more interactive and allow real-time engagement\n Webinars are static content with no audience interaction, while online courses are interactive.\n  Online courses are one-time events, while webinars are ongoing and have multiple sessions", "2");
    addQuestion("What are two formats commonly used for delivering audio content to the audience?\n  podcasts and audiobooks\n live video events and recorded vidoe presentations\n visual content with graphics and images\n text-based documents and digital books", "1");
    addQuestion("How can businesses use infographics to effectively communicate complex information?\n using long paragraphs of text to explain complex information in detail\n ignoring visual elements and relying on written content\n  presenting data visually\n using complex jargon and technical language","3");
    addQuestion("How can user-generated content be leveraged to benefit a brand's digital marketing strategy?","2");
    addQuestion("What is the purpose of refining digital content?\n  to ensure clarity, accuracy, and consistency, making it more effective and re;evant to the target audience.\n  is to increase its word count and make it longer.\n  to add more multimedia elements to make it visually appealing.\n  to use complex languages and jargon to impress the audience.", "1");
    addQuestion("How can multimedia elements enhance digital content?\n  by making it more complex and challenging to understand. \n  by increasing word count and making it longer\n  by captivatingthe audience's attention, increasing engagement, and making the content more visually appealing\n  by replacing the need for written conent and relying solely on visuals.","3");
    addQuestion("What are some examples of interactive elements that can be integrated into digital content?\n  images, videos, and infographics\n  social media sharing buttons and website links.\n  relevant keywords and meta tags for search engine information\n  quizzes, polls, and calls-on-action","4");
    addQuestion("Why is updating digial conent with the latest information and industry trends important?\n  is not essential, as the original content is already valuable\n  to keep the conent accurate, relevant, and valuable to the audience\n  is time-consuming and unnecessary\n  is only relevant for certain industries","2");
    addQuestion("How does integrating user feedback contribute to conent improvement?\n  by allowing content creators to address the audience's needs and preferences\n  It does not contribute to the content improvement.\n  It only makes the content more complex and confusing for the audience.\n  It is unnecessary as the content creators already know ehat is best for their audience.","1");
    addQuestion("How does identifying common themes and connections among the various content items contribute to the creation of a cohesive narrative?\n  It makes the content more complex and challenging for the audience to understand.\n  It allows content creators to copy and paste content without making ani modifications, saving time and effort.\n  It helps create a logical flow and structure, ensuring the content is well-connected and coherent. \n 4.It has no impact on the narrative and structure of the content.","3");
    addQuestion("Why is adding your own unique insights and perspectives essential when creating new digital content?\n  It is unnecessary and may confuse the audience, so it is best to stick to existing information. \n  It brings a fresh and original angle to the content, making it unique and engaging.\n  They may not be relevant.\n  It takes too much time and effort and does not add value to the content.","2");
    addQuestion("What Kind of output would you expect from DALL-E if provided with a descrpitive prompt?\n  a detailed image\n  a spreadsheet\n a database\n  a website layout","1");
    addQuestion("How does GPT-3 help in the field of marketing?\n  By automating customer support\n  By enhancing web page loading speed\n  By generating relevant copy\n By improving server uptime","3");
    addQuestion("What should be considered when prompting DALL-E to create visual content?\n  The color of the user interface\n  The precision and detail of the prompt\n  The programming language used\n  The number of users online", "2");
    addQuestion("What is a realistic expectation when using AI to create content?\n  AI will require some level of human oversight and editing\n  AI can generate large volumes of content with no errors\n  AI will make content decisions independently\n  AI does not need data inputs to generate content","1");
    addQuestion("In AI-generated content, what is the significance of 'multimedia'?\n  In encompasses various content forms like text, images, video, and audio\n  it refers to the use of text and images\n  It is limited to audio-visual content\n  It only includes content that can be printed","2");
    addQuestion(" What kind of content might a business use AI-generated text and visuals for?\n  Social media campaigns\n  Internal server maintenance logs\n  Database encryption methods\n  Firmware update logs","1");
    addQuestion("What is the aim of a case study analysis in AI ethics?\n  To compile statistics on AI failures\n  To find the most cost-effective AI model\n  To identify and suggest resolutions to ethical issues\n  To design a new AI system from scratch","3");

}

void selectRandomQuestion() {
    if (questionCount == 0) {
        currentQuestion = NULL;
        return;
    }

    int index = rand() % questionCount;
    QuestionNode* current = questionHead;
    for (int i = 0; i < index && current != NULL; i++) {
        current = current->next;
    }

    currentQuestion = current;
}

int checkAnswer(int userAnswer) {
    if (!currentQuestion) return 0;

    if (userAnswer < 1 || userAnswer > 4) {
        return -1; // Răspuns invalid
    }

    return userAnswer == currentQuestion->data.correctAnswer ? 1 : 0;
}

void freeQuestions() {
    QuestionNode* current;

    while (questionHead) {
        current = questionHead;
        questionHead = questionHead->next;
        free(current);
    }

    questionCount = 0;
    currentQuestion = NULL;
}

// void showRandomQuestion() {
//     if (currentQuestion == NULL) return;

//     int screenWidth = GetScreenWidth();
//     int screenHeight = GetScreenHeight();

//     // Coordonate pentru butoane
//     Rectangle answerBoxes[4];
//     const int boxWidth = 600;
//     const int boxHeight = 50;
//     const int startY = screenHeight / 2 - 120;
//     const int spacing = 70;
//     int selected = -1;

//     // Setăm răspunsurile
//     char *questionText = currentQuestion->data.question;
//     int correctAnswer = currentQuestion->data.correctAnswer;

//     // Creăm zonele butoanelor
//     for (int i = 0; i < 4; i++) {
//         answerBoxes[i].x = screenWidth / 2 - boxWidth / 2;
//         answerBoxes[i].y = startY + i * spacing;
//         answerBoxes[i].width = boxWidth;
//         answerBoxes[i].height = boxHeight;
//     }

//     BeginDrawing();
//     ClearBackground(RAYWHITE);

//     DrawText("Choose the correct answer:", screenWidth / 2 - 170, 50, 24, BLACK);

//     // Afișăm întrebarea (prima linie)
//     const char* firstLine = strtok(questionText, "\n");
//     DrawText(firstLine, screenWidth / 2 - MeasureText(firstLine, 22) / 2, 100, 22, DARKGRAY);

//     // Afișăm variantele de răspuns
//     for (int i = 0; i < 4; i++) {
//         // Extragem linia curentă
//         char* line = strtok(NULL, "\n");
//         if (!line) break;

//         Color boxColor = LIGHTGRAY;

//         // Detectăm click
//         if (CheckCollisionPointRec(GetMousePosition(), answerBoxes[i])) {
//             boxColor = SKYBLUE;
//             if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
//                 selected = i + 1; // răspunsurile sunt 1-based
//             }
//         }

//         // Dacă a fost selectat, colorăm în funcție de corectitudine
//         if (selected != -1) {
//             if (selected == correctAnswer && selected == i + 1) boxColor = GREEN;
//             else if (selected == i + 1) boxColor = RED;
//         }

//         DrawRectangleRec(answerBoxes[i], boxColor);
//         DrawRectangleLinesEx(answerBoxes[i], 2, DARKGRAY);
//         DrawText(line, answerBoxes[i].x + 10, answerBoxes[i].y + 12, 20, BLACK);
//     }

//     EndDrawing();
// }

void DrawTextManualWrap(const char* text, int x, int y, int maxWidth, int fontSize, Color color) {
    char buffer[1024];
    strncpy(buffer, text, sizeof(buffer)-1);
    buffer[sizeof(buffer)-1] = '\0';

    char* line = buffer;
    int lineHeight = fontSize + 6;
    while (*line) {
        int len = 0, lastSpace = -1, width = 0;
        while (line[len] && width < maxWidth) {
            if (line[len] == ' ') lastSpace = len;
            len++;
            char temp = line[len];
            line[len] = '\0';
            width = MeasureText(line, fontSize);
            line[len] = temp;
        }
        if (width >= maxWidth && lastSpace != -1) len = lastSpace;
        char old = line[len];
        line[len] = '\0';
        
        DrawText(line, x, y, fontSize, color);

        line[len] = old;
        line += len;
        while (*line == ' ') line++;
        y += lineHeight;
        if (!*line) break;
    }
}

void draw_question(QuestionNode* q) {
    if (!q) return;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();


    // Extrage prima linie (întrebarea)
    char questionCopy[MAX_TEXT];
    strncpy(questionCopy, q->data.question, MAX_TEXT);
    questionCopy[MAX_TEXT-1] = '\0';

    char* saveptr;
    char* firstLine = strtok_r(questionCopy, "\n", &saveptr);
    //DrawText(firstLine, screenWidth / 2 - MeasureText(firstLine, 22) / 2, 100, 22, DARKGRAY);
    DrawTextManualWrap(firstLine, screenWidth / 2 - 400, 100, 800, 30, RAYWHITE);

    // Extrage și afișează răspunsurile cu butoane A, B, C, D
    int y = 250;
    int boxWidth = 50;      // Lățimea butonului pentru literă
    int boxHeight = 50;     // Înălțimea butonului pentru literă
    int spacing = 50;
    int answerSpacingY = 30;
    int answerTextOffsetX = 70; // Distanța de la stânga ecranului pentru textul răspunsului

    for (int i = 0; i < 4; i++) {
        char* line = strtok_r(NULL, "\n", &saveptr);
        if (!line) break;

        // Poziția butonului (doar pentru literă)
        Rectangle letterBox;
        letterBox.x = screenWidth / 2 - 400 + 10; // Poziționează la stânga
        letterBox.y = y + i * (boxHeight + answerSpacingY);
        letterBox.width = boxWidth;
        letterBox.height = boxHeight;

        // Desenează butonul pentru literă
        Color boxColor = LIGHTGRAY;
        Vector2 mouse = GetMousePosition();
        if (CheckCollisionPointRec(mouse, letterBox)) {
            boxColor = SKYBLUE;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                // Marchează răspunsul selectat (poți folosi o variabilă globală)
                selectedAnswer = i + 1; // 1-based
            }
        }
        DrawRectangleRec(letterBox, boxColor);
        DrawRectangleLinesEx(letterBox, 2, DARKGRAY);

        // Desenează litera (A, B, C, D) centrată în buton
        char letter[3] = { 'A' + i, '.', '\0' };
        int letterWidth = MeasureText(letter, 28);
        DrawText(letter, letterBox.x + (boxWidth - letterWidth) / 2, letterBox.y + (boxHeight - 28) / 2, 28, DARKBLUE);

        // Desenează textul răspunsului lângă buton
        DrawTextManualWrap(line, letterBox.x + boxWidth + 20, letterBox.y + 5, 700, 20, RAYWHITE);
    }

    // Poți returna answerBoxes dacă vrei să le folosești pentru input cu mouse-ul
}