#############################################################################
# Makefile for building: build/CloudFactory.app/Contents/MacOS/CloudFactory
# Generated by qmake (2.01a) (Qt 4.7.2) on: Sun Apr 17 16:58:11 2011
# Project:  CloudFactory.pro
# Template: app
# Command: /usr/bin/qmake -o CloudFactory.xcodeproj/project.pbxproj CloudFactory.pro
#############################################################################

MOC       = /Developer/Tools/Qt/moc
UIC       = /Developer/Tools/Qt/uic
LEX       = flex
LEXFLAGS  = 
YACC      = yacc
YACCFLAGS = -d
DEFINES       = -DQT_XML_LIB -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
INCPATH       = -I/usr/local/Qt4.7/mkspecs/macx-xcode -I. -I/Library/Frameworks/QtCore.framework/Versions/4/Headers -I/usr/include/QtCore -I/Library/Frameworks/QtGui.framework/Versions/4/Headers -I/usr/include/QtGui -I/Library/Frameworks/QtOpenGL.framework/Versions/4/Headers -I/usr/include/QtOpenGL -I/Library/Frameworks/QtXml.framework/Versions/4/Headers -I/usr/include/QtXml -I/usr/include -I$(WM5_PATH)/SDK/Include -I. -I/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers -I/System/Library/Frameworks/AGL.framework/Headers -Itmp/moc -I/usr/local/include -I/System/Library/Frameworks/CarbonCore.framework/Headers -F/Library/Frameworks
DEL_FILE  = rm -f
MOVE      = mv -f

IMAGES = 
PARSERS =
preprocess: $(PARSERS) compilers
clean preprocess_clean: parser_clean compiler_clean

parser_clean:
check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compilers: tmp/moc/moc_GraphicsView.cpp tmp/moc/moc_HomeScreen.cpp tmp/moc/moc_MainScene.cpp\
	 tmp/moc/moc_mygldrawer.cpp tmp/rcc/qrc_resources.cpp
compiler_objective_c_make_all:
compiler_objective_c_clean:
compiler_moc_header_make_all: tmp/moc/moc_GraphicsView.cpp tmp/moc/moc_HomeScreen.cpp tmp/moc/moc_MainScene.cpp tmp/moc/moc_mygldrawer.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) tmp/moc/moc_GraphicsView.cpp tmp/moc/moc_HomeScreen.cpp tmp/moc/moc_MainScene.cpp tmp/moc/moc_mygldrawer.cpp
tmp/moc/moc_GraphicsView.cpp: src/MainScene.h \
		src/MetaballCanvas.hpp \
		src/marchingcubes.hpp \
		src/CloudModel.hpp \
		src/BluePrintDetect.h \
		src/BluePrintHUD.h \
		src/HUDWidget.h \
		src/HomeScreen.h \
		src/Levels.h \
		src/GraphicsView.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ src/GraphicsView.h -o tmp/moc/moc_GraphicsView.cpp

tmp/moc/moc_HomeScreen.cpp: src/HomeScreen.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ src/HomeScreen.h -o tmp/moc/moc_HomeScreen.cpp

tmp/moc/moc_MainScene.cpp: src/MetaballCanvas.hpp \
		src/marchingcubes.hpp \
		src/CloudModel.hpp \
		src/BluePrintDetect.h \
		src/BluePrintHUD.h \
		src/HUDWidget.h \
		src/MainScene.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ src/MainScene.h -o tmp/moc/moc_MainScene.cpp

tmp/moc/moc_mygldrawer.cpp: src/marchingcubes.hpp \
		src/mygldrawer.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ src/mygldrawer.h -o tmp/moc/moc_mygldrawer.cpp

compiler_rcc_make_all: tmp/rcc/qrc_resources.cpp
compiler_rcc_clean:
	-$(DEL_FILE) tmp/rcc/qrc_resources.cpp
tmp/rcc/qrc_resources.cpp: resources.qrc
	/Developer/Tools/Qt/rcc -name resources resources.qrc -o tmp/rcc/qrc_resources.cpp

compiler_image_collection_make_all: tmp/ui/qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) tmp/ui/qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_rez_source_make_all:
compiler_rez_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean 

