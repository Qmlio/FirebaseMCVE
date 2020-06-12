#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "task.h"
#include "worker.h"
#include <QObject>
namespace qmlio {
namespace googleFirebase {
class TaskManager : public QObject {
  Q_OBJECT
public:
  explicit TaskManager(QObject *parent = nullptr);
  ~TaskManager();
  void addTask(Task *tsk);
  int getMaxConcurrentThreads() const;
  void setMaxConcurrentThreads(int value);

signals:
  void complete(Task *helper);
  void pending(firebase::FutureBase future);
  void invalid();

protected:
  void waitForFuture(Task *tsk);
  void removeAll();
  void addWorker(Worker *);
  void hold(Worker *);

protected slots:
  int getWorkingLoad() const;
  void addWork(Worker *);
  void removeWorker(Worker *);
  void releaseWorker(int index);

private:
  QMap<Task *, Worker *> workerManager;
  QVector<Worker *> workers;
  QMap<int, Worker *> manager;
  int maxConcurrentThreads;
};
} // namespace googleFirebase
} // namespace qmlio
#endif // TASKMANAGER_H
