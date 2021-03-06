#include "pagenumberwidget.h"

#include <core/resourcepage.h>
#include <core/resourcerecord.h>
#include <core/toolbutton.h>
#include <views/qsshelper.h>

#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>

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
    if (total_ == n)
        return;
    total_ = n;
    no_ = -1;
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
    if (page_)
        page_->switchSubPage(no_);
}

bool PageNumberWidget::gotoPrev()
{
	return gotoPage(no_ - 1);
}

bool PageNumberWidget::gotoNext()
{
	return gotoPage(no_ + 1);
}

bool PageNumberWidget::gotoPage(int n)
{
    RecordMergeScope rs(page_);
    if (n == no_)
        return true;
    if (n < 0 || n >= total_)
        return false;
    setNumber(n);
    emit pageNumberChanged(no_);
    return true;
}

bool PageNumberWidget::isFirstPage() const
{
    return no_ == 0;
}

bool PageNumberWidget::isLastPage() const
{
    return no_ + 1 == total_;
}

void PageNumberWidget::notify()
{
    emit pageNumberChanged(no_);
}

ToolButton *PageNumberWidget::toolButton()
{
    if (toolButton_ == nullptr)
        toolButton_ = new ToolButton({"pages", "",
                                      ToolButton::CustomWidget, QVariant::fromValue(this)});
    return toolButton_;
}

void PageNumberWidget::attachResourcePage(ResourcePage *page)
{
    if (page_)
        page_->disconnect(this);
    page_ = page;
    if (page_) {
        connect(page, &ResourcePage::currentSubPageChanged, this, [this] () {
            int no = page_->currentSubNumber();
            if (no == -1)
                setNumber(no);
            else
                gotoPage(no);
        });
    }
}

void PageNumberWidget::buttonClicked()
{
    if (sender() == preBtn_) {
        gotoPrev();
    } else if (sender() == nextBtn_) {
        gotoNext();
    }
}
