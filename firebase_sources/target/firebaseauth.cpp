#include "firebaseauth.h"
#include <QAndroidJniObject>
#include <QDebug>
#include <QtAndroid>
#include <QtAndroidExtras/QAndroidJniEnvironment>
#include <QtAndroidExtras/QAndroidJniObject>

#define TASK_ID FirebaseUtils::Auth

namespace auth = ::firebase::auth;
using namespace qmlio::googleFirebase;

FirebaseAuth::FirebaseAuth(QObject *parent)
    : QObject(parent), m_auth(nullptr), m_complete(false), m_signedIn(false),
      m_errId(ErrorNone), m_action(ActionSignIn), mTaskManager(new TaskManager)

{

  firebaseUtils = FirebaseUtils::instance();

  connect(firebaseUtils, &FirebaseUtils::readyChanged, this,
          &FirebaseAuth::init);

  connect(mTaskManager, &TaskManager::complete, this,
          &FirebaseAuth::onFutureEvent);
}

void FirebaseAuth::setSignIn(bool value) {

  if (m_signedIn != value) {
    m_signedIn = value;

    signedInChanged(value);
  }
}

void FirebaseAuth::setError(int errId, const QString &errMsg) {
  m_errId = errId;
  m_errMsg = errMsg;

  emit errorChanged(errId, errMsg);
}

FirebaseAuth *FirebaseAuth::getInstance() {
  static QSharedPointer<FirebaseAuth> self(new FirebaseAuth);
  return self.data();
}

FirebaseAuth::~FirebaseAuth() { qDebug() << " deleting auth "; }

void FirebaseAuth::signInAnnonymously() {
  auto future = m_auth->SignInAnonymously();
  Task *tsk = Task::createNewTask(TASK_ID, ActionSignIn, future,
                                  "auth.signInAnonymous");
  mTaskManager->addTask(tsk);
}

void FirebaseAuth::init() {
  qDebug() << "initialising Auth";
  if (!firebaseUtils->isReady()) {
    return;
  }
  if (!m_auth) {
    firebase::InitResult result;
    m_auth = auth::Auth::GetAuth(firebaseUtils->firebaseNativeApp(), &result);

    if (result == firebase::kInitResultSuccess) {

      auto *user = m_auth->current_user();
      if (user != nullptr) {

        setSignIn(true);
        setComplete(true, Action::ActionSignIn);
      } else {

        signedInChanged(false);
      }

    } else {
      setError(firebase::kInitResultFailedMissingDependency,
               "Google Play Services Update");
    }
  }
}

void FirebaseAuth::onFutureEvent(Task *helper) {
  if (helper->getId() == FirebaseUtils::Auth) {

    auto g = helper->getFuture();
    auto *future = &g;

    if (future->error() == auth::kAuthErrorNone) {
      switch (helper->getType()) {

      case ActionSignIn: {
        this->taskFinished(true, ActionSignIn, QVariantMap());
        break;
      }
      }

    } else {
      setError(future->error(), future->error_message());
    }

    delete helper; // delete task
  }
}
void FirebaseAuth::setComplete(bool complete, Action act) {

  emit taskFinished(complete, act, QVariantMap());
}
