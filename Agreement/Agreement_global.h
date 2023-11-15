#ifndef AGREEMENT_GLOBAL_H
#define AGREEMENT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(AGREEMENT_LIBRARY)
#  define AGREEMENT_EXPORT Q_DECL_EXPORT
#else
#  define AGREEMENT_EXPORT Q_DECL_IMPORT
#endif

#endif // AGREEMENT_GLOBAL_H
