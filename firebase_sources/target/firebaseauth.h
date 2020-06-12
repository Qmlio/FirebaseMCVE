#ifndef FIREBASEAUTH_H
#define FIREBASEAUTH_H

#include "firebase/auth.h"
#include "utils/firebaseutils.h"
#include <QAndroidActivityResultReceiver>
#include <QObject>
#include <QVariantMap>
#include <utils/taskmanager.h>

namespace qmlio {

namespace googleFirebase {

class FirebaseAuth : public QObject {
  Q_OBJECT

public:
  enum Error {
    ErrorNone = firebase::auth::kAuthErrorNone,
    ErrorUnimplemented = firebase::auth::kAuthErrorUnimplemented,
    ErrorFailure = firebase::auth::kAuthErrorFailure
  };
  Q_ENUM(Error)

  static FirebaseAuth *getInstance();
  ~FirebaseAuth();

  enum Action { ActionSignIn };
  Q_ENUM(Action)

signals:
  void signedInChanged(bool isSignedIn);
  void runningChanged();
  void taskFinished(bool success, int actionId, const QVariantMap user);
  void errorChanged(int errId, const QString &errMsg);

public slots:
  void signInAnnonymously();

protected slots:
  void init();
  void onFutureEvent(Task *helper);

protected:
  explicit FirebaseAuth(QObject *parent = nullptr);
  void setComplete(bool complete, Action action);
  void setSignIn(bool value);
  void setError(int errId, const QString &errMsg = QString(""));

private:
  firebase::auth::Auth *m_auth;
  bool m_complete;
  bool m_signedIn;
  int m_errId;
  QString m_errMsg;
  int m_action;
  FirebaseUtils *firebaseUtils;
  TaskManager *mTaskManager;
  Q_DISABLE_COPY(FirebaseAuth)
};

} // namespace googleFirebase
} // namespace qmlio
#endif // FIREBASEAUTH_H
