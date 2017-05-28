TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    armordetector.cpp \
    predictor.cpp \
    rectutil.cpp

INCLUDEPATH += /usr/local/include/opencv
LIBS += -lopencv_core \
-lopencv_imgproc \
-lopencv_highgui \
-lopencv_ml \
-lopencv_video \
-lopencv_features2d \
-lopencv_calib3d \
-lopencv_objdetect \
-lopencv_contrib \
-lopencv_legacy \
-lopencv_flann

DISTFILES += \
    ArmorDetector.pro.user

HEADERS += \
    armordetector.h \
    predictor.h \
    rectutil.h
