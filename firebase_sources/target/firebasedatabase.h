#ifndef FIREBASEDATABASE_H
#define FIREBASEDATABASE_H

#include "firebase/database.h"
#include "utils/firebaseutils.h"
#include <QObject>
#include <utils/task.h>
#include <utils/taskmanager.h>

namespace qmlio {
namespace googleFirebase {

class FirebaseDatabase : public QObject {

  Q_OBJECT

public:
  ~FirebaseDatabase() override;
  static FirebaseDatabase *getInstance();
  firebase::database::Database *getDatabase() const;

  void setError(int errorCode, QString errorMsg, QString tag = "database");
  enum Types { SetValue, UpdateValue, RemoveValue, GetValue };

  static Task *createTask(Types t, firebase::FutureBase future,
                          QString tag = "database", int p = 0);

signals:
  void errorChanged(int errorCode, QString errorMsg, QString tag);
  void databaseInitialized(bool ready);
  void completed(int type, QByteArray value);

public slots:
  void test(const QVariant &value);

protected slots:
  void init();
  void finished(Task *tsk);

protected:
  explicit FirebaseDatabase(QObject *parent = nullptr);

private:
  firebase::database::Database *database = nullptr;
  bool dbReady;

  TaskManager *mTaskManager;
  FirebaseUtils *service;
  Q_DISABLE_COPY(FirebaseDatabase)
};
} // namespace googleFirebase
} // namespace qmlio
#endif // FIREBASEDATABASE_H
