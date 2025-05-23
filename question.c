#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "question.h"
#include "raylib.h"

static QuestionNode* questionHead = NULL;
static int questionCount = 0;
 QuestionNode* currentQuestion = NULL;

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

   addQuestion("What are the main types of text-based digital content?\n 1. articles, blog posts, ebooks, and whitepapers\n 2. images and infographics\n 3. videos and podcasts\n 4. social media posts and tweets", "1");
   addQuestion("Name two formats commonly used for interactive digital content.\n 1. quizzes and interactive infographics\n 2. blog posts and articles\n 3. videos and webinars\n 4. social media posts and emails.", "1");
   addQuestion("How can businesses use social media content to engage with their audience effectively?\n 1. ignoring customer comments and messages on social media platforms\n 2. posting content only abouts their products or services without providing any value to the audience\n 3. creating and sharing valuable and relevant content that addresses their audience's needs and interest\n 4. overloading the audience with excessive promotional posts and advertisements", "3");
   addQuestion("Which is an example of a digital content format that can be used to showcase product features and benefits?\n 1. podcast episodes discussing the product features\n 2. an explainer video\n 3. a collection of images without any context\n 4. social media posts with short descriptionsof the product without any visuals or demonstrations.","2");
   addQuestion("How can virtual and augmented reality content enhance user experience?\n 1. It can be really distracting and confusing for users.\n 2. It is only suitable for gaming and entertainment purposes\n 3. It is limited to expensive and high-end devices, making it inaccessible for most users\n 4. It can enhance user experience by providing immersive and interactive experiences that blend digital elements with the real world.","4");
   addQuestion("Is it important to analyze audience feedback and comments to identify areas for improvement and refinement in content?\n1. It is not relevant or necessary. \n2. Yes, it is essential to identify areas improvement and refinement in content.\n 3. Only feedback from friends and family should be considered.\n 4. One should rely only on intuition and personal preferences to determine conetnt improvements.","2");
   addQuestion("Is regularly updating digital content with the latest data, statistics, and industry trends to keep it relevant and valuable?\n 1. No, it is a time-consuming process.\n 2. Yes, regularly updating digital content is crucial to keep it relevant and valuable.\n 3. It shouldn't be a priority, as it doesn't affect its value.\n 4. Outdated information is easier to find and use. ","2");
   addQuestion("Why is it important to explore a diverse range of sources, such as articles, data, images, and videos, when gathering content for creating new and original digital content?\n 1. It helps increase the word count an dlenght of the content.\n 2. It allows the use of the same conent repeatedly for different projects, saving time and effort.\n 3. It is unnecessary and may lead to confusion and inconsistencies in the content. \n 4. It provides a varienty of perspectives and insights for a more comprehensive and unique content creation.","4");
   addQuestion("How do multimedia elements, such as images, videos, and infographics, enhance the visual appeal of digital content?\n 1. They encrease word count and lenght of the content, making it more comprehensive.\n 2. They distract the audience from the main message of the content, making it harder to understand.\n 3. They are unnecessary and do not impact the visual appeal.\n 4. They enhance visual appeal if digital content by captivating the audience's attention and making the conetnt more visually appealing and engaging.","4");
   addQuestion("What is the purpose of incorporating interactive elements, such as quizzes, or calls-on-action, in digital content?\n1. They overwhelm the audience with too much information, leading to disengagement\n 2 .They make the content more complicated and challeging to understand, discouraging audience interaction.\n 3. They create a more engaging and participative experience, encouraging audience interaction and feedback.\n 4. They have no impact on audience engagement and participation.","3");
   addQuestion("What is GPT-3 primarly used for in content creation? \n 1. creating databases\n 2. generating text\n 3. developing mobile apps\n 4.composing music","2");
   addQuestion("Which AI tool is known for generating visual content?\n 1. Excel\n 2. Tensorflow\n 3.AutoCAD\n 4. DALL-E","4");
   addQuestion("How can AI like GPT-3 enhance the content creation process?\n 1. by replacing all marketing jobs\n 2.by eliminating the nned for human creativity\n 3. by automating and scalng content production\n 4.by only generating content in English","3");
   addQuestion("In the context of AI-generated content, what does 'augmenting human creativity' mean? \n 1. AI completely takes over the creative process from humans\n 2. Humans are no longers needed in any creative process from humans\n 3. AI restricts the forms of content that can be created \n 4.AI assists and enhances human-driven content creation ","4");
   addQuestion("Which type of content is NOT typically generated by AI like GPT-3 and DALL-E?\n 1. marketing copy\n 2. blog articles\n 3. visual art\n 4. perfume scents","4");
   addQuestion(" Which AI model is well-known for text generation capabilities?\n 1. AutoCAD\n 2. SolidWorks\n 3. Blender\n 4. GPT-4","4");
   addQuestion("What is a key consideration when using DALL-E for creating visuals?\n 1. The color calibration of the monitor\n 2.The specificity of the text prompt\n 3. The pixel density of the images\n 4. The storage capacity of the AI system", "2");
   addQuestion("Why is ethical reasoning important in AI-generated content?\n 1. To make the content more entertaining\n 2. To ensure the content can go viral\n 3. To ensure content adheres to moral and legal standards\n 4. To reduce the cost of content production","3");
   addQuestion(" In the context of AI-generated content, what is 'integration'?\n 1. Combining different forms of content for a cohesive presentation\n 2. Reducing file sizes for storage\n 3. Translating content into multiple languages\n 4. Programming the AI to self-replicate","1");
   addQuestion("What does an effective prompt for GPT-3 include?\n 1. Ambiguous instructions\n 2.Minimum character length\n 3. Maximum keyword density\n 4. Detailed context and desired output format","4");

    addQuestion("What are some common examples of visual content used in digital marketing?\n 1. text-based articles and blog posts\n 2.audio podcasts and webinars\n 3.social media posts wihtout any visuals or images\n 4.infographics", "4");
    addQuestion("What is the difference between webinars and online courses?\n 1. They are the same, just the names differ.\n 2.Webinars are live or pre-recorded online events that focus on a specific topic; they are more interactive and allow real-time engagement\n 3.Webinars are static content with no audience interaction, while online courses are interactive.\n 4. Online courses are one-time events, while webinars are ongoing and have multiple sessions", "2");
    addQuestion("What are two formats commonly used for delivering audio content to the audience?\n 1. podcasts and audiobooks\n 2.live video events and recorded vidoe presentations\n 3.visual content with graphics and images\n 4.text-based documents and digital books", "1");
    addQuestion("How can businesses use infographics to effectively communicate complex information?\n 1.using long paragraphs of text to explain complex information in detail\n 2.ignoring visual elements and relying on written content\n 3. presenting data visually\n 4.using complex jargon and technical language","3");
    addQuestion("How can user-generated content be leveraged to benefit a brand's digital marketing strategy?","2");
    addQuestion("What is the purpose of refining digital content?\n 1. to ensure clarity, accuracy, and consistency, making it more effective and re;evant to the target audience.\n 2. is to increase its word count and make it longer.\n 3. to add more multimedia elements to make it visually appealing.\n 4. to use complex languages and jargon to impress the audience.", "1");
    addQuestion("How can multimedia elements enhance digital content?\n 1. by making it more complex and challenging to understand. \n 2. by increasing word count and making it longer\n 3. by captivatingthe audience's attention, increasing engagement, and making the content more visually appealing\n 4. by replacing the need for written conent and relying solely on visuals.","3");
    addQuestion("What are some examples of interactive elements that can be integrated into digital content?\n 1. images, videos, and infographics\n 2. social media sharing buttons and website links.\n 3. relevant keywords and meta tags for search engine information\n 4. quizzes, polls, and calls-on-action","4");
    addQuestion("Why is updating digial conent with the latest information and industry trends important?\n 1. is not essential, as the original content is already valuable\n 2. to keep the conent accurate, relevant, and valuable to the audience\n 3. is time-consuming and unnecessary\n 4. is only relevant for certain industries","2");
    addQuestion("How does integrating user feedback contribute to conent improvement?\n 1. by allowing content creators to address the audience's needs and preferences\n 2. It does not contribute to the content improvement.\n 3. It only makes the content more complex and confusing for the audience.\n 4. It is unnecessary as the content creators already know ehat is best for their audience.","1");
    addQuestion("How does identifying common themes and connections among the various content items contribute to the creation of a cohesive narrative?\n 1. It makes the content more complex and challenging for the audience to understand.\n 2. It allows content creators to copy and paste content without making ani modifications, saving time and effort.\n 3. It helps create a logical flow and structure, ensuring the content is well-connected and coherent. \n 4.It has no impact on the narrative and structure of the content.","3");
    addQuestion("Why is adding your own unique insights and perspectives essential when creating new digital content?\n 1. It is unnecessary and may confuse the audience, so it is best to stick to existing information. \n 2. It brings a fresh and original angle to the content, making it unique and engaging.\n 3. They may not be relevant.\n 4. It takes too much time and effort and does not add value to the content.","2");
    addQuestion("What Kind of output would you expect from DALL-E if provided with a descrpitive prompt?\n 1. a detailed image\n 2. a spreadsheet\n 3.a database\n 4. a website layout","1");
    addQuestion("How does GPT-3 help in the field of marketing?\n 1. By automating customer support\n 2. By enhancing web page loading speed\n 3. By generating relevant copy\n 4.By improving server uptime","3");
    addQuestion("What should be considered when prompting DALL-E to create visual content?\n 1. The color of the user interface\n 2. The precision and detail of the prompt\n 3. The programming language used\n 4. The number of users online", "2");
    addQuestion("What is a realistic expectation when using AI to create content?\n 1. AI will require some level of human oversight and editing\n 2. AI can generate large volumes of content with no errors\n 3. AI will make content decisions independently\n 4. AI does not need data inputs to generate content","1");
    addQuestion("In AI-generated content, what is the significance of 'multimedia'?\n 1. In encompasses various content forms like text, images, video, and audio\n 2. it refers to the use of text and images\n 3. It is limited to audio-visual content\n 4. It only includes content that can be printed","2");
    addQuestion(" What kind of content might a business use AI-generated text and visuals for?\n 1. Social media campaigns\n 2. Internal server maintenance logs\n 3. Database encryption methods\n 4. Firmware update logs","1");
    addQuestion("What is the aim of a case study analysis in AI ethics?\n 1. To compile statistics on AI failures\n 2. To find the most cost-effective AI model\n 3. To identify and suggest resolutions to ethical issues\n 4. To design a new AI system from scratch","3");

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

void draw_question(QuestionNode* q) {
    if (!q) return;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    DrawText("Choose the correct answer:", screenWidth / 2 - 170, 50, 24, BLACK);

    // Extrage prima linie (întrebarea)
    char questionCopy[MAX_TEXT];
    strncpy(questionCopy, q->data.question, MAX_TEXT);
    questionCopy[MAX_TEXT-1] = '\0';

    char* saveptr;
    char* firstLine = strtok_r(questionCopy, "\n", &saveptr);
    DrawText(firstLine, screenWidth / 2 - MeasureText(firstLine, 22) / 2, 100, 22, DARKGRAY);

    // Extrage și afișează răspunsurile cu butoane A, B, C, D
    int y = 160;
    int boxWidth = 600;
    int boxHeight = 50;
    int spacing = 20;
    Rectangle answerBoxes[4];

    for (int i = 0; i < 4; i++) {
        char* line = strtok_r(NULL, "\n", &saveptr);
        if (!line) break;

        answerBoxes[i].x = screenWidth / 2 - boxWidth / 2;
        answerBoxes[i].y = y + i * (boxHeight + spacing);
        answerBoxes[i].width = boxWidth;
        answerBoxes[i].height = boxHeight;

        // Desenează butonul
        DrawRectangleRec(answerBoxes[i], LIGHTGRAY);
        DrawRectangleLinesEx(answerBoxes[i], 2, DARKGRAY);

        // Desenează litera (A, B, C, D)
        char letter[3] = { 'A' + i, '.', '\0' };
        DrawText(letter, answerBoxes[i].x + 15, answerBoxes[i].y + 12, 28, DARKBLUE);

        // Desenează textul răspunsului
        DrawText(line, answerBoxes[i].x + 50, answerBoxes[i].y + 12, 20, BLACK);
    }

    // Poți returna answerBoxes dacă vrei să le folosești pentru input cu mouse-ul
}