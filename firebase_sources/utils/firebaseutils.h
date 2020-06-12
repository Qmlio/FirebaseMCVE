#ifndef FIREBASEUTILS_H
#define FIREBASEUTILS_H

#include "firebase/app.h"
#include "firebase/future.h"
#include "firebase/util.h"
#include "firebase/variant.h"
#include "task.h"
#include <QObject>
#include <QSharedPointer>
#include <QThreadPool>
#include <QTimer>
namespace qmlio {
namespace googleFirebase {
template <typename ResultType> const ResultType *result(const void *p) {
  return p == nullptr ? nullptr : static_cast<const ResultType *>(p);
}
class FirebaseUtils : public QObject {
  Q_OBJECT
public:
  enum Tasks { Auth, Database, Storage, Messaging, DyanmicLinks };
  static void wait();
  ~FirebaseUtils();
  firebase::App *firebaseNativeApp() const;
  static FirebaseUtils *instance();
  static QVariant fromFirebaseVariant(const firebase::Variant &v);
  static firebase::Variant fromQtVariant(const QVariant &v);
  inline bool isReady() const { return mReady; }
signals:
  void readyChanged();

protected:
  void init();
  static QSharedPointer<FirebaseUtils> self;

private:
  explicit FirebaseUtils(QObject *parent = nullptr);
  bool mReady;
  QTimer *_initTimer = nullptr;
  firebase::App *_firebaseApp = 0;

  Q_DISABLE_COPY(FirebaseUtils)
};
} // namespace googleFirebase
} // namespace qmlio
#endif // FIREBASEUTILS_H
