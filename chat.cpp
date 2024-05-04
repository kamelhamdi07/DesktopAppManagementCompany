#include "chat.h"
#include "ui_chat.h"
#include <QTime>
chat::chat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chat)
{
    ui->setupUi(this);
   connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(processMessage())); // connecte le bouton d'envoi à la fonction processMessage()
   // Initialise le générateur de nombres aléatoires
   qsrand(QTime::currentTime().msec());
}

chat::~chat()
{
    delete ui;
}
/*QString responses[] = {
    "Bonjour! Comment ça va?",
    "Je suis content de vous parler!",
    "Comment puis-je vous aider?",
    "Je suis un chatbot, je peux répondre à vos questions!",
    "Désolé, je ne comprends pas votre question.",
    "Pouvez-vous reformuler votre question s'il vous plaît?",
};

void chatbot::processMessage() {
    QString message = ui->messageInput->text(); // récupère le message saisi par l'utilisateur
    ui->messageInput->clear(); // efface le champ de saisie
    ui->messageLog->append("<b>You:</b> " + message); // affiche le message de l'utilisateur dans le widget QTextEdit

    // traitement du message et génération de la réponse aléatoire
    int index = qrand() % 6; // génère un nombre aléatoire entre 0 et 5
    QString response = responses[index]; // récupère la réponse correspondante
    ui->messageLog->append("<b>ChatBot:</b> " + response); // affiche la réponse du chatbot dans le widget QTextEdit
}

// tableau de réponses
QStringList responses = {"Bonjour! Comment ça va?", " Moi aussi Je suis content de vous parler.", "Qu'aimeriez-vous discuter aujourd'hui?", "Je suis désolé, je ne comprends pas votre question."};

// compteur pour accéder à la prochaine réponse dans le tableau
int responseIndex = 0;

void chatbot::processMessage() {
    QString message = ui->messageInput->text(); // récupère le message saisi par l'utilisateur
    ui->messageInput->clear(); // efface le champ de saisie
    ui->messageLog->append("<b>You:</b> " + message); // affiche le message de l'utilisateur dans le widget QTextEdit

    // récupère la prochaine réponse dans le tableau
    QString response = responses[responseIndex];
    responseIndex = (responseIndex + 1) % responses.size(); // incrémente le compteur et revient au début du tableau si nécessaire

    ui->messageLog->append("<b>ChatBot:</b> " + response); // affiche la réponse du chatbot dans le widget QTextEdit
}
*/
void chat::processMessage() {

        QString message = ui->messageInput->text(); // récupère le message saisi par l'utilisateur
        ui->messageInput->clear(); // efface le champ de saisie
        ui->messageLog->append("<b>You:</b> " + message); // affiche le message de l'utilisateur dans le widget QTextEdit

        QString response;
        QString lowercaseMessage = message.toLower(); // convertit le message en minuscules
        QString uppercaseMessage = message.toUpper(); // convertit le message en majuscules

        // traitement du message et génération de la réponse
        if (lowercaseMessage == "bonjour" || lowercaseMessage == "salut" || lowercaseMessage == "hello" ||
            uppercaseMessage == "BONJOUR" || uppercaseMessage == "SALUT" || uppercaseMessage == "HELLO") {
            QStringList greetings = {"Bonjour! Comment ça va?", "Salut! Comment puis-je vous aider aujourd'hui?", "Hello! Que puis-je faire pour vous?"};
            response = greetings.at(qrand() % greetings.size());
            response += " &#x1F60A;"; // ajouter le smiley souriant à la fin de la réponse
             ui->messageLog->append("<b>Eyai:</b> " + response);
        }
        else if (lowercaseMessage == "vous etes qui" || lowercaseMessage == "enti chkoun " ||
                 uppercaseMessage == "VOUS ETES QUI" || uppercaseMessage == "ENTI CHKOUN") {
            response = "Je suis un chat bot, je suis content de vous parler.";
             ui->messageLog->append("<b>Eyai:</b> " + response);
        }
        else if (lowercaseMessage == "vous pouvez m'aider" || lowercaseMessage.contains("aide") || lowercaseMessage.contains("conseil") ||
                 uppercaseMessage == "VOUS POUVEZ M'AIDER" || uppercaseMessage.contains("AIDE") || uppercaseMessage.contains("CONSEIL")) {
            QStringList helpResponses = {"Bien sûr, que puis-je faire pour vous aider?", "Je suis là pour vous aider. De quoi avez-vous besoin?", "Je suis là pour vous soutenir. Que puis-je faire pour vous?"};
            response = helpResponses.at(qrand() % helpResponses.size());
             ui->messageLog->append("<b>Eyai:</b> " + response);
        }
        else if (lowercaseMessage.contains("heure") || uppercaseMessage.contains("HEURE")) {
            // Réponse avec l'heure actuelle
            QTime currentTime = QTime::currentTime();
            response = "Il est actuellement " + currentTime.toString("hh:mm:ss");
             ui->messageLog->append("<b>Eyai:</b> " + response);
        }
        else if (lowercaseMessage.contains("date") || uppercaseMessage.contains("DATE")) {
            // Réponse avec la date actuelle
            QDate currentDate = QDate::currentDate();
            response = "Nous sommes le " + currentDate.toString("dd.MM.yyyy");
            ui->messageLog->append("<b>Eyai:</b> " + response);
        }


        else if (lowercaseMessage == "l'intelligence artificielle ?" ||
                 uppercaseMessage == "L'INTELLIGENCE ARTIFICIELLE ?") {
            response = "L'intelligence artificielle est une branche de l'informatique qui vise à créer des machines capables de simuler l'intelligence humaine. Cela inclut des techniques telles que l'apprentissage automatique, le traitement du langage naturel et la vision par ordinateur.";
        }



        else if (message.toLower() == "derniers développements en informatique" || message.toUpper() == "DERNIERS DÉVELOPPEMENTS EN INFORMATIQUE") {
            QString response = "L'informatique est un domaine en constante évolution et de nouveaux développements apparaissent régulièrement. Parmi les derniers développements, on peut citer l'émergence de l'Internet des objets, la réalité virtuelle et augmentée, l'apprentissage automatique et l'intelligence artificielle, ainsi que les nouvelles technologies de stockage de données comme la mémoire à changement de phase.";
            ui->messageLog->append("<b>Eyai:</b> " + response);
        }
        else if (message.toLower() == "derniers développements techniques" || message.toUpper() == "DERNIERS DÉVELOPPEMENTS TECHNIQUES") {
            QString response = "Les derniers développements techniques sont très variés et dépendent du domaine d'application. Cependant, certaines des dernières avancées comprennent la miniaturisation des composants électroniques, l'utilisation de matériaux avancés pour la construction de véhicules plus légers et plus efficaces sur le plan énergétique, et l'utilisation de la technologie blockchain pour garantir la sécurité des transactions en ligne.";
            ui->messageLog->append("<b>Eyai:</b> " + response);
        }

        else if (lowercaseMessage == "mechant" || lowercaseMessage == "bara zamer " ||
                 uppercaseMessage == "MECHANT" || uppercaseMessage == "BARA ZAMER") {
            response = "Je suis désolé, mais en tant que Chat Bot, je n'ai pas de sentiments et je ne suis ni gentil ni méchant.";
            response += "&#x1F622;";

                                    ui->messageLog->append("<b>Eyai:</b> " + response);
                       }
                                   else {
                                       // réponse par défaut
                                       QStringList greetings = {"Bonjour! Comment puis-je vous aider aujourd'hui?", "Désolé, je ne comprends pas votre question.", "Hello! Que puis-je faire pour vous?","Pouvez-vous reformuler votre question s'il vous plaît?"};
                                       QString response = greetings.at(qrand() % greetings.size());
                                       response += " &#x1F60A;";
                                       ui->messageLog->append("<b>Eyai:</b> " + response);
                                   }
                               }

