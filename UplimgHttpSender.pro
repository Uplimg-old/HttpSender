#This file (c) by : - Martin Hammerchmidt alias Imote
#
#This file is licensed under a
#Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
#
#You should have received a copy of the license along with this
#work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.
#
#If you have contributed to this file, add your name to authors list.

TEMPLATE = app
TARGET = uplimg_network_http
QT += core network gui widgets
QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    httpsender.h

SOURCES += \
    httpsender.cpp \
    main.cpp

