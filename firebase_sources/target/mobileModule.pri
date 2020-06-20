message(Configuring mobile)

# add the firebase include directory
INCLUDEPATH += $$FIREBASE_SDK_PATH/include
INCLUDEPATH += $$PWD

DEFINES += QMLIO_FIREBASE_APP

contains(QMLIO_FIREBASE_CONFIG,"auth"){
message("Configuring Firebase auth")
DEFINES += QMLIO_FIREBASE_AUTH
}

contains(QMLIO_FIREBASE_CONFIG,"database"){
message("Configuring Firebase Database")
DEFINES += QMLIO_FIREBASE_DATABASE
}

android {
message(" Configuring Android. ")


FIREBASE_SDK_LIBS_PREFIX = "firebase_"

#buiding using gcc
FIREBASE_SDK_LIBS_PATH = $$FIREBASE_SDK_PATH/libs/android/$$ANDROID_TARGET_ARCH/gnustl
DEPENDPATH += $$FIREBASE_SDK_LIBS_PATH


# configuring Auth
contains(DEFINES,QMLIO_FIREBASE_AUTH) {
    message( "Including  Firebase Auth for android" )
    PRE_TARGETDEPS += $$FIREBASE_SDK_LIBS_PATH/lib$${FIREBASE_SDK_LIBS_PREFIX}auth.a
    LIBS += -L$$FIREBASE_SDK_LIBS_PATH -l$${FIREBASE_SDK_LIBS_PREFIX}auth
}

# configuring Database
contains(DEFINES,QMLIO_FIREBASE_DATABASE) {
    message( "Including  Firebase database for android" )
    PRE_TARGETDEPS += $$FIREBASE_SDK_LIBS_PATH/lib$${FIREBASE_SDK_LIBS_PREFIX}database.a
    LIBS += -L$$FIREBASE_SDK_LIBS_PATH -l$${FIREBASE_SDK_LIBS_PREFIX}database
}

# configuring App
contains(DEFINES,QMLIO_FIREBASE_APP) {
    message( "Including  Firebase app for android" )
LIBS += -L$$FIREBASE_SDK_LIBS_PATH -l$${FIREBASE_SDK_LIBS_PREFIX}app
 }
}

HEADERS += \
   $$PWD/utils/platformutils.h \
   $$PWD/firebaseauth.h \
   $$PWD/utils/firebaseutils.h \
   $$PWD/utils/task.h \
   $$PWD/firebasedatabase.h \
   $$PWD/utils/taskmanager.h \
   $$PWD/utils/worker.h

SOURCES += $$PWD/utils/platformutils.cpp \
   $$PWD/firebaseauth.cpp \
   $$PWD/utils/firebaseutils.cpp \
   $$PWD/utils/task.cpp \
   $$PWD/firebasedatabase.cpp \
   $$PWD/utils/taskmanager.cpp \
   $$PWD/utils/worker.cpp \



