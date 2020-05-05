#include "loadanim.h"

LoadAnim::LoadAnim(QWidget *parent) : QWidget(parent)
{
    lbl = new QLabel(this,Qt::WindowStaysOnTopHint);
    anim = new QMovie(":/img/img/load.gif");
    anim->setSpeed(200);
    timer = new QTimer;
    timer->setInterval(2500);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timerLoop()));
    lbl->setMovie(anim);
    setFixedSize(100,100);
    lbl->setFixedSize(100,100);
    anim->setScaledSize(lbl->size());
    hide();
}

void LoadAnim::start()
{
    end=false;
    parentWidget()->setEnabled(false);
    show();
    lbl->show();
    anim->start();
    timer->start();
}

void LoadAnim::stop()
{
    end=true;
}

void LoadAnim::timerLoop()
{
    if (!end) return;
    parentWidget()->setEnabled(true);
    hide();
    anim->stop();
    timer->stop();
}

void LoadAnim::paintEvent(QPaintEvent *event)
{
    move(parentWidget()->width() / 2 - width() / 2,
         parentWidget()->height() / 2 - height() / 2);
    QWidget::paintEvent(event);
}
