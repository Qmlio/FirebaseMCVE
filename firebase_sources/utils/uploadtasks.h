#ifndef UPLOADTASKS_H
#define UPLOADTASKS_H

#include <QDebug>
#include <QObject>
#include <QThread>
#include <functional>
namespace qmlio {
namespace googleFirebase {
class UploadTasks : public QThread {
  Q_OBJECT
  typedef std::function<void()> Task;

public:
  UploadTasks(QObject *parent = nullptr);
  ~UploadTasks() override;

  void addTask(Task tsk);
signals:
  void finished();

protected:
  void run() override;

private:
  Task m_trask;
};
} // namespace googleFirebase
} // namespace qmlio
#endif // UPLOADTASKS_H
