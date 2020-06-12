#include "Worker.h"
using namespace qmlio::googleFirebase;

Worker::Worker(QObject *parent) : QThread(parent) {
  qDebug() << "creating worker " << this;
  connect(this, &Worker::finished, this,
          [=]() { emit this->workfinished(this); });
}

Worker::~Worker() { qDebug() << "deleting worker " << this; }

void Worker::run() { this->m_trask(); }

void Worker::addTask(Task tsk) { m_trask = tsk; }
