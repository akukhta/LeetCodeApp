#include "ProblemWidget.h"

QString const ProblemWidget::active = "border-radius: 15px; background-color: rgb(255, 255, 255);";
QString const ProblemWidget::passtive = "border-radius: 15px; background-color: rgb(45, 45, 68);";
QString const ProblemWidget::activeLabel = "QLabel { color : rgb(0,0, 0);}";
QString const ProblemWidget::passtiveLabel = "QLabel { color : rgb(255, 255, 255);}";

ProblemWidget::ProblemWidget(QString name, QString acceptance, QString difficulty, QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.nameLabel->setText(name);
	ui.acceptanceLabel->setText(acceptance);
	ui.difficultyLabel->setText(difficulty);
	setAttribute(Qt::WA_Hover, true);
    leaved();
}

bool ProblemWidget::event(QEvent* e)
{
    switch (e->type())
    {
    case QEvent::HoverEnter:
        hoverEnter(static_cast<QHoverEvent*>(e));
        return true;
        break;
    case QEvent::HoverLeave:
        hoverLeave(static_cast<QHoverEvent*>(e));
        return true;
        break;
    case QEvent::HoverMove:
        hoverMove(static_cast<QHoverEvent*>(e));
        return true;
        break;
    default:
        break;
    }
    return QWidget::event(e);
}

void ProblemWidget::enterEvent(QEvent* e)
{
    activated();
}

void ProblemWidget::leaveEvent(QEvent* e)
{
    leaved();
}


void ProblemWidget::hoverEnter(QHoverEvent* event)
{
    qDebug() << Q_FUNC_INFO << event->type();
}

void ProblemWidget::hoverLeave(QHoverEvent* event)
{
    qDebug() << Q_FUNC_INFO << event->type();
}

void ProblemWidget::hoverMove(QHoverEvent* event)
{
    qDebug() << Q_FUNC_INFO << event->type();
}

void ProblemWidget::activated()
{
    setStyleSheet(active);
    ui.nameLabel->setStyleSheet(activeLabel);
    ui.acceptanceLabel->setStyleSheet(activeLabel);
    ui.difficultyLabel->setStyleSheet(activeLabel);
}

void ProblemWidget::leaved()
{
    setStyleSheet(passtive);
    ui.nameLabel->setStyleSheet(passtiveLabel);
    ui.acceptanceLabel->setStyleSheet(passtiveLabel);
    ui.difficultyLabel->setStyleSheet(passtiveLabel);
}

ProblemWidget::~ProblemWidget()
{}
