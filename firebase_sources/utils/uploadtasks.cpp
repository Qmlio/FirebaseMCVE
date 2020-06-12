#include "uploadtasks.h"
using namespace qmlio::googleFirebase;

UploadTasks::UploadTasks(QObject *parent) : QThread(parent) {
  qDebug() << "creating upload task " << this;
}

UploadTasks::~UploadTasks() { qDebug() << "deleting upload task " << this; }

void UploadTasks::run() { this->m_trask(); }

void UploadTasks::addTask(Task tsk) { m_trask = tsk; }
