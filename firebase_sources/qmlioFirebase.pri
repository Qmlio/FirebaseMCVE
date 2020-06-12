message(initialising Qt Firebase)

isEmpty(FIREBASE_SDK_PATH){
error("Firebase sdk path  is invalid, plugin may fail to build. ")
}
else{
message("Using firebase_sdk_path ($$FIREBASE_SDK_PATH)")
}

android {
    include(target/mobileModule.pri)
}
