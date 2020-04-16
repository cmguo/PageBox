#include "pagenumberwidget.h"

#include <core/toolbutton.h>

#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>

#include <views/qsshelper.h>

PageNumberWidget::PageNumberWidget(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint)
{
    static QssHelper qss(":/teachingtools/qss/pagenumber.qss");
    QSize iconSize = qss.value("QPushButton", "qproperty-iconSize").toSize();
    setStyleSheet(qss);
    QHBoxLayout* layout = new QHBoxLayout(this);
    preBtn_ = new QPushButton(this);
    preBtn_->setObjectName(("preBtn"));
    preBtn_->setIconSize(iconSize);
    preBtn_->setIcon(ToolButton::makeIcon(":/teachingtools/icon/arrow_left.svg,default", iconSize));
    preBtn_->setEnabled(false);
    progressLabel_ = new QLabel(this);
    progressLabel_->setObjectName(("progressLabel"));
    progressLabel_->setText(("0/0"));
    nextBtn_ = new QPushButton(this);
    nextBtn_->setObjectName(("nextBtn"));
    nextBtn_->setIconSize(iconSize);
    nextBtn_->setIcon(ToolButton::makeIcon(":/teachingtools/icon/arrow_right.svg,default", iconSize));
    nextBtn_->setEnabled(false);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(preBtn_);
    layout->addWidget(progressLabel_);
    layout->addWidget(nextBtn_);
    setLayout(layout);
    hide();
    QObject::connect(preBtn_, &QPushButton::clicked, this, &PageNumberWidget::buttonClicked);
    QObject::connect(nextBtn_, &QPushButton::clicked, this, &PageNumberWidget::buttonClicked);
}

PageNumberWidget::~PageNumberWidget()
{
    if (toolButton_)
        delete toolButton_;
}

void PageNumberWidget::setTotal(int n)
{
    total_ = n;
    setNumber(total_ == 0 ? -1 : 0);
}

void PageNumberWidget::setNumber(int n)
{
    if (no_ == n)
        return;
    no_ = n;
    progressLabel_->setText(QString("%1/%2").arg(no_ + 1).arg(total_));
    preBtn_->setEnabled(no_ > 0);
    nextBtn_->setEnabled(no_ + 1 < total_);
}

ToolButton *PageNumberWidget::toolButton()
{
    if (toolButton_ == nullptr)
        toolButton_ = new ToolButton({"pages", "",
                                      ToolButton::CustomWidget, QVariant::fromValue(this)});
    return toolButton_;
}

void PageNumberWidget::buttonClicked()
{
    if (sender() == preBtn_) {
        if (no_ > 0) {
            setNumber(no_ - 1);
        }
    } else if (sender() == nextBtn_) {
        if (no_ + 1 < total_) {
            setNumber(no_ + 1);
        }
    }
    emit pageNumberChanged(no_);
}
