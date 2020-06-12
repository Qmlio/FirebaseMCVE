#ifndef TASK_H
#define TASK_H
#include "firebase/future.h"
#include <QObject>
#include <QString>
#include <QThread>
namespace qmlio {
namespace googleFirebase {
class Task {
public:
  Task(int id, int type, firebase::FutureBase future, QString tag = "",
       int prior = 0, bool usestdFuture = false);
  Task();

  ~Task();

  static Task *createNewTask(int id, int type, firebase::FutureBase future,
                             QString tag = "", int priority = 0,
                             bool usestdFuture = false);

  // setters
  void setId(int id);
  void setType(int type);
  void setTag(QString tag);
  void setFuture(firebase::FutureBase future);
  void setFuture();
  void setPriorty(int prior);

  // getters
  int getId() const;
  int getType() const;
  QString getTag() const;
  QString key() const;
  int priority() const;
  firebase::FutureBase getFuture() const;
  QThread::Priority getTask_Priority() const;
  void setTask_Priority(const QThread::Priority &value);

  firebase::Future<std::string> getStdfuture() const;
  void setStdfuture(const firebase::Future<std::string> &stdfuture);

  bool getUseStdFuture() const;
  void setUseStdFuture(bool value);

protected:
  QString generateKey();

private:
  int id;
  int type;
  bool useStdFuture;
  firebase::FutureBase future;
  firebase::Future<std::string> mStdfuture;
  QString tag;
  int m_Priority;
  QString m_key;
  QString temp;
  QThread::Priority task_Priority;
};

} // namespace googleFirebase
} // namespace qmlio
Q_DECLARE_METATYPE(qmlio::googleFirebase::Task)
#endif // TASK_H
