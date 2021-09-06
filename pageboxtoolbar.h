#ifndef PAGEBOXTOOLBAR_H
#define PAGEBOXTOOLBAR_H

#include "PageBox_global.h"

#include <views/toolbarwidget.h>

class PageNumberWidget;

class PAGEBOX_EXPORT PageBoxToolBar : public ToolbarWidget
{
    Q_OBJECT
public:
    explicit PageBoxToolBar(QWidget *parent = nullptr);

    virtual ~PageBoxToolBar() override;

protected:
    QWidget * createPopupWidget() override;
};

#endif // PAGEBOXTOOLBAR_H
