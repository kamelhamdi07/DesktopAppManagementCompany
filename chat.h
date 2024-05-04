#ifndef CHAT_H
#define CHAT_H

#include <QDialog>

namespace Ui {
class chat;
}

class chat : public QDialog
{
    Q_OBJECT

public:
    explicit chat(QWidget *parent = nullptr);
    ~chat();
private slots:
    void processMessage();
private:
    Ui::chat *ui;
};

#endif // CHAT_H
