#include "firebasedatabase.h"
#include "../utils/platformutils.h"

#include <QDateTime>
#include <QDebug>

#define TASK_ID FirebaseUtils::Database

using namespace qmlio::googleFirebase;

FirebaseDatabase::FirebaseDatabase(QObject *parent)
    : QObject(parent), dbReady(false) {
  service = FirebaseUtils::instance();

  mTaskManager = new TaskManager();
  connect(service, &FirebaseUtils::readyChanged, this, &FirebaseDatabase::init);
  connect(mTaskManager, &TaskManager::complete, this,
          &FirebaseDatabase::finished);
}

FirebaseDatabase::~FirebaseDatabase() {
  qDebug() << "deleting database " << this;
  // database = nullptr;
}

firebase::database::Database *FirebaseDatabase::getDatabase() const {
  return this->database;
}

void FirebaseDatabase::setError(int errorCode, QString errorMsg, QString tag) {
  emit errorChanged(errorCode, errorMsg, tag);
}

Task *FirebaseDatabase::createTask(FirebaseDatabase::Types _type,
                                   firebase::FutureBase future, QString tag,
                                   int priority) {

  Task *tsk = Task::createNewTask(FirebaseUtils::Database, _type, future, tag,
                                  priority);
  return tsk;
}

qint64 FirebaseDatabase::timeStamp() {
  QDateTime t;
  return t.currentMSecsSinceEpoch();
}

void FirebaseDatabase::test(const QVariant &value) {
  qDebug() << value;
  auto future = database->GetReference().Child("test").SetValue(
      FirebaseUtils::fromQtVariant(value));

  auto tsk = createTask(SetValue, future, "testing::Error", 0);

  qDebug() << "creating " << tsk->key() << future.status();
  mTaskManager->addTask(tsk);
}

void FirebaseDatabase::init() {
  qDebug() << "initialising database Android " << this;
  if (!PlatformUtils::getNativeWindow()) {
    emit databaseInitialized(false);
    return;
  }

  if (GooglePlayServices::getAvailability() ==
      GooglePlayServices::AvailabilityAvailable) {

    firebase::InitResult result;
    database = firebase::database::Database::GetInstance(
        service->firebaseNativeApp(), &result);

    if (result == firebase::kInitResultSuccess) {
      dbReady = true;

      emit databaseInitialized(true);

    } else if (result != firebase::kInitResultSuccess) {
      setError(firebase::kInitResultFailedMissingDependency,
               "Please update your google play services");
      emit databaseInitialized(false);
      dbReady = false;
    }
  }
}
void FirebaseDatabase::finished(Task *tsk) {

  if (tsk->getId() == TASK_ID) {
    auto future = tsk->getFuture();
    if (future.error() == firebase::database::kErrorNone) {

      if (tsk->key() == currentKey) {
        switch (tsk->getType()) {
        case FirebaseDatabase::SetValue: {
          emit completed(FirebaseDatabase::SetValue, QByteArray());

        } break;
        }

        delete tsk;
      }

    } else {
      setError(future.error(), future.error_message());
    }
  }
}
