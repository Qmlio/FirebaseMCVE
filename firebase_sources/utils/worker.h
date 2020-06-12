#ifndef WORKER_H
#define WORKER_H

#include <QDebug>
#include <QObject>
#include <QThread>
#include <functional>
namespace qmlio {
namespace googleFirebase {
class Worker : public QThread {
  Q_OBJECT
  typedef std::function<void()> Task;

public:
  Worker(QObject *parent = nullptr);
  ~Worker() override;

  void addTask(Task tsk);
signals:
  void workfinished(Worker *);

protected:
  void run() override;

private:
  Task m_trask;
};
} // namespace googleFirebase
} // namespace qmlio

#endif // WORKER_H
