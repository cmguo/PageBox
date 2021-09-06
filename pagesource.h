#ifndef PAGESOURCE_H
#define PAGESOURCE_H

#include "PageBox_global.h"
#include "qpropertybindings.h"

#include <core/resourceview.h>

#include <QtPromise>
#include <QObject>
#include <QUrl>

class ToolButton;

class QAbstractItemModel;

class PAGEBOX_EXPORT PageSource : public ResourceView
{
    Q_OBJECT

    Q_CLASSINFO("version", "1.0")

public:
    explicit PageSource(Resource * res, Flags flags = None,
                        Flags clearFlags = None);

public:
    virtual QSizeF pageSize() = 0;

    virtual QPropertyBindings * itemBinding() = 0;

    virtual QtPromise::QPromise<void> load() = 0;

    virtual QAbstractItemModel * items() = 0;

    virtual int initialPage() = 0;

signals:
    void requestPage(int page);

public:
    virtual void onLoaded();

    virtual bool onToolButton(ToolButton * button);
};

#endif // PAGESOURCE_H
