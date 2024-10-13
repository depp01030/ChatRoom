#ifndef CODE_CARD_H
#define CODE_CARD_H

#include <QPushButton>  
// #include "card_color.h"
class CodeCard : public QPushButton {
    Q_OBJECT

public: 
    explicit CodeCard(int id, QString word, QWidget *parent = nullptr);
    // void setupConnections();
    int m_id;
    QString m_word; 
    void turnOpen(const QColor &color);
private slots:
    // void onCardClicked();
signals:
    void cardClicked(const CodeCard* codeCard);
private: 
    void initializeCard(); 
    QColor m_backgroundColor = QColor(87, 83, 72);
};
#endif // CODE_CARD_H