#ifndef PAGEBOX_GLOBAL_H
#define PAGEBOX_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PAGEBOX_LIBRARY)
#  define PAGEBOX_EXPORT Q_DECL_EXPORT
#else
#  define PAGEBOX_EXPORT Q_DECL_IMPORT
#endif

#endif // PAGEBOX_GLOBAL_H
