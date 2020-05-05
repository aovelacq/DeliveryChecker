#ifndef LOADANIM_H
#define LOADANIM_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QMovie>

class LoadAnim : public QWidget
{
        Q_OBJECT
    public:
        explicit LoadAnim(QWidget *parent = nullptr);
        void start();
        void stop();
    signals:
    private slots:
        void timerLoop();
    protected:
        void paintEvent(QPaintEvent *event);

    private:
        QTimer *timer;
        QLabel *lbl;
        QMovie *anim;
        bool end = false;
};

#endif // LOADANIM_H
